def determinant(a):
    return  (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
           - a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
           + a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]))


def intersects(a, c, b):
    if min(a[1], b[1]) > c[1] or max(a[1], b[1]) < c[1]:
        return False
    else:
        return True

with open('input.in', 'r') as fichier:
    def supremum(a, b):
        if a[1] == b[1]:
            return a[0] <= b[0]

        return a[1] <= b[1]

    def onSegment(a, b, c):
        return max(a[0], b[0]) >= c[0] >= min(a[0], b[0]) and max(a[1], b[1]) >= c[1] >= min(a[1], b[1]) and not determinant([a + [1], b + [1], c + [1]])

    n = int(fichier.readline())
    P = []
    for _ in range(n):
        line = fichier.readline()
        P.append([int(x) for x in line.split()])

    X = [int(x) for x in fichier.readline().split()]

    count = 0

    for index in range(0, len(P)):
        current = P[index % n]
        next = P[(index + 1) % n]

        if onSegment(current, next, X):
            count = None
            break

        if intersects(current, X, next):
            if X[0] < max(next[0], current[0]) and \
                ((determinant([current + [1], next + [1], X + [1]]) > 0 and supremum(current, next)) \
                    or (determinant([current + [1], next + [1], X + [1]]) < 0 and supremum(next, current))):
                count += 1

    if (count is None):
        print ('Pe latură')
    elif (count % 2 == 0):
        print ('Exterior')
    else:
        print ('Interior')