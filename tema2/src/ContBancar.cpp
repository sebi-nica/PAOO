#include "ContBancar.h"
#include "Jurnal.h"

// Item 4: lista de initializare (atribuirea in corp n-ar compila).
ContBancar::ContBancar(const std::string& iban, const Client& titular)
    : iban_(iban), titular_(titular), sold_(0) {
    jurnal().scrie("Cont deschis: " + iban_ + " pentru " + titular_.nume());
}

void ContBancar::depune(int suma) {
    sold_ += suma;
    jurnal().scrie(iban_ + ": depunere " + std::to_string(suma) + " lei");
}

bool ContBancar::retrage(int suma) {
    if (suma > sold_) {
        jurnal().scrie(iban_ + ": retragere " + std::to_string(suma) + " lei REFUZATA (fonduri insuficiente)");
        return false;
    }
    sold_ -= suma;
    jurnal().scrie(iban_ + ": retragere " + std::to_string(suma) + " lei");
    return true;
}
