import math

# Merges two heaps
def merge(n, m):
        if (n.min_root.key > m.min_root.key):
            aux = n.min_root.right;
            while (aux.right != n.min_root):
                aux = aux.right
            aux.right = m.min_root.right
            m.min_root.right = n.min_root
            m.noNodes += n.noNodes
            return m
        else:
            aux = m.min_root.right
            while (aux.right != m.min_root):
                aux = aux.right
            aux.right = n.min_root.right
            n.min_root.right = m.min_root
            n.noNodes += m.noNodes
            return n
        return None

class fheap:
    root = None
    min_root = None
    noNodes = 0
    
    class node:
        def __init__(self, key):
            self.key = key
            self.up = None
            self.down = None
            self.left = None
            self.right = None
            self.degree = 0

    # Put node n between l and r
    def putBetween(self, l, n, r):
        n.left = l
        n.right = r
        r.left = n
        l.right = n
    
    # Takes out node n from a list
    def takeOut(self, n):
        n.left.right = n.right
        n.right.left = n.left
        
    # Put node n between root and root.right
    def putRootList(self, n):
        if self.root is None:
            self.root = n
        else:
            self.putBetween(self.root, n, self.root.right)

    # Put node n as a child of up
    def putChildList(self, up, n):
        if up.down is None:
            up.down = n
        else:
            self.putBetween(up.down, n, up.down.right)

    # Removes node n from root list
    def removeNode(self, n):
        if n == self.root:
            self.root = n.right
        self.takeOut(n)

    # Removes n (child of up)
    def removeChild(self, up, n):
        if up.down == up.down.right:
            up.down = None
        elif up.down == n:
            up.down = n.right
            n.right.up = up
        self.putBetween (n.left, n, n.right)

    # Iterates the root list
    def getRootList(self, head):
        node = head.right
        yield node
        
        while node != head:
            node = node.right
            yield node

    # Returns the min
    def getMin(self):
        return self.min_root

    # Deletes the min and consolidates the tree
    def extractMin(self):
        nod = self.min_root
        if nod is not None:
            if nod.down is not None:
                aux = [x for x in self.getRootList(nod.down)]
                for index in range(len(aux)):
                    self.putRootList(aux[index])
                    aux[index].up = None
            self.removeNode(nod)
            if nod == nod.right:
                self.min_root = None
                self.root = None
            else:
                self.min_root = nod.right
                self.consolidate()
            self.noNodes -= 1
        return nod

    # Insert a new element
    def push(self, key):
        n = self.node(key)
        n.left = n.right = n
        self.putRootList(n)
        if self.min_root is None or n.key < self.min_root.key:
            self.min_root = n
        self.noNodes += 1
        return n

    # Finds the value sotred in val and returns the node
    def find_(self, init, val):
        found = init.right
        aux = None
        
        if (init.key == val):
            return init
        
        if (init == found and found.down != None):
            aux = self.find_(init.down, val)
        
        if (aux != None):
            return found

        while (found != init and found.key != val):
            if (found.down != None):
                aux = self.find_(found.down, val)
            
            if (aux != None):
                return aux
            
            found = found.right
        
        if (found.key != val):
            return None
        else:
            return found

    # Deletes a node of a given value
    def delete(self, val):
        if (val == self.min_root.key):
            self.extractMin()
        else:
            n = self.find_(self.min_root, val)
            if (n.right != n):
                if (n.up != None and n.down != None):
                    self.putBetween(n.left, n.down, n.right)
                    n.up.down = n.down
                elif (n.up != None and n.down == None):
                    self.takeOut(n)
                    n.up.down = n.right
                elif (n.down != None and n.up == None):
                    self.takeOut(n)
                    self.putBetween(n.left, n.down, n.right)
                elif (n.down == None and n.down == None):
                    self.takeOut(n)
            else:
                if (n.up != None and n.down != None):
                    n.down.up = n.up
                    n.up.down = n.down
                elif (n.up == None and n.down != None):
                    n.down.up = None
                    n = n.down
                elif (n.up != None and n.down == None):
                    n.up.down = None
            
    # Compare the degrees and combine the nodes of equal degrees
    def consolidate(self):
        degree_arr = [None] * int(math.log(self.noNodes) / math.log(2) + 1)
        nodes = list()
        for n in self.getRootList(self.min_root):
            nodes.append(n)

        for index in range(len(nodes)):
            m = nodes[index]
            deg = m.degree
            while degree_arr[deg] != None:
                n = degree_arr[deg]
                if m.key > n.key:
                    m, n = n, m
                self.childLink(n, m)
                degree_arr[deg] = None
                deg += 1
            degree_arr[deg] = m
        for index in range(len(degree_arr)):
            if degree_arr[index] is not None:
                if degree_arr[index].key < self.min_root.key:
                    self.min_root = degree_arr[index]

    # We put n as a child of m
    def childLink(self, n, m):
        self.removeNode(n)
        n.left = n.right = n
        self.putChildList(m, n)
        m.degree += 1
        n.up = m
    
    # Prints the root node list
    def display(self):
        print ("AVEM " + str(self.noNodes) + " NODURI: ")
        for n in self.getRootList(self.min_root):
            print (' -> ' + str(n.key), end='')
        print (' -> ')
        

'''
    OPERATII:
    1 - inserare valoare
    2 - stergere valoare
    3 - afisare minim
    4 - sterge minim
'''

fh = fheap()
file = open('input.txt', 'r')
n = int(file.readline())
for index in range(n):
    print ("OPERATIA CU NUMARUL: " + str(index + 1) + ": ", end='')
    op = [int(x) for x in file.readline().split(' ')]
    if (op[0] == 1):
        print ("OPERATIE DE INSERARE A LUI " + str(op[1]))
        fh.push(op[1])
    elif (op[0] == 2):
        print ("OPERATIE DE STERGERE A LUI " + str(op[1]))
        fh.delete(op[1])
    elif (op[0] == 3):
        print ("AFIS. MINIM = " + str(fh.getMin().key))
    elif (op[0] == 4):
        print ("STERGERE MINIM")
        fh.extractMin()
    fh.display()
        
