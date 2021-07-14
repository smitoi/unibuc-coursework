import numpy as np

def determinant(a):
    return  (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
           - a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
           + a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]))

def positionCircle(X, Y, Z, P):
    if determinant([X + [1], Y + [1], Z + [1]]) < 0:
        X, Z = Z, X

    det = np.linalg.det(np.array([
        [X[0], X[1], X[0] ** 2 + X[1] ** 2, 1],
        [Y[0], Y[1], Y[0] ** 2 + Y[1] ** 2, 1],
        [Z[0], Z[1], Z[0] ** 2 + Z[1] ** 2, 1],
        [P[0], P[1], P[0] ** 2 + P[1] ** 2, 1]]))
    
    if -1e-8 < det < 1e-8:
        print ('Pe cerc')
    elif det < 0:
        print ('Exterior')
    else:
        print ('Interior')
        return True
    
    return False

def isIllegal(X, Y, Z, P):
    positionCircle(X, Y, Z, P) or positionCircle(Y, Z, P, X)

with open('input.in', 'r') as fichier:
    X = [int(x) for x in fichier.readline().split()]
    Y = [int(y) for y in fichier.readline().split()]
    Z = [int(z) for z in fichier.readline().split()]
    P = [int(p) for p in fichier.readline().split()]

    # Exercițiul 3
    positionCircle(X, Y, Z, P)

    # Exercițiul 4
    isIllegal(X, Y, Z, P)

    


