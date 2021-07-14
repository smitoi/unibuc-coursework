aux = input()
p = [0] * len(aux)

for index in range(len(aux)):
	if aux[index] == '(':
		p[index] = 1
	else:
		p[index] = -1

q = int(input())

while (q):
    st, dr = [int(x) for x in input().split()]
    
    par = 0
    aux = 0
    for index in range(st - 1, dr):
        if (p[index] == 1):
            aux += 1
        elif (p[index] == -1 and aux > 0):
            par += 2
            aux -= 1
    print (par)
    q -= 1