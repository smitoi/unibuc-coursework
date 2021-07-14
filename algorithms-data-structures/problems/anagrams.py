# https://csacademy.com/contest/archive/task/anagrams

n = int(input())
lit = dict()

while (n):
    cuv = input()
    cuv = ''.join(sorted(cuv))
    if (cuv in lit):
        lit[cuv] += 1
    else:
        lit[cuv] = 1
    n -= 1
    
maxim = -1
for val in lit:
    if (lit[val] > maxim):
        maxim = lit[val]

print (maxim)