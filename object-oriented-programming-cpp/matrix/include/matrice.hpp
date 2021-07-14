#ifndef MATRICE_H
#define MATRICE_H

class   matrice {
    private:
        int     linii;
        int     coloane;
        double     **valori;
    public:
        // Constructorii
        matrice();
        matrice(int, int, int);
        matrice(const matrice&);
        ~matrice() {
            for (int index = 0; index < linii; ++index)
                delete[] valori[index];
            delete[] valori;
        }

        // Metode pentru actualizarea de valori
        void        citire();
        void        actualizare(int, int, int);
        void        diagonala(int);
        matrice     submatrice(int, int);

        // Metode pentru preluarea de valori
        int     getRows(); // nrlinii
        int     getCols(); // nrcoloane
        int     getElems(); // nrelemente
        void    afisare();
        double  determinant();

        // Operatii pentru prelucrare
        matrice&    operator=(const matrice&);
        double* operator[](int);

        // Operatii aditive
        friend  matrice operator+(const matrice&, const matrice&);
        friend  matrice operator+(const matrice&);
        friend  matrice& operator+=(matrice&, const matrice&);

        // Operatii de scadere
        friend  matrice operator-(const matrice&, const matrice&);
        friend  matrice operator-(const matrice&);
        friend  matrice& operator-=(matrice&, const matrice&);

        // Operatii multiplicative
        friend  matrice operator*(const matrice&, const matrice&);
        friend  matrice operator*(const double, const matrice&);
        friend  matrice operator*(const matrice&, const double);
        friend  matrice& operator*=(matrice&, const matrice&);
        friend  matrice& operator*=(matrice&, const double);

        // Operatii de comparare
        friend  bool operator!=(const matrice&, const matrice&);
        friend  bool operator==(const matrice&, const matrice&);
        friend  bool operator<=(const matrice&, const matrice&);
        friend  bool operator<(const matrice&, const matrice&);
        friend  bool operator>=(const matrice&, const matrice&);
        friend  bool operator>(const matrice&, const matrice&);
        friend  bool operator!=(const matrice&, const double);
        friend  bool operator==(const matrice&, const double);
        friend  bool operator<=(const matrice&, const double);
        friend  bool operator<(const matrice&, const double);
        friend  bool operator>=(const matrice&, const double);
        friend  bool operator>(const matrice&, const double);
        friend  bool operator!=(const double, const matrice&);
        friend  bool operator==(const double, const matrice&);
        friend  bool operator<=(const double, const matrice&);
        friend  bool operator<(const double, const matrice&);
        friend  bool operator>=(const double, const matrice&);
        friend  bool operator>(const double, const matrice&);
        friend  int  operator!(const matrice&);
        friend  matrice operator~(const matrice&);

        // Operatii de afisare si citire
        friend  std::ostream& operator<<(std :: ostream&, const matrice&);
        friend  std::istream& operator>>(std :: istream&, matrice&);
};

#endif // MATRICE_H
