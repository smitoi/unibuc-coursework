#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        int     dimensiune;
        int*    valori;
    public:
        Vector();
        Vector(int, int*);
        Vector(Vector&);
        void    actualizare(int, int = 0);
        void    push(int);
        void    pop();
        int     getLen();
        int*    getElems();
        Vector& operator=(const Vector&);
        int&    operator[](int);
        friend      std::ostream& operator<<(std :: ostream&, Vector&);
        friend      std::istream& operator>>(std :: istream&, Vector&);
        ~Vector() {
            delete valori;
        }
};
#endif

