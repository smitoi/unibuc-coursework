# https://csacademy.com/contest/interview-archive/task/Bounded-offset-sorting/statement/

from heapq import *
def bounded_offset_sorting(array, m):
    array_s = list()
    heap = array[: m + 1]
    heapify(heap)
    
    for i in range(m + 1, len(array)):
        array_s.append(heappop(heap))
        heappush(heap, array[i])
    
    for i in range(len(heap)):
        array_s.append(heappop(heap))
    return array_s

n, m = [int(x) for x in input().split()]
array = [int(x) for x in input().split()]
print (bounded_offset_sorting(array, m))