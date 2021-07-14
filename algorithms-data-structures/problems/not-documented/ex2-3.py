with open('input.in', 'r') as fichier:
    n = int(fichier.readline())
    S = []
    for _ in range(n):
        line = fichier.readline()
        s = [int(x) for x in line.split()]
        
        if s[0]:
            s[2] = -s[2] / s[0]
        else:
            s[2] = -s[2] / s[1]

        S.append(s)

    X = [int(x) for x in line.split()]

    min_x = min_y = float('inf')
    max_x = max_y = float('-inf')

    for s in S:
        x, y, z = s

        c = z
        if x != 0:
            if max_x < z <= X[0]:
                max_x = z
            elif min_x > z >= X[0]:
                min_x = z
        else:
            if max_y < z <= X[1]:
                max_y = z
            elif min_y > z >= X[1]:
                min_y = z

    if min_x == float('inf') or max_x == float('-inf') or min_y == float('inf') or max_y == float('-inf'):
        print ('Nici un dreptunghi găsit după condiția dată.')
    else:
        lungime = max_x - min_x
        latime = max_y - min_y
        print (f'Dreptunghiul minim are aria {lungime * latime}')