def monotonie(n, P, a, b, c):
    localMins = 0

    for index in range(n):
        M = a * P[(index - 1) % n][0] + b * P[(index - 1) % n][1]
        N = a * P[index][0] + b * P[index][1]
        O = a * P[(index + 1) % n][0] + b * P[(index + 1) % n][1]

        if N < M and N <= O:
            localMins += 1
    
    if localMins == 1:
        print (f'Este monoton după {a} * x + {b} * y = {c}')
    else:
        print (f'Nu este monoton după {a} * x + {b} * y = {c}')

with open('input.in', 'r') as fichier:
    n = int(fichier.readline())
    P = []
    for _ in range(n):
        line = fichier.readline()
        P.append([int(x) for x in line.split()])

    monotonie(n, P, 1, 0, 0)
    monotonie(n, P, 0, 1, 0)