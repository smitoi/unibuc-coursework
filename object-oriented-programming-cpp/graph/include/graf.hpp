#ifndef GRAF_H
#define GRAF_H

#include "lista.hpp"
#include "matrice.hpp"

class graf {
    protected:
        int nr_noduri;
        graf(int nr = 0)
        {
            nr_noduri = nr;
        };
    public:
        int     getNrNoduri();
        friend  std :: ostream&     operator<<(std :: ostream&, graf&);
        friend  std :: istream&     operator>>(std :: istream&, graf&);
        virtual std :: ostream&     afisare(std :: ostream&) = 0;
        virtual std :: istream&     citire(std :: istream&) = 0;
        virtual bool    isConex() = 0;
        virtual void    afisareVectorTati(int) = 0;
        virtual ~graf() {};
};

class graf_neorientat: public graf {
    private:
        Lista lis;
    public:
        graf_neorientat();
        graf_neorientat(const Lista&);
        std :: ostream&    afisare(std :: ostream&);
        std :: istream&      citire(std :: istream&);
        friend  std :: ostream&    operator<<(std :: ostream&, graf_neorientat&);
        friend  std :: istream&    operator>>(std :: istream&, graf_neorientat&);
        bool        isConex();
        void        afisareVectorTati(int) {
        };
        ~graf_neorientat() {
        }
};

class graf_orientat: public graf {
    private:
        matrice mat;
    public:
        graf_orientat();
        graf_orientat(const matrice&);
        std :: ostream& afisare(std :: ostream&);
        std::istream& citire(std :: istream&);
        friend  std :: ostream&    operator<<(std :: ostream&, graf_orientat&);
        friend  std :: istream&    operator>>(std :: istream&, graf_orientat&);
        bool        isConex();
        bool        canBeTree();
        void    afisareVectorTati(int);
        ~graf_orientat() {
        }
};

#endif

