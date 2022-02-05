from __future__ import annotations

import struct
import itertools

from threading import Thread
from random import uniform
from typing import IO, List

MAX_SEGMENT: int = 4096
HEADER_SIZE: int = 8

SEQ_NUM_MIN: int = 0
SEQ_NUM_MAX: int = 0xFFFFFFFF

alpha: float = .8
beta: float = uniform(1.3, 2)

timeoutUpperBound: float = 5
timeoutLowerBound: float = 25e-2


class InitialTime:
    time: float


class IsDone:
    isDone: bool
    windowSize: int

    def __init__(self):
        self.isDone = False
        self.windowSize = -1


class ThreadWithStatusAndTime:
    thread: Thread
    status: IsDone
    startTime: InitialTime
    sequenceNumber: int

    def __init__(self, thread: Thread, status: IsDone, startTime: InitialTime, sequenceNumber: int):
        self.thread = thread
        self.status = status
        self.startTime = startTime
        self.sequenceNumber = sequenceNumber


def createClientHeader(sequenceNumber: int, checkSum: int, flag: str) -> bytes:
    flagNum: int

    if flag == 'F':
        flagNum = 1
    elif flag == 'P':
        flagNum = 2
    else:
        flagNum = 4

    flagNum <<= 13

    return struct.pack('!LHH', sequenceNumber, checkSum, flagNum)


def parseClientHeader(octets: bytes) -> tuple:
    sequenceNumber, checkSum, flagNum = struct.unpack('!LHH', octets)

    flagNum >>= 13

    flag: str

    if flagNum & 0b1:
        flag = 'F'

    elif flagNum & 0b10:
        flag = 'P'

    else:
        flag = 'S'

    return sequenceNumber, checkSum, flag


def createServerHeader(acknowledgementNumber: int, checkSum: int, windowSize: int) -> bytes:
    return struct.pack('!LHH', acknowledgementNumber, checkSum, windowSize)


def parseServerHeader(octets: bytes) -> tuple:
    acknowledgementNumber, checkSum, windowSize = struct.unpack('!LHH', octets)
    return acknowledgementNumber, checkSum, windowSize


def readSegment(fileDescriptor: IO) -> bytes:
    while True:
        data = fileDescriptor.read(MAX_SEGMENT)
        if not data:
            break
        yield data


def readNSegments(fileDescriptor, n: int) -> List[bytes]:
    return [item for item in itertools.islice(readSegment(fileDescriptor), n)]


def addWithCarry(a: int, b: int) -> int:
    c: int = a + b
    return (c & 0xFFFF) + (c >> 16)


def calculateCheckSum(octets: bytes) -> int:
    checkSum: int = 0

    if len(octets) & 1:
        octets += bytes(1)

    nums: tuple = struct.unpack_from('!%dH' % (len(octets) >> 1), octets)

    for num in nums:
        checkSum = addWithCarry(checkSum, num)

    return ~checkSum & 0xFFFF


def verifyCheckSum(octets) -> bool:
    return not calculateCheckSum(octets)
