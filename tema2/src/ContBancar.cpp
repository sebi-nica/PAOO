#include "ContBancar.h"
#include "Jurnal.h"

// Item 4: toti membrii sunt initializati in lista de initializare, in ordinea
// in care sunt declarati in clasa. Varianta cu atribuiri in corpul constructorului
// nici nu ar compila: iban_ este const, iar Client nu are constructor implicit.
//
//   ContBancar::ContBancar(const std::string& iban, const Client& titular) {
//       iban_ = iban;        // eroare: iban_ este const
//       titular_ = titular;  // eroare: titular_ ar fi trebuit construit implicit inainte
//   }
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
