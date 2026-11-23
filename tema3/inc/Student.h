//
// Created by Sebi on 23-Nov-26.
//

#ifndef TEMA3_STUDENT_H
#define TEMA3_STUDENT_H

#include "Persoana.h"

class Student : public Persoana {
private:
    int nota;

public:
    Student(const char* nume, int varsta, int nota);
    Student(const Student& other);
    Student& operator=(const Student& other);
    void afiseaza() const;
};

#endif //TEMA3_STUDENT_H
