# https://www.csacademy.com/contest/interview-archive/task/array-intersection/submissions/

def array_intersection(a1, a2):
    d1 = dict()
    d2 = dict()
    a = list()
    
    for elem in a1:
        if elem not in d1:
            d1[elem] = 1
        else:
            d1[elem] += 1

    for elem in a2:
        if elem not in d2 and elem in d1:
            d2[elem] = 1
        elif elem in d2:
            d2[elem] += 1

    for elem in d2:
        a.extend([elem] * (min(d1[elem], d2[elem])))
    
    print (len(a))
    return a

a = [int(x) for x in input().split()]
b = [int(x) for x in input().split()]

print (array_intersection(a, b));