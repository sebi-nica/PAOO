//
// Created by Sebi on 23-Nov-26.
//
#include "Persoana.h"
#include <cstring>
#include <iostream>

void Persoana::afiseaza() const {
    std::cout << "[ " << nume << ", " << varsta << " ]\n";
}

Persoana::Persoana(const char* nume, int varsta) : varsta(varsta) {
    this->nume = new char[strlen(nume) + 1];
    strcpy(this->nume, nume);
}

Persoana::Persoana(const Persoana& other) : varsta(other.varsta) {
    this->nume = new char[strlen(other.nume) + 1];
    strcpy(this->nume, other.nume);
}

Persoana::~Persoana() {
    delete[] nume;
}

Persoana& Persoana::operator=(const Persoana& other) {

    if (this == &other)
        return *this;

    char* temp = new char[strlen(other.nume) + 1];
    strcpy(temp, other.nume);

    delete[] nume;
    nume = temp;
    varsta = other.varsta;

    return *this;
}

Persoana& Persoana::operator+=(int other_varsta) {
    varsta += other_varsta;
    return *this;
}