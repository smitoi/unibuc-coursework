# https://csacademy.com/contest/interview-archive/task/four-x-tremes/

def four_xtremes(a, b, c, d):
    a = [a, b, c, d]
    a.sort()
    return max(abs(a[0] - a[1]), max(abs(a[1] - a[2]), max(abs(a[2] - a[3]), abs(a[3] - a[0]))))

a = int(input())
b = int(input())
c = int(input())
d = int(input())
print (four_xtremes(a, b, c, d))