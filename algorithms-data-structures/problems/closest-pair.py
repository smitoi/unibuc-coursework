# https://csacademy.com/contest/interview-archive/task/closest-pair/

def closest_pair(first, second):
    first.sort()
    second.sort()
    i = j = 0
    val = -1
    while i < n and j < n:
        if abs(first[i] - second[j]) == 0:
            return 0
        if (val == -1):
            val = abs(first[i] - second[j])
        else:
            val = min(val, abs(first[i] - second[j]))
        if first[i] > second[j]:
            j += 1 
        else:
            i += 1 
    return val

n = int(input())
first = list(map(int, input().split(' ')))
second = list(map(int, input().split(' ')))
answer = closest_pair(first, second)
print(answer)