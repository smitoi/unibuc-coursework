# https://csacademy.com/contest/interview-archive/task/all-bst-preorders/statement/

class nod:
    def __init__(self, value, right, left):
        self.value = value
        self.right = right
        self.left = left

def preorder(root):
    if (root != None):
        print (root.value, end = ' ')
        preorder(root.left)
        preorder(root.right)

def arbori(st, fi):
    arb = list()
    
    
    if (st > fi):
        arb.append(None)
        return arb
    elif (st == fi):
        return [nod(st, None, None)]

    for i in range(st, fi + 1):
        arbSt = arbori(st, i - 1)
        arbDr = arbori(i + 1, fi)
        for j in range(len(arbSt)):
            nod_st = arbSt[j]
            for k in range(len(arbDr)):
                nod_dr = arbDr[k]
                nod_nou = nod(i, nod_dr, nod_st)
                arb.append(nod_nou)
                
    return arb

def all_bst_preorders(size):
    total = arbori(1, size)
    for i in range(len(total)):
        preorder(total[i])
        print ()

size = int(input())
all_bst_preorders(size)
