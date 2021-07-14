from math import sqrt

def determinant(a):
    return  (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
           - a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
           + a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]))

def nu_determina_viraj(L):
    p = L[len(L) - 1]
    r = L[len(L) - 2]
    q = L[len(L) - 3]
    orientare = [[1, 1, 1], [p[0], r[0], q[0]], [p[1], r[1], q[1]]]
    if (determinant(orientare) < 0):
        return False
    else:
        return True

def distanta(P, R):
    return sqrt ((R[0] - P[0]) ** 2 + (R[1] - P[1]) ** 2)

with open('input.in', 'r') as fichier:
    n = int(fichier.readline())
    P = []
    for _ in range(n):
        line = fichier.readline()
        P.append([int(x) for x in line.split()])
    P_ = P
    L = [P[0], P[1]]
    P = P[2 : ]

    for point in P:
        L.append(point)
        while len(L) > 2 and nu_determina_viraj(L):
            penultim = len(L) - 2
            L = L[ : penultim] + L[penultim + 1 :]
    if len(L) > 2 and nu_determina_viraj([L[len(L) - 2], L[len(L) - 1], L[0]]):
        penultim = len(L) - 1
        L = L[ : penultim] + L[penultim + 1 :]
    if len(L) > 2 and nu_determina_viraj([L[len(L) - 1], L[0], L[1]]):
        penultim = 0
        L = L[ : penultim] + L[penultim + 1 :]

    R = []
    P = []
    for point in P_:
        if point not in L:
            R.append(point)
        else:
            P.append(point)
    
    while len(R):
        minim = float('+inf')
        min_tup = []

        for r in R:
            for index in range(len(P) - 1):
                i = P[index]
                j = P[index + 1]

                dist = distanta(i, r) + distanta(r, j) - distanta(i, j)
                tup = (i, j, r)

                if dist < minim:
                    minim = dist
                    min_tup = [tup]
                elif dist == minim:
                    min_tup.append(tup)
        
        minim = float('+inf')
        best_tup = None
        for tup in min_tup:
            i, j, r = tup
            dist = (distanta(i, r) + distanta(r, j)) / distanta(i, j)

            if dist < minim:
                best_tup = tup
                minim = dist
        
        i, j, r = best_tup
        for index in range(len(P) + 1):
            if P[index] == i and P[index + 1] == j:
                P.insert(index + 1, r)
                break
        R.remove(r)
    print (P)


