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

    min_x = min_y = float('-inf')
    max_x = max_y = float('inf')

    for s in S:
        x, y, z = s

        c = z
        if x != 0:
            if x > 0:
                max_x = min(max_x, c)
            else:
                min_x = max(min_x, c)
        else:
            if y > 0:
                max_y = min(max_y, c)
            else:
                min_y = max(min_y, c)

    if min_x > max_x or min_y > max_y:
        print ('Intersecție vidă')
    else:
        print ('Intersecție nevidă')

        if max_x == float('+inf') or max_y == float('+inf') or min_x == float('-inf') or min_y == float('-inf'):
            print ('Este intersecție nemărginită')
        else:
            print ('Este intersecție mărginită')