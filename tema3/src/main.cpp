//
// Created by Sebi on 23-Nov-26.
//

#include <iostream>

#include "Persoana.h"
#include "Student.h"

int main() {
    Persoana a("Ana", 20);
    Persoana b("Bogdan", 30);
    Persoana c("Cristi", 40);

    (a += 1) += 2;
    a.afiseaza();

    std::cout << "---------------\n";

    a = a;
    a.afiseaza();

    std::cout << "---------------\n";

    a = b = c;
    a.afiseaza();
    b.afiseaza();
    c.afiseaza();

    std::cout << "---------------\n";

    Student s1("Dana", 21, 9);

    Student s2(s1);
    s2.afiseaza();

    return 0;
}
