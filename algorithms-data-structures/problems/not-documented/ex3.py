def determinant(a):
    return  (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
           - a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
           + a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]))

with open('input.in', 'r') as fichier:
    n = int(fichier.readline())
    P = []
    for _ in range(n):
        line = fichier.readline()
        P.append([int(x) for x in line.split()])
    X = [int(x) for x in fichier.readline().split()]

    exterior = False
    for index in range(0, len(P) - 1):
        p = P[index]
        q = P[index + 1]
        r = X
        orientare = [[1, 1, 1], [p[0], r[0], q[0]], [p[1], r[1], q[1]]]
        if (determinant(orientare) == 0):
            exterior = None
        elif exterior is not None and determinant(orientare) > 0:
            exterior = True
    p = P[0]
    q = P[len(P) - 1]
    r = X
    orientare = [[1, 1, 1], [p[0], r[0], q[0]], [p[1], r[1], q[1]]]
    
    if (determinant(orientare) == 0):
        exterior = None
    elif exterior is not None and determinant(orientare) > 0:
        exterior = True

    if (exterior is None):
        print ('Pe latură')
    elif (exterior == True):
        print ('Exterior')
    else:
        print ('Interior')