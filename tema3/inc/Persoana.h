//
// Created by Sebi on 23-Nov-26.
//

#ifndef TEMA3_PERSOANA_H
#define TEMA3_PERSOANA_H



class Persoana {
private:
    char* nume;
    int varsta;
public:
    Persoana(const char* nume, int varsta); // constructor
    virtual ~Persoana(); // destructor
    Persoana(const Persoana& other); // copy constructor
    Persoana& operator=(const Persoana& other);
    Persoana& operator+=(int other_varsta);
    void afiseaza() const;
};

#endif //TEMA3_PERSOANA_H