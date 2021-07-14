# https://codeforces.com/contest/580/problem/B

n, d = [int(x) for x in input().split()]
s = []

while (n):
    s.append([int(x) for x in input().split()])
    n -= 1


s = sorted(s, key=lambda x: x[0], reverse=True)
st = 0
suma = 0
maxim = -1
for dr in range(len(s)):
    suma += s[dr][1]
    while (abs(s[st][0] - s[dr][0]) >= d):
        suma -= s[st][1]
        st += 1
    if (suma > maxim):
        maxim = suma

print (maxim)
