//
// Created by Sebi on 23-Nov-26.
//
#include "Student.h"
#include <iostream>

Student::Student(const char* nume, int varsta, int nota)
    : Persoana(nume, varsta), nota(nota) {
}

Student::Student(const Student& other)
    : Persoana(other), nota(other.nota) {
}

Student& Student::operator=(const Student& other) {
    if (this == &other)
        return *this;

    Persoana::operator=(other);
    nota = other.nota;

    return *this;
}

void Student::afiseaza() const {
    Persoana::afiseaza();
    std::cout << "  nota: " << nota << "\n";
}
