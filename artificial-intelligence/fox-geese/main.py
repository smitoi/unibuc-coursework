import pygame
import sys

from argparse import ArgumentParser
from copy import deepcopy
from time import time, sleep
from statistics import mean, median

WINDOW_SIZE = 700
GRID_SIZE = 96
OFFSET = 2

BACKGROUND_COLOR = (255, 251, 255)
SELECTED_COLOR = (241, 218, 191)
GEESE_COLOR = (86, 56, 36)
FOX_COLOR = (152, 68, 71)
BLACK_COLOR = (0, 0, 0)

GEESE_TURN = 0
FOX_TURN = 1
IS_FINAL = False

PLAYER_TURN = 'P'
COMPUTER_TURN = 'C'

MAX_DEPTH = 4
ALGORITHM = 'min_max'

COMPUTER_GAME = False

GLOBAL_LIST_TIME = []

GLOBAL_LIST_NODES = []
GLOBAL_CURRENT_NODES = 0

GLOBAL_START = time()
GLOBAL_END = 0
GLOBAL_MOVES = 0

class GameState:
    def __init__(self, turn, configuration, level):
        self.turn = turn
        self.configuration = configuration
        self.level = level

    def getNextStates(self):
        configurations = []

        searched = 'G' if self.turn == GEESE_TURN else 'F'
        nextTurn = GEESE_TURN if self.turn == FOX_TURN else FOX_TURN

        for index in range(len(self.configuration)):
            for jndex in range(len(self.configuration[index])):
                if self.configuration[index][jndex] == searched:
                    possiblePos = [(0, 1), (1, 0), (0, -1), (-1, 0)]
                    if index % 2 == jndex % 2:
                        possiblePos.extend([(1, 1), (1, -1), (-1, 1), (-1, -1)])

                    if self.turn == FOX_TURN:
                        possiblePos.extend([(0, 2), (2, 0), (0, -2), (-2, 0)])
                        if index % 2 == jndex % 2:
                            possiblePos.extend([(2, 2), (2, -2), (-2, 2), (-2, -2)])

                    for pos in possiblePos:
                        try:
                            posX = jndex + pos[0]
                            posY = index + pos[1]

                            posX_ = jndex + pos[0] // 2
                            posY_ = index + pos[1] // 2

                            if pos in [(2, 2), (2, -2), (-2, 2), (-2, -2), (0, 2), (2, 0), (0, -2), (-2, 0)]:
                                takePiece = True
                            else:
                                takePiece = False

                            if posX < 0 or posY < 0 or posX_ < 0 or posY_ < 0:
                                raise IndexError

                            if not takePiece and self.configuration[posY][posX] == '.':
                                newConfig = deepcopy(self.configuration)
                                newConfig[index][jndex] = '.'
                                newConfig[posY][posX] = searched
                                configurations.append(GameState(not nextTurn, newConfig, self.level - 1))
                            elif self.configuration[posY_][posX_] == 'G' and self.configuration[posY][posX] == '.':
                                newConfig = deepcopy(self.configuration)
                                newConfig[index][jndex] = '.'
                                newConfig[posY_][posX_] = '.'
                                newConfig[posY][posX] = searched
                                configurations.append(GameState(not nextTurn, newConfig, self.level - 1))
                        except IndexError:
                            continue
        return configurations

    # Dacă vulpea nu mai are nici o mutare
    def noFoxMoves(self):
        (jndex, index) = Game.getFoxPos(self.configuration)

        possiblePos = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        takePos = [(2, 0), (-2, 0), (0, 2), (0, -2)]

        # print (f'Poziția vulpii {index}, {jndex}')
        if index % 2 == jndex % 2:
            possiblePos.extend([(1, 1), (1, -1), (-1, 1), (-1, -1)])
            takePos.extend([(2, 2), (2, -2), (-2, 2), (-2, -2)])

        for pos, tpos in zip(possiblePos, takePos):
            try:
                if jndex + pos[1] < 0 or index + pos[0] < 0 or jndex + tpos[0] < 0 or index + tpos[1] < 0:
                    raise IndexError
                if self.configuration[jndex + pos[1]][index + pos[0]] == '.':
                    # print (f'Vulpea poate muta pe {jndex + pos[1]} {index + pos[0]}')
                    return True
                elif self.configuration[jndex + pos[0]][index + pos[1]] == 'G' and self.configuration[jndex + tpos[0]][index + tpos[1]] == '.':
                    # print (f'Vulpea poate lua pe pe {jndex + pos[1]} {index + pos[0]}')
                    return True
            except IndexError:
                continue
        
        return False

    def isFinal(self):
        geese = 0

        # dacă sunt mai puțin de 4 gâște
        for row in self.configuration:
            for elem in row:
                if elem == 'G':
                    geese += 1
        
        if self.turn == GEESE_TURN and geese < 4:
            print ('Vulpea a câștigat')
            return True
        # sau vulpea nu mai are nici o mutare
        elif self.turn == FOX_TURN and self.noFoxMoves() == 0:
            print ('Gâștele au câștigat')
            return True

        return False

    def getScore(self):
        score = 0
        (jndex, index) = Game.getFoxPos(self.configuration)

        possiblePos = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        if index % 2 == jndex % 2:
            possiblePos.extend([(1, 1), (1, -1), (-1, 1), (-1, -1)])

        if self.turn == FOX_TURN and COMPUTER_GAME:
            # For each goose left on the table we do -1
            # Din moment ce vulpea este max, am calculat în așa fel încât fiecare gâscă care se află pe tablă să fie un dezavantaj
            for row in self.configuration:
                for elem in row:
                    if elem == 'G':
                        score -= 1
        else:
            # For each position that is free for the fox we do +1
            # If we can take a goose from the current position we +2
            # Din moment ce gâsca este min, am calculat în așa fel încât fiecare poziție în care vulpea se poate muta să fie un dezavantaj
            # + iau în calcul și pozițiile în care vulpea poate să ia gâște
            foxPos = Game.getFoxPos(self.configuration)
            positions = [foxPos]
            auxConfig = deepcopy(self.configuration)

            for position in [(2, 2), (2, -2), (-2, 2), (-2, -2), (0, 2), (2, 0), (0, -2), (-2, 0)]:
                try:
                    geesePos = (foxPos[0] + position[0] // 2, foxPos[1] + position[1] // 2)
                    if auxConfig[geesePos[0]][geesePos[1]] == 'G' and auxConfig[position[0]][position[1]] == '.':
                        score += 2
                except IndexError:
                    continue
            for position in positions:
                for move in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                    try:
                        if position[0] + move[0] < 0 or position[1] + move[1] < 0:
                            raise IndexError
                        if auxConfig[position[0] + move[0]][position[1] + move[1]] != 'X':
                            if auxConfig[position[0] + move[0]][position[1] + move[1]] == '.':
                                score += 1
                                auxConfig[position[0] + move[0]][position[1] + move[1]] = 'F'
                                positions.append((position[0] + move[0], position[1] + move[1]))
                    except IndexError:
                        continue
        
        return score

# Algoritmul min max
def min_max(state):
    global GLOBAL_CURRENT_NODES

    state.possibleStates = state.getNextStates()
    GLOBAL_CURRENT_NODES += len(state.possibleStates)
    
    if state.level == 0 or len(state.possibleStates) == 0:
        state.score = state.getScore()
        return state
        

    movesWithEstimation = [ min_max(x) for x in state.possibleStates ]

    if state.turn == FOX_TURN:
        state.newState = max(movesWithEstimation, key = lambda x: x.getScore())
    else:
        state.newState = min(movesWithEstimation, key = lambda x: x.getScore())

    state.score = state.newState.score
    return state

# Algoritmul alpha beta
def alpha_beta(alpha, beta, state):
    global GLOBAL_CURRENT_NODES

    # Ordonăm mutările după scorul căutat
    state.possibleStates = sorted(state.getNextStates(), key = lambda x: x.getScore(), reverse=state.turn == FOX_TURN)
    GLOBAL_CURRENT_NODES += len(state.possibleStates)
    
    if state.level == 0 or state.isFinal():
        state.score = state.getScore()
        return state
    
    if alpha > beta:
        return state
            
    if state.turn == FOX_TURN:
        currentScore = float('-inf')

        for move in state.possibleStates:
            newState = alpha_beta(alpha, beta, move)

            if currentScore < newState.getScore():
                state.newState = newState
                currentScore = newState.getScore()
            if alpha < newState.getScore():
                alpha = newState.getScore()
                if alpha >= beta:
                    break
    else:
        currentScore = float('inf')
        for move in state.possibleStates:
            newState = alpha_beta(alpha, beta, move)

            if currentScore > newState.getScore():
                state.newState = newState
                currentScore = newState.getScore()
            if beta > newState.getScore():
                beta = newState.getScore()
                if alpha >= beta:
                    break

    state.score = state.newState.getScore()

    return state

class Game:
    # Inițializarea jocului
    def __init__(self, players):
        # Matricea jocului
        self.matrix = [
            ['X', 'X', '.', '.', '.', 'X', 'X'],
            ['X', 'X', '.', '.', '.', 'X', 'X'],
            ['G', '.', '.', 'F', '.', '.', 'G'],
            ['G', '.', '.', '.', '.', '.', 'G'],
            ['G', 'G', 'G', 'G', 'G', 'G', 'G'],
            ['X', 'X', 'G', 'G', 'G', 'X', 'X'],
            ['X', 'X', 'G', 'G', 'G', 'X', 'X']
        ]

        # Suprafața pe care desenăm elementele jocului
        self.displaySurface = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE))
        pygame.display.set_caption('Mitoi Ștefan - Daniel === Vulpea și Gâștele')

        # Lista cu playerii care participă la joc
        self.player = players.pop()
        self.players = players
        
        # Turul jocului, încep gâștele
        self.turn = GEESE_TURN

        # Elementul selectat de pe tablă + dacă avem o mutare combo (vulpea sare peste mai multe gâște)
        self.selected = None
        self.comboMoves = None

        self.start = time()
        self.end = None
    
    # O metodă ce returnează poziția vulpii pe tablă
    @staticmethod
    def getFoxPos(configuration):
        for index in range(len(configuration)):
            for jndex in range(len(configuration[index])):
                if configuration[index][jndex] == 'F':
                    return (jndex, index)

    # Metodă ce desenează elementele pe tablă
    def drawBoard(self):
        global IS_FINAL
        
        # Desenăm elementele pe rând
        for index in range(len(self.matrix)):
            for jndex in range(len(self.matrix[index])):
                if self.matrix[index][jndex] != 'X':
                    # Desenăm dreptunghiurile
                    posX = WINDOW_SIZE // len(self.matrix) * jndex
                    posY = WINDOW_SIZE // len(self.matrix[index]) * index
                    color = SELECTED_COLOR if (jndex, index) == self.selected else BACKGROUND_COLOR

                    # Marcăm poziția finală
                    if self.matrix[index][jndex] != '.' and IS_FINAL:
                        color = SELECTED_COLOR

                    pygame.draw.rect(self.displaySurface, color, (posX + OFFSET, posY + OFFSET, GRID_SIZE, GRID_SIZE))
                    # Dacă avem drum pe diagonală îl desenăm
                    if index % 2 == jndex % 2:
                        for pos in [(1, 1), (1, -1), (-1, 1), (-1, -1)]:
                            pygame.draw.line(self.displaySurface, BLACK_COLOR, 
                                    (posX + GRID_SIZE // 2 + OFFSET, posY + GRID_SIZE // 2 + OFFSET), 
                                    (posX + GRID_SIZE // 2 + OFFSET + (pos[0]) * GRID_SIZE // 2, posY + GRID_SIZE // 2 + OFFSET + (pos[1]) * GRID_SIZE // 2), 4)
                    # Desenăm cercurile pentru piese și pentru locurile goale
                    if self.matrix[index][jndex] != '.':
                        color = GEESE_COLOR if self.matrix[index][jndex] == 'G' else FOX_COLOR
                        pygame.draw.circle(self.displaySurface, color, (posX + GRID_SIZE // 2 + OFFSET, posY + GRID_SIZE // 2 + OFFSET), GRID_SIZE // 4)
                    else:
                        pygame.draw.circle(self.displaySurface, BLACK_COLOR, (posX + GRID_SIZE // 2 + OFFSET, posY + GRID_SIZE // 2 + OFFSET), GRID_SIZE // 8)
                    
    # Desenarea tablei de joc
    def drawGame(self):
        self.drawBoard()

    # Funcția face schimbarea turului
    def switchTurn(self):
        global GLOBAL_MOVES

        GLOBAL_MOVES += 1
        if self.start is None:
            self.start = time()
        else:
            self.end = time()

        if self.turn == GEESE_TURN:
            self.turn = FOX_TURN
            self.selected = Game.getFoxPos(self.matrix)
        else:
            self.turn = GEESE_TURN
            self.selected = None

        self.players = [self.player] + self.players
        self.player = self.players.pop()

        if self.start is not None and self.end is not None:
            if self.player == 'P':
                GLOBAL_LIST_TIME.append(self.end - self.start)
            if COMPUTER_GAME:
                remainingTime = 0.5 - (self.end - self.start)
                if remainingTime > 0:
                    sleep(remainingTime)
        
    # Funcție ce tratează evenimentele
    def handleEvent(self, event):
        # Tratăm evenimentul de selectare a piesei pentru gâscă
        if self.turn == GEESE_TURN:
            try:
                if event.type == pygame.MOUSEBUTTONDOWN:
                    index = event.pos[0] // (GRID_SIZE + OFFSET)
                    jndex = event.pos[1] // (GRID_SIZE + OFFSET)
                    if self.matrix[jndex][index] == 'G':
                        self.selected = (index, jndex)
            except IndexError:
                pass
        # Tratăm evenimentul de mutare a piesei
        if event.type == pygame.KEYDOWN and self.selected is not None:
            if event.key in [pygame.K_w, pygame.K_a, pygame.K_s, pygame.K_d, pygame.K_q, pygame.K_e, pygame.K_z, pygame.K_c]:
                posX = self.selected[0]
                posY = self.selected[1]
                move = None

                if event.key == pygame.K_w:
                    posY -= 1
                    move = (0, -1)
                if event.key == pygame.K_a:
                    posX -= 1
                    move = (-1, 0)
                elif event.key == pygame.K_s:
                    posY += 1
                    move = (0, 1)
                elif event.key == pygame.K_d:
                    posX += 1
                    move = (1, 0)
                elif event.key == pygame.K_q and posX % 2 == posY % 2:
                    posY -= 1
                    posX -= 1
                    move = (-1, -1)
                elif event.key == pygame.K_e and posX % 2 == posY % 2:
                    posY -= 1
                    posX += 1
                    move = (1, -1)
                elif event.key == pygame.K_z and posX % 2 == posY % 2:
                    posY += 1
                    posX -= 1
                    move = (-1, 1)
                elif event.key == pygame.K_c and posX % 2 == posY % 2:
                    posY += 1
                    posX += 1
                    move = (1, 1)

                # Verificăm validitatea mișcării și dacă ne aflăm într-o mișcare de tip combo
                if move is not None:
                    try:
                        if self.matrix[posY][posX] == '.' and self.comboMoves is None:
                            self.matrix[self.selected[1]][self.selected[0]] = '.'
                            self.matrix[posY][posX] = 'F' if self.turn == FOX_TURN else 'G'
                            self.selected = (posX, posY)
                            self.switchTurn()
                        elif self.turn == FOX_TURN and self.matrix[posY][posX] == 'G' and self.matrix[posY + move[1]][posX + move[0]] == '.':
                            self.matrix[self.selected[1]][self.selected[0]] = '.'
                            self.matrix[posY][posX] = '.'
                            posX, posY = posX + move[0], posY + move[1]
                            self.matrix[posY][posX] = 'F'
                            self.selected = (posX, posY)
                            nextMoves = 0
                            for pos in [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]:
                                try:
                                    if pos[0] != 0 and pos[1] != 0 and self.selected[0] % 2 != self.selected[1] % 2:
                                        continue
                                    if self.matrix[self.selected[1] + pos[1]][self.selected[0] + pos[0]] == 'G' and self.matrix[self.selected[1] + pos[1] * 2][self.selected[0] + pos[0] * 2] == '.':
                                        nextMoves += 1
                                except:
                                    continue
                             # O parte în care fie setăm ca mișcarea următoare să fie de tip combo, fie schimbăm turul
                            if nextMoves != 0:
                                self.comboMoves = True
                                return
                            else:
                                self.comboMoves = None
                                self.switchTurn()
                        elif self.comboMoves:
                            self.comboMoves = None
                            self.switchTurn()
                    except IndexError:
                        if nextMoves != 0:
                            self.comboMoves = True
                            return
                        else:
                            self.comboMoves = None
                            self.switchTurn()

    # Loop-ul jocului
    def gameLoop(self):
        global GLOBAL_CURRENT_NODES, IS_FINAL

        while True:
            # Se desenează elementele de pe tablă
            self.drawGame()
            pygame.display.update()

            # Se verifică dacă acum joacă un player sau calculatorul
            if self.player == 'P':
                # print ('human')
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        self.endGame()
                        pygame.quit()
                        sys.exit()
                    else:
                        self.handleEvent(event)
            else:
                # Pentru calculatorul facem mișcarea direct și calculăm și timpul de decizie
                self.start = time()

                newState = GameState(self.turn, self.matrix, MAX_DEPTH)
                if ALGORITHM == 'min_max':
                    think = min_max(newState).newState
                else:
                    think = alpha_beta(-500, 500, newState).newState
                
                GLOBAL_LIST_NODES.append(GLOBAL_CURRENT_NODES)
                GLOBAL_CURRENT_NODES = 0

                self.matrix = think.configuration
                print (f'Scorul prezis este {think.score}')
                self.end = time()
                
                print (f'Calculatorul a gândit {self.end - self.start} secunde.')
                GLOBAL_LIST_TIME.append(self.end - self.start)

                self.switchTurn()

                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        self.endGame()
                        pygame.quit()
                        sys.exit()
                
                self.start = None
                self.end = None
            
            if (GameState(self.turn, self.matrix, MAX_DEPTH).isFinal()):
                break
        
        IS_FINAL = True

        while True:
            self.drawGame()
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.endGame()
                    pygame.quit()
                    sys.exit()
    
    def endGame(self):
        if len(GLOBAL_LIST_TIME):
            print (f'Timpul total de gândire: {sum(GLOBAL_LIST_TIME)}')
            print (f'Timpul mediu de gândire: {mean(GLOBAL_LIST_TIME)}')
            print (f'Mediana timpului de gândire: {median(GLOBAL_LIST_TIME)}')
        if len(GLOBAL_LIST_NODES):
            print (f'Numărul minim de noduri generate: {min(GLOBAL_LIST_NODES)}')
            print (f'Numărul maxim de noduri generate: {max(GLOBAL_LIST_NODES)}')
            print (f'Numărul total: {sum(GLOBAL_LIST_NODES)}')
        GLOBAL_END = time()
        print (f'Programul a rulat timp de {GLOBAL_END - GLOBAL_START} secunde')
        print (f'S-au făcut {GLOBAL_MOVES} mișcări')

if __name__ == '__main__':
    # Argument parser pentru inițializarea jocului
    parser = ArgumentParser(usage=__file__ + ' '
                                             '[--type TYPE] '
                                             '[--algorithm ALGORITM]'
                                             '[--euristic EURISTICĂ]'
                                             '[--help]',				 
                            description='Problema plăcilor suprapuse')

    parser.add_argument('-t', '--type',
                        dest='type',
                        default=1,
                        help='Tipul jocului: 1 (jucător vulpe v. jucător gâște), 2 (jucător vulpe v. calculator gâște), 3 (calculator vulpe v. jucător gâște), 4 (calculator vulpe v. calculator gâște)',
                        type=int)
    
    parser.add_argument('-a', '--algorithm',
                        dest='alg',
                        default='alpha_beta',
                        choices=['min_max', 'alpha_beta'],
                        help='Algoritmul pentru calcularea mișcărilor calculatorului. Opțiune ignorată pentru modul de joc 1.',
                        type=str)
    
    parser.add_argument('-d', '--difficulty',
                    dest='diff',
                    default='easy',
                    choices=['easy', 'medium', 'hard'],
                    help='Dificultatea jocului - adâncimea arborelui de parcurs (easy, medium, hard).',
                    type=str)

    args = vars(parser.parse_args())

    if args['type'] == 1:
        players = ['P', 'P']
    elif args['type'] == 2:
        players = ['P', 'C']
    elif args['type'] == 3:
        players = ['C', 'P']
    elif args['type'] == 4:
        players = ['C', 'C']
        COMPUTER_GAME = True

    if args['diff'] == 'easy':
        MAX_DEPTH = 1
    elif args['diff'] == 'medium':
        MAX_DEPTH = 2
    elif args['diff'] == 'hard':
        MAX_DEPTH = 4

    ALGORITHM = args['alg']

    Game(players).gameLoop()