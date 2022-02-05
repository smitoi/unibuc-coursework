import socket
import logging

from helper import *
from argparse import ArgumentParser
from random import uniform
from queue import PriorityQueue

from threading import Thread


logging.basicConfig(filename='logReceptor.txt', filemode='a', format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)


class Payload:
    sequenceNumber: int
    payload: bytes

    def __init__(self, sequenceNumber, payload):
        self.sequenceNumber = sequenceNumber
        self.payload = payload

    def __lt__(self, other):
        return self.sequenceNumber < other.sequenceNumber

    def __eq__(self, other):
        return self.__dict__ == other.__dict__


class WriterThreadData:
    buffer: PriorityQueue
    currentAcknowledgementNumber: int
    fileDescriptor: IO

    def __init__(self, buffer: PriorityQueue, currentAcknowledgementNumber: int, fileDescriptor: IO):
        self.buffer = buffer
        self.currentAcknowledgementNumber = currentAcknowledgementNumber
        self.fileDescriptor = fileDescriptor


def generateWindowSize() -> int:
    return round(uniform(1, 5))


def fileWriter(data: WriterThreadData):
    while True:
        if data.fileDescriptor.closed:
            return 0

        while data.buffer.qsize() and data.currentAcknowledgementNumber == data.buffer.queue[0].sequenceNumber:
            currentPayload: Payload = data.buffer.get()
            data.fileDescriptor.write(currentPayload.payload)
            data.currentAcknowledgementNumber += 1


def send(sock: socket, octets: bytes, address: str, windowSize: int):
    logging.info('Responding with windowSize: %d.' % windowSize)
    sock.sendto(octets, address)


def main():
    parser = ArgumentParser(usage=__file__ + ' '
                                             '-p/--port PORT'
                                             '-f/--file FILE_PATH',
                            description='Reliable UDP Receptor')

    parser.add_argument('-p', '--port',
                        dest='port',
                        default='10000',
                        help='Listener port')

    parser.add_argument('-f', '--file',
                        dest='file',
                        help='Path used to store the transferred file')

    args = vars(parser.parse_args())

    port = int(args['port'])
    file = args['file']

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)

    address: str = '0.0.0.0'
    serverAddress = (address, port)

    sock.bind(serverAddress)

    logging.info("Server is running on %s:%s." % (address, port))

    expectedAddress: str or None = None

    currentAcknowledgementNumber: int = -1
    buffer: PriorityQueue[Payload] = PriorityQueue()

    fileDescriptor: IO = open(file, 'wb')

    fileWriterThreadData: WriterThreadData = WriterThreadData(buffer, currentAcknowledgementNumber, fileDescriptor)
    fileWriterThread: Thread = Thread(target=fileWriter, args=(fileWriterThreadData,))

    fileWriterThread.start()

    while True:
        try:
            logging.info('Awaiting message.')

            data, address = sock.recvfrom(MAX_SEGMENT + HEADER_SIZE)

            if not verifyCheckSum(data):
                logging.info('Received package with wrong checksum. Ignoring.')
                continue

            if expectedAddress is not None and address != expectedAddress:
                logging.info('Received package from unexpected address: %s. Ignoring.' % str(address))
                continue

            sequenceNumber, _, flag = parseClientHeader(data[:8])

            if expectedAddress is None and flag != 'S':
                logging.info(f'No synchronisation has been done before receiving a package with flag {flag}. Ignoring.')
                continue

            logging.info('Received sequenceNumber: %d.' % sequenceNumber)

            acknowledgementNumber = sequenceNumber + (0 if flag == 'P' else 1)

            if acknowledgementNumber == 0:
                fileWriterThreadData.currentAcknowledgementNumber = 0

            if flag == 'S':
                logging.info('Received \'synchronise\' flag.')

                if fileWriterThreadData.fileDescriptor.closed:
                    logging.info('File already received. Can\'t synchronise again. Ignoring.')
                    continue

                fileWriterThreadData.currentAcknowledgementNumber = acknowledgementNumber + 1
                logging.info('Setting expected address as %s.' % str(address))
                expectedAddress = address

            windowSize = generateWindowSize()

            octetsWithoutCheckSum: bytes = createServerHeader(acknowledgementNumber, 0, windowSize)

            checkSum: int = calculateCheckSum(octetsWithoutCheckSum)

            octetsWithCheckSum: bytes = createServerHeader(acknowledgementNumber, checkSum, windowSize)

            if flag == 'F':
                logging.info('Received \'finalise\' flag.')

                if not fileWriterThreadData.fileDescriptor.closed:
                    logging.info('Saving file.')
                    while fileWriterThreadData.buffer.qsize():
                        pass
                    fileWriterThreadData.fileDescriptor.close()
                    fileWriterThread.join()
                    logging.info('File successfully saved.')

                sock.sendto(octetsWithCheckSum, address)
                continue

            elif flag == 'P':
                payload: bytes = data[8:]
                logging.info('Received \'package\' flag.')
                payloadBuffer: Payload = Payload(sequenceNumber, payload)

                if acknowledgementNumber >= fileWriterThreadData.currentAcknowledgementNumber:
                    fileWriterThreadData.buffer.put(payloadBuffer)
                    logging.info('Appending to buffer.')
                else:
                    logging.info('Package is duplicate. Omitted.')

            send(sock, octetsWithCheckSum, address, windowSize)

        except Exception as err:
            logging.exception(str(err))


if __name__ == '__main__':
    main()
