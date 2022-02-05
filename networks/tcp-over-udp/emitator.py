import logging

from argparse import ArgumentParser
from socket import *

from threading import Lock
from helper import *

from math import floor
from time import time

from queue import Queue

from typing import Set, Dict, IO

timeoutTime: float = 1
smoothedRoundTripTime: float

logging.basicConfig(filename='logEmitator.txt', filemode='a', format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)


def connect(sock: socket, serverAddress: tuple) -> tuple:
    global smoothedRoundTripTime

    sequenceNumber: int = floor(uniform(SEQ_NUM_MIN, SEQ_NUM_MAX))

    flag: str = 'S'

    octetsWithoutCheckSum: bytes = createClientHeader(sequenceNumber, 0, flag)

    checkSum: int = calculateCheckSum(octetsWithoutCheckSum)

    octetsWithCheckSum: bytes = createClientHeader(sequenceNumber, checkSum, flag)

    initialTime: float = time()

    logging.info('Sending \'synchronize\' flag.')

    sock.sendto(octetsWithCheckSum, serverAddress)

    try:
        data: bytes = sock.recvfrom(HEADER_SIZE)[0]

    except timeout:
        logging.info('Connection timeout. Retrying...')
        return connect(sock, serverAddress)

    if not verifyCheckSum(data):
        logging.info('Received package with wrong checksum. Retrying...')
        return connect(sock, serverAddress)

    smoothedRoundTripTime = time() - initialTime

    acknowledgementNumber: int
    checkSum: int
    windowSize: int

    acknowledgementNumber, checkSum, windowSize = parseServerHeader(data)

    return acknowledgementNumber, windowSize


def finalize(sock: socket, serverAddress: tuple, sequenceNumber: int) -> int:
    octetsWithoutCheckSum: bytes = createClientHeader(sequenceNumber, 0, 'F')

    checkSum: int = calculateCheckSum(octetsWithoutCheckSum)

    octetsWithCheckSum: bytes = createClientHeader(sequenceNumber, checkSum, 'F')

    logging.info('Sending \'finalise\' flag.')
    sock.sendto(octetsWithCheckSum, serverAddress)

    try:
        data: bytes = sock.recvfrom(HEADER_SIZE)[0]

    except timeout:
        logging.info('Connection timeout. Retrying...')
        return finalize(sock, serverAddress, sequenceNumber)

    if not verifyCheckSum(data):
        logging.info('Received package with wrong checksum. Retrying...')
        return finalize(sock, serverAddress, sequenceNumber)

    logging.info('Finalised connection :)')

    return 0


def listener(sock: socket, threads: Dict[int, ThreadWithStatusAndTime], status: IsDone) -> int:
    global smoothedRoundTripTime, timeoutTime

    while True:
        if status.isDone:
            return 0

        try:
            data, address = sock.recvfrom(HEADER_SIZE)

        except Exception as err:
            logging.info(str(err))
            continue

        if not verifyCheckSum(data):
            logging.info('Received package with wrong checksum. Ignoring.')
            continue

        acknowledgementNumber, _, windowSize = parseServerHeader(data)

        logging.info('Received package with acknowledgementNumber: %d.' % acknowledgementNumber)

        try:
            currentThread: ThreadWithStatusAndTime = threads[acknowledgementNumber]

        except Exception as err:
            logging.info('Thread with acknowledgementNumber %d already resolved.' % acknowledgementNumber)
            logging.info(str(err))
            continue

        currentThread.status.windowSize = windowSize
        currentThread.status.isDone = True

        roundTripTime: float = time() - currentThread.startTime.time

        smoothedRoundTripTime = alpha * smoothedRoundTripTime + (1 - alpha) * roundTripTime

        timeoutTime = max(timeoutLowerBound, min(timeoutUpperBound, beta * smoothedRoundTripTime))

        logging.info('Modifying timeout as %s.' % timeoutTime)

        sock.settimeout(timeoutTime)


def sender(sock: socket, serverAddress: tuple, sequenceNumber: int, payloadOctets: bytes,
           missingAcknowledgementNumbers: Set[int], lock: Lock, status: IsDone, initialTime: InitialTime) -> int:

    octetsWithoutCheckSum = createClientHeader(sequenceNumber, 0, 'P') + payloadOctets

    checkSum = calculateCheckSum(octetsWithoutCheckSum)

    octetsWithCheckSum = createClientHeader(sequenceNumber, checkSum, 'P') + payloadOctets

    logging.info('Sending sequenceNumber: %d.' % sequenceNumber)

    initialTime.time = time()

    sock.sendto(octetsWithCheckSum, serverAddress)

    targetTime: float = time() + timeoutTime

    while time() <= targetTime:
        if status.isDone:
            break

    if status.isDone:
        with lock:
            missingAcknowledgementNumbers.remove(sequenceNumber)

        return 0

    logging.info('Timeout for %d expired. Resending.' % sequenceNumber)

    return sender(sock, serverAddress, sequenceNumber, payloadOctets,
                  missingAcknowledgementNumbers, lock, status, initialTime)


def main():
    parser = ArgumentParser(usage=__file__ + ' '
                                             '-a/--address IP '
                                             '-p/--port PORT '
                                             '-f/--file FILE_PATH',
                            description='Reliable UDP Emitter')

    parser.add_argument('-a', '--address',
                        dest='address',
                        default='192.168.0.1',
                        help='Destination server\'s IP address')

    parser.add_argument('-p', '--port',
                        dest='port',
                        default='10000',
                        help='Destination server\'s port')

    parser.add_argument('-f', '--file',
                        dest='file',
                        help='Path to file')

    args = vars(parser.parse_args())

    file = args['file']
    serverAddress = (args['address'], int(args['port']))

    sock = socket(AF_INET, SOCK_DGRAM, proto=IPPROTO_UDP)

    sock.settimeout(timeoutTime)

    lock: Lock = Lock()

    try:
        acknowledgementNumber, windowSize = connect(sock, serverAddress)

        fileDescriptor: IO = open(file, 'rb')

        threads: Dict[int, ThreadWithStatusAndTime] = dict()
        threadsQueue: Queue[ThreadWithStatusAndTime] = Queue()

        missingAcknowledgementNumbers: Set[int] = set()
        currentSequenceNumber: int = 0

        sentSegments: int = -1
        currentSequenceNumber: int

        listenerThreadStatus: IsDone = IsDone()
        listenerThread: Thread = Thread(target=listener, args=(sock, threads, listenerThreadStatus))
        listenerThread.start()

        while segments := readNSegments(fileDescriptor, windowSize):
            for segment in segments:
                sentSegments += 1
                currentSequenceNumber: int = acknowledgementNumber + sentSegments + 1

                if currentSequenceNumber == SEQ_NUM_MAX:
                    acknowledgementNumber = 0
                    currentSequenceNumber = 0
                    sentSegments = -1

                    for threadWithStatusAndTime in threads.values():
                        threadWithStatusAndTime.thread.join()

                status: IsDone = IsDone()

                with lock:
                    missingAcknowledgementNumbers.add(currentSequenceNumber)

                initialTime: InitialTime = InitialTime()

                logging.info('Creating thread for sequenceNumber %d.' % currentSequenceNumber)
                thread: Thread = Thread(target=sender, args=(sock, serverAddress, currentSequenceNumber, segment,
                                                             missingAcknowledgementNumbers, lock, status, initialTime))

                threadWithStatusAndTime = ThreadWithStatusAndTime(thread, status, initialTime, currentSequenceNumber)

                threads[currentSequenceNumber] = threadWithStatusAndTime
                threadsQueue.put(threadWithStatusAndTime)
                thread.start()

            currentThreadToWait: ThreadWithStatusAndTime

            while (newWindowSize := windowSize - len(missingAcknowledgementNumbers)) <= 0:
                currentThreadToWait = threadsQueue.get()

                currentThreadToWait.thread.join()

                windowSize = currentThreadToWait.status.windowSize

                threads.pop(currentThreadToWait.sequenceNumber)
                del currentThreadToWait

            windowSize = newWindowSize

        for threadWithStatusAndTime in threads.values():
            threadWithStatusAndTime.thread.join()

        listenerThreadStatus.isDone = True
        listenerThread.join()

        finalize(sock, serverAddress, currentSequenceNumber + 1)

    except Exception as err:
        logging.exception(str(err))

    finally:
        logging.info('Socket is now closed.')
        sock.close()


if __name__ == '__main__':
    main()
