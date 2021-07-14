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

with open('input.in', 'r') as fichier:
    n = int(fichier.readline())
    P = []
    for _ in range(n):
        line = fichier.readline()
        P.append([int(x) for x in line.split()])
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
    print (L)