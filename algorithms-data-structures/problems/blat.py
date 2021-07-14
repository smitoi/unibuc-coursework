# https://www.infoarena.ro/problema/blat

input = open('blat.in')
linie = [int(x) for x in input.readline().split(' ')]
nr_probleme_propuse = linie[0]
nr_probleme_alese = linie[1]
nr_studenti = linie[2]
matrice = []
punctaj_total_maxim = 0
punctaj_total_minim = 0
punctaj_student_maxim = -1
punctaj_student_minim = -1
punctaj_probleme = [0] * nr_probleme_propuse

for index in range(nr_studenti):
    linie = [int(x) for x in input.readline().split(' ')]
    matrice.append(linie)

for index in range(nr_studenti):
    punctaj_actual_minim = sum(sorted(matrice[index])[0 : nr_probleme_alese])
    punctaj_actual_maxim = sum(sorted(matrice[index], reverse=True)[0 : nr_probleme_alese])
    
    for jndex in range(len(matrice[index])):
        punctaj_probleme[jndex] += matrice[index][jndex]
	
    if (punctaj_actual_minim < punctaj_student_minim) or punctaj_student_minim == -1:
        punctaj_student_minim = punctaj_actual_minim
	
    if (punctaj_actual_maxim > punctaj_student_maxim) or punctaj_student_maxim == -1:
        punctaj_student_maxim = punctaj_actual_maxim
	
out = open('blat.out', 'w')
out.write (str(sum(sorted(punctaj_probleme, reverse=True)[0 : nr_probleme_alese])))
out.write('\n')
out.write (str(sum(sorted(punctaj_probleme)[0 : nr_probleme_alese])))
out.write('\n')
out.write (str(punctaj_student_maxim))
out.write('\n')
out.write (str(punctaj_student_minim))