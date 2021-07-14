#ifndef MATRICE_H
#define MATRICE_H

class   matrice {
    private:
        int     linii;
        int     coloane;
        int     **valori;
    public:
        matrice();
        matrice(int, int, int);
        matrice(const matrice&);
        void        actualizare(int, int, int);
        void        diagonala(int);
        int         getRows() const;
        int         getCols() const;
        matrice&    operator=(const matrice&);
        int*        operator[](int);
        friend      std::ostream& operator<<(std :: ostream&, matrice&);
        friend      std::istream& operator>>(std :: istream&, matrice&);
        ~matrice() {
            for (int index = 0; index < linii; ++index)
                delete valori[index];
            delete valori;
        }
};

#endif
