# https://csacademy.com/contest/archive/task/dominoes/statement/

n, k = [int(x) for x in input().split()]
nums = [int(x) for x in input().split()]
maxim = k

st = 0
dr = 0
while dr < n:
    suma = nums[dr] - nums[st] - 1 - (dr - st - 1)
    if (suma > k):
        st += 1
    else:
        dom = nums[dr] - nums[st]
        if (dom + k - suma > maxim):
            maxim = dom + k - suma
        dr += 1
        
print (maxim + 1)