#ifndef LISTA_H
#define LISTA_H

#include "vector.hpp"

class Lista {
    private:
        Vector*     lista;
        int         dimensiune;
    public:
        Lista();
        Lista(int dim, Vector* = nullptr);
        Lista(Lista&);
        int     getLen() const;
        Lista& operator=(const Lista&);
        Vector&    operator[](int) const;
        friend      std::ostream& operator<<(std :: ostream&, Lista&);
        friend      std::istream& operator>>(std :: istream&, Lista&);
        ~Lista() {
            delete[] lista;
        }
};
#endif
