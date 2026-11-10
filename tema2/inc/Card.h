#pragma once
#include <string>
#include <type_traits>
#include "ContBancar.h"

// Un card legat de un cont. Nu scriem nicio functie speciala.
//
// Item 5: compilatorul genereaza copy constructor-ul (un card duplicat pentru
// ACELASI cont este ok), dar NU poate genera copy assignment-ul:
//   - cont_ este o referinta, iar o referinta nu poate fi "relegata" la alt cont;
//   - numar_ este const, deci nu poate fi modificat.
// Asadar operator= este sters automat: un card nu poate fi mutat pe alt cont.
class Card {
public:
    Card(ContBancar& cont, const std::string& numar);   // Item 4: referinta si const -> lista de initializare

    bool plateste(int suma,const std::string& comerciant);
    const std::string& numar() const { return numar_; }

private:
    ContBancar& cont_;
    const std::string numar_;
};

static_assert(std::is_copy_constructible<Card>::value, "copy constructor generat");
static_assert(!std::is_copy_assignable<Card>::value, "operator= nu poate fi generat");
