def determinant(a):
    return  (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
           - a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
           + a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]))

with open('input.in', 'r') as fichier:
    p = [int(x) for x in fichier.readline().split()]
    r = [int(x) for x in fichier.readline().split()]
    q = [int(x) for x in fichier.readline().split()]
    orientare = [[1, 1, 1], [p[0], r[0], q[0]], [p[1], r[1], q[1]]]
    if (determinant(orientare) == 0):
        print ('coliniare')
    elif (determinant(orientare) > 0):
        print ('în stânga')
    else:
        print ('în dreapta')

