def determinant(a):
    return  (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
           - a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
           + a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]))

def orientare(p, r, q):
    orientare = [[1, 1, 1], [p[0], r[0], q[0]], [p[1], r[1], q[1]]]
    return determinant(orientare)

with open('input.in', 'r') as fichier:
    n = int(fichier.readline())
    P = []
    for _ in range(n):
        line = fichier.readline()
        P.append([int(x) for x in line.split()])
    X = [int(x) for x in fichier.readline().split()]

    s = 0
    d = len(P) - 1
    while len(P) > 3:
        print (P)
        p = P[0]
        q = P[d // 2 + 1]
        r = X

        # Stânga
        if orientare(p, r, q) > 0:
            d = d // 2 + 1
            P = P[: d + 1]
        # Dreapta
        else:
            s = (s + d) // 2
            P = [P[0]] + P[s :]
    A = P[0]
    B = P[1]
    C = P[2]    

    # https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
    d1 = orientare(A, B, X)
    d2 = orientare(B, C, X)
    d3 = orientare(C, A, X)

    has_neg = (d1 < 0) or (d2 < 0) or (d3 < 0);
    has_pos = (d1 > 0) or (d2 > 0) or (d3 > 0);

    if not (has_neg and has_pos):
        print ('Interior')
    else:
        print ('Exterior')