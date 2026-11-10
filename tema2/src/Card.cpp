#include "Card.h"
#include "Jurnal.h"

Card::Card(ContBancar& cont, const std::string& numar) : cont_(cont), numar_(numar) {
    jurnal().scrie("Card " + numar_ + " emis pentru contul " + cont_.iban());
}

bool Card::plateste(int suma, const std::string& comerciant) {
    jurnal().scrie("Card " + numar_ + ": plata la " + comerciant);
    return cont_.retrage(suma);
}
