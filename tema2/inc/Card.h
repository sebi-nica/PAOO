#pragma once
#include <string>
#include <type_traits>
#include "ContBancar.h"

// Card legat de un cont.
// Item 5: copy ctor generat; operator= sters (membru referinta + const).
class Card {
public:
    Card(ContBancar& cont, const std::string& numar);   // Item 4: lista de initializare

    bool plateste(int suma,const std::string& comerciant);
    const std::string& numar() const { return numar_; }

private:
    ContBancar& cont_;
    const std::string numar_;
};

static_assert(std::is_copy_constructible<Card>::value, "copy constructor generat");
static_assert(!std::is_copy_assignable<Card>::value, "operator= nu poate fi generat");
