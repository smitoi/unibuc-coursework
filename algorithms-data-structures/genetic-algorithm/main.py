from random import choices, uniform, shuffle, randint, random
from math import log2
from tabulate import tabulate
from bisect import bisect_left
from copy import deepcopy
import sys, os

# Disable print
def block_print():
    sys.stdout = open(os.devnull, 'w', encoding='utf-8')

# Restore print
def enable_print():
    sys.stdout = sys.__stdout__

class Color:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Population:
    def __init__(self):
        self.genomes = []

    # Generate initial population
    def initial_population(self, size, length):
        # Generăm o populație de mărime size unde fiecare cromozom are lungimea length
        self.genomes = []
        for _ in range(size):
            self.genomes.append(Genome(length))
        self.calculate_probabilities()

    # Calculates the array of probabilities for each genome
    def calculate_probabilities(self):
        # Calculăm intervalele de probabilități
        self.probabilities = [0]
        function_sum = sum(_.function for _ in self.genomes)

        for index, genome in enumerate(self.genomes):
            probability = genome.function / function_sum
            self.genomes[index].probability = probability
            self.probabilities.append(self.probabilities[-1] + probability)
        # Din cauza erorilor de tip floating point a trebuit să setez ultimul element la 1
        self.probabilities[-1] = 1
    
    # Show probabilities array
    def show_probabilities(self):
        out = f'Intervalele de {Color.OKBLUE}probabilitate{Color.ENDC} calculate: '
        if first_generation:
            print (out)
            print (self.probabilities)
        if output is not None and (first_generation or debug_file):
            output_file.write(out + '\n')
            output_file.write(str(self.probabilities) + '\n')
    
    # Prints the genome in a tabular manner
    def genomes_tabular_data(self):
        return (tabulate([[X.genes, X.decimal, X.function, X.probability] \
                for index, X in enumerate(self.genomes)], \
                headers=[f"{Color.OKBLUE}ID{Color.ENDC}", f"{Color.OKBLUE}Gene{Color.ENDC}", f"{Color.OKBLUE}Valore x{Color.ENDC}", f"{Color.OKBLUE}Valoare f(x){Color.ENDC}", f"{Color.OKBLUE}Probabilitate{Color.ENDC}"],\
                showindex="always"))
    
    # Select the population
    def select_population(self, n):
        population_ = Population()
        # Selectăm o populație de n indivizi
        for index in range(n):
            u = random()
            p = bisect_left(self.probabilities, u)
            out = 'u = ' + Color.OKGREEN + str(u) + Color.ENDC + ' => selectăm cromozomul ' + Color.OKGREEN + str(p - 1) + Color.ENDC
            if first_generation:
                print (out)
            if output is not None and (first_generation or debug_file):
                output_file.write(out + '\n')
            population_.genomes.append(self.genomes[p - 1])
        return population_

    # Crossover
    def crossover(self, n):
        # Etapa de recombinare, alegem din indivizii selectați pe cei pe care îi vom recombina
        selected = []
        population__ = deepcopy(self)
        out = Color.OKGREEN + 'Probabilitate de încrucișare ' + Color.ENDC + str(pr)

        if first_generation:
            print (out)
        if output is not None and (first_generation or debug_file):
            output_file.write(out + '\n')

        for index, genome in enumerate(self.genomes):
            u = random()
            if u < pr:
                out = 'Selectat cromozomul ' + Color.FAIL + str(index) + Color.ENDC
                if first_generation:
                    print (out)
                if output is not None and (first_generation or debug_file):
                    output_file.write(out + '\n')
                selected.append(index)
        shuffle(selected)

        # Recombinăm câte 2
        while len(selected) > 1 and len(selected) != 3:
            m = selected.pop()
            t = selected.pop()

            # Putem să punem primii biți de la cromozonul mai mare și ceilalți de la cel mai mic
            # if population__.genomes[m].function > population__.genomes[t].function:
            #     m, t = t, m

            k = randint(0, l)
            out = 'Combinare cromozom ' + Color.WARNING + str(m) + Color.ENDC + ' cu cromozom ' + Color.WARNING + str(t) + Color.ENDC + ' în punctul de rupere k = ' + str(k)
            if first_generation:
                print (out)
            if output is not None and (first_generation or debug_file):
                output_file.write(out + '\n')
            population__.genomes[m].genes = self.genomes[m].genes[: k] + self.genomes[t].genes[k :]
            population__.genomes[t].genes = self.genomes[t].genes[: k] + self.genomes[m].genes[k :]
            population__.genomes[m].update()
            population__.genomes[t].update()
            if first_generation or (output is not None and debug_file):
                tabel = tabulate([[str(m), self.genomes[m].genes], \
                                [str(t), self.genomes[t].genes], \
                                [str(m) + '/' + str(t), population__.genomes[m].genes], \
                                [str(t) + '/' + str(m), population__.genomes[t].genes]], \
                                headers=[f"{Color.OKBLUE}Cromozom{Color.ENDC}", f"{Color.OKBLUE}Gene{Color.ENDC}"])
            if first_generation:
                print (tabel)
            if output is not None and (first_generation or debug_file):
                output_file.write(tabel + '\n')

        # Dacă la final rămân 3, îi recombinăm între ei
        if len(selected) == 3:
            [x, y, z] = selected
            k = randint(0, l)
            k_ = randint(k, l)
            out = 'Combinare triplă cromozom ' + Color.WARNING + str(x) + Color.ENDC + ' cu cromozom ' + Color.WARNING + str(y) + Color.ENDC + ' și ' + Color.WARNING + str(z) + Color.ENDC + ' în punctul de rupere k = ' + str(k) + ", k' = " + str(k_)
            if first_generation:
                print (out)
            if output is not None and (first_generation or debug_file):
                output_file.write(out + '\n')
            population__.genomes[x].genes = self.genomes[x].genes[: k] + self.genomes[y].genes[k : k_] + self.genomes[z].genes[k_ :]
            population__.genomes[y].genes = self.genomes[y].genes[: k] + self.genomes[z].genes[k : k_] + self.genomes[x].genes[k_ :]
            population__.genomes[z].genes = self.genomes[z].genes[: k] + self.genomes[x].genes[k : k_] + self.genomes[y].genes[k_ :]
            population__.genomes[x].update()
            population__.genomes[y].update()
            population__.genomes[z].update()
            if first_generation or (output is not None and debug_file):
                tabel = tabulate([[str(x), self.genomes[x].genes], \
                                [str(y), self.genomes[y].genes], \
                                [str(z), self.genomes[z].genes], \
                                [str(x) + '/' + str(y) + '/' + str(z), population__.genomes[x].genes], \
                                [str(y) + '/' + str(z) + '/' + str(x), population__.genomes[y].genes], \
                                [str(z) + '/' + str(x) + '/' + str(y), population__.genomes[z].genes]], \
                                headers=[f"{Color.OKBLUE}Cromozom{Color.ENDC}", f"{Color.OKBLUE}Gene{Color.ENDC}"])
            if first_generation:
                print (tabel)
            if output is not None and (first_generation or debug_file):
                output_file.write(tabel + '\n')
        return population__

    # Mutation
    def mutation(self, mode):
        # Mutația rară
        if mode == 'hard':
            for index, genome in enumerate(self.genomes):
                u = random()
                if u < pm:
                    for jndex in self.genomes[index].genes:
                        self.genomes[index].genes[jndex] = self.genomes[index].genes[jndex] ^ 1
                        self.genomes[index].update()
        # Mutația deasă
        elif mode == 'soft':
            for index, genome in enumerate(self.genomes):
                u = random()
                if u < pm:
                    for jndex in self.genomes[index].genes:
                        u = random()
                        if u < pm:
                            self.genomes[index].genes[jndex] = self.genomes[index].genes[jndex] ^ 1
                            self.genomes[index].update()
    
    def flip(self):
        for index, genome in enumerate(self.genomes):
            u = random()
            if u < pflip:
                k = randint(0, l - 1)
                k_ = randint(k, l - 1)
                # print (f'A avut loc flip cu {k} si {k_}')
                # print (self.genomes[index].genes)
                start = k
                stop = k_
                while start < stop:
                    self.genomes[index].genes[start], self.genomes[index].genes[stop] = self.genomes[index].genes[stop], self.genomes[index].genes[start]
                    start += 1
                    stop -= 1
                self.genomes[index].update()
                # print (self.genomes[index].genes)
                # input()
                    


    # Get the best element
    def function_maximum(self):
        # Găsim elementul cu cel mai bun fitness
        maximum = a
        max_index = -1
        x = 0

        for index, genome in enumerate(self.genomes):
            if genome.function > maximum:
                maximum = genome.function
                max_index = index
                x = genome.decimal
        
        return [max_index, maximum, x]

    # Mean performance value
    def mean_performance_value(self):
        # Performanța medie a populației actuale
        suma = 0
        for genome in self.genomes:
            suma += genome.function
        return round(suma / len(self.genomes), p)

class Genome:
    # Initialises a genome
    def __init__(self, length):
        self.genes = choices([0, 1], k = length)
        self.decimal = self.to_decimal()
        self.function = self.calc_func()
    
    # Converts a genome to decimal
    def to_decimal(self):
        X = 0.0
        acc = 1

        for gene in reversed(self.genes):
            X += acc * gene
            acc *= 2

        # Se folosește formula din curs
        self.decimal = round((X * ((b - a) / (2 ** l - 1)) + a), p)
        return self.decimal
    
    # Function
    def calc_func(self):
        # Se calculează funcția de fitness în funcție de funcția dată ca input
        self.function = round(f(self.decimal), p)
        return self.function
    
    # Updates the values contained in the genome
    def update(self):
        self.to_decimal()
        self.calc_func()

filename = 'input.in' # Fișier de output
debug_iteration = False # Se va opri la fiecare iterație
debug_file = False # Dacă vrem tot ouput-ul în fișier
want_keyboard = False # Se va afișa doar în terminal, cu posibilitatea de a continua programul prin mutație forțată
output = 'Exercițiu.txt' # Fișierul de output

# Dacă vrem afișare la terminal, nu vrem să afișăm în fișier
if want_keyboard == True:
    output = None

# Eliminăm culorile dacă afișăm în fișier
if output is not None:
    Color.HEADER = ''
    Color.OKBLUE = ''
    Color.OKCYAN = ''
    Color.OKGREEN = ''
    Color.WARNING = ''
    Color.FAIL = ''
    Color.ENDC = ''
    Color.BOLD = ''
    Color.UNDERLINE = ''
    output_file = open(output, 'w', encoding='utf-8')

# Inițializarea
try:
    input_file = open(filename)
except IOError:
    print (f'{Color.FAIL}[x] {Color.ENDC} Nu s-a dat un fișier valid de intrare.')
else:
    with input_file:
        d = int(input_file.readline()) # Dimensiunea populației
        [a, b] = [int(x) for x in input_file.readline().split()] # Domeniul de definiție al funcției
        [m, n, o] = [int(x) for x in input_file.readline().split()] # Parametrii funcției
        # f = lambda x : m * x ** 2 + n * x + o
        f = lambda x : x ** 3 + 3 * x ** 2 - 4 * x + 7
        p = int(input_file.readline()) # Precizia
        l = int(log2((b - a) * 10 ** p)) + 1 # Dimensiunea unui cromozom
        pr = float(input_file.readline()) # Probabilitate recombinare
        pm = float(input_file.readline()) # Probabilitate mutație
        steps = int(input_file.readline()) # Pași
        pflip = 0.05

        print (f'{Color.HEADER}Datele citite din fișier:{Color.ENDC}')
        print (f'{Color.OKCYAN}Dimensiunea populației:{Color.ENDC} {d}')
        print (f'{Color.OKCYAN}Domeniul de definiție al funcției:{Color.ENDC} [{a}, {b}]')
        print (f'{Color.OKCYAN}Funcția:{Color.ENDC} ({m} * x ** 2) + ({n} * x) + ({o})')
        print (f'{Color.OKCYAN}Domeniul de definiție al funcției:{Color.ENDC} [{a}, {b}]')
        print (f'{Color.OKCYAN}Precizia:{Color.ENDC} {p} => {Color.OKCYAN}cromozomi de dimensiune{Color.ENDC} {l}')
        print (f'{Color.OKCYAN}Probabilitatea de recombinare:{Color.ENDC} {pr}')
        print (f'{Color.OKCYAN}Probabilitatea de mutație:{Color.ENDC} {pm}')
        print (f'{Color.OKCYAN}Numărul de generații:{Color.ENDC} {steps}')
    
    # Generăm populația inițială și calculăm intervalele de probabilități
    population = Population()
    population.initial_population(d, l)
    first_generation = True
    last_maximum = -1
    print (f'{Color.OKBLUE}[?]{Color.ENDC} Begin?')
    input()

    # Pentru fiecare etapă
    for step in range(steps):
        # Afișăm populația inițială
        tabel = population.genomes_tabular_data()
        out = 'Populatia initiala:'
        if (first_generation):
            print (out)
            print (tabel)
        if output is not None and (first_generation or debug_file):
            output_file.write (out + '\n')
            output_file.write (tabel + '\n')
        population.show_probabilities()

        # Selectăm indivizi, lăsând loc liber pentru cel elitist, generăm P'
        population_ = population.select_population(d - 1)
        out = 'După selecție, P\':'
        tabel = population_.genomes_tabular_data()
        if (first_generation):
            print (out)
            print (tabel)
        if output is not None and (first_generation or debug_file):
            output_file.write (out + '\n')
            output_file.write (tabel + '\n')

        # Etapa de crossover, recombinăm și generăm P''
        population__ = population_.crossover(d - 1)
        out = 'După combinare, P\'\': '
        tabel = population__.genomes_tabular_data()
        if (first_generation):
            print (out)
            print (tabel)
        if output is not None and (first_generation or debug_file):
            output_file.write (out + '\n')
            output_file.write (tabel + '\n')

        # Mutația are loc, am lăsat-o ca fiind cea rară
        population__.mutation('soft')
        population__.flip()

        # Luăm maximul din populația P și îl inserăm în P''
        [index, maximum, x] = population.function_maximum()
        population__.genomes.insert(randint(0, l - 2), population.genomes[index])

        # P devine P'', calculăm perfomranța
        population = deepcopy(population__)
        mean = population.mean_performance_value()
        population.calculate_probabilities()

        # Output
        if last_maximum == maximum:
            out = f'{Color.WARNING}[=] {Color.ENDC}'
            print (out, end='')
            if output is not None:
                output_file.write(out)
        elif last_maximum < maximum:
            out = (f'{Color.OKGREEN}[+] {Color.ENDC}')
            print (out, end='')
            if output is not None:
                output_file.write(out)
        else:
            out = f'{Color.FAIL}[x] {Color.ENDC}'
            print (out, end='')
            if output is not None and (first_generation or debug_file):
                output_file.write(out + '\n')
            out = f' S-a încălcat criteriul elitist cu {maximum} și {last_maximum}.'
            print (out)
            if output is not None:
                output_file.write(out + '\n')
            break
        last_maximum = maximum
        out = 'Maximul este ' + str(maximum) + ', performanța medie este ' + str(mean) + ' pentru x = ' + str(x)
        print ('Maximul este ' + str(maximum) + ', performanța medie este ' + str(mean) + ' pentru x = ' + str(x))
        if output is not None:
            output_file.write(out + '\n')

        try:
            pm_
        except NameError:
            pass
        else:
            pm = pm_
            del pm_

        if (first_generation):
            input()

        # Dacă performanța medie e egală cu maximul, putem să facem o mutație forțată
        if maximum == mean and step != steps - 1 and output is None and want_keyboard is True:
            print (f'{Color.FAIL}[x]{Color.ENDC} Performanța a egalat maximul.')
            choice = None
            while choice not in ['y', 'ye', 'yes', 'n', 'no']:
                print (f'{Color.OKBLUE}[?]{Color.ENDC} Încheiem prematur programul? Mai avem {steps - step} generații (yes / no) ')
                choice = input().strip().lower()
            if choice in ['y', 'ye', 'yes']:
                break
            else:
                print (f'{Color.WARNING}[!]{Color.ENDC} Continuăm, dar generăm o serie nouă de cromozomi prin mutații \'forțate\'.')
                pm_ = pm
                pm = max(pm, 0.75)
                input()
    
        first_generation = debug_iteration

    [index, maximum] = population.function_maximum()
    out = 'Maximul final este ' + str(maximum)
    print (out)
    if output is not None:
        output_file.write(out + '\n')
