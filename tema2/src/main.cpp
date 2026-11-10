#include <iostream>
#include "Card.h"
#include "Client.h"
#include "ContBancar.h"
#include "Jurnal.h"

int main() {
    std::cout << "Pornire aplicatie...\n";

    Client ana("Ana Popescu", "2950101123456");
    Client mihai("Mihai Ionescu", "1880505654321");

    // Jurnalul este construit abia acum, la prima folosire (Item 4).
    ContBancar contAna("RO01PAOO0001", ana);
    ContBancar contMihai("RO01PAOO0002", mihai);

    // Item 5: copy constructor generat de compilator pentru Client.
    // Fiecare cont pastreaza propria copie a datelor clientului.
    Client anaCopie = ana;
    std::cout << "Copie client (generata de compilator): " << anaCopie.nume() << "\n";

    contAna.depune(1000);
    contMihai.depune(250);
    contAna.retrage(200);
    contMihai.retrage(500);              // refuzata: fonduri insuficiente

    Card cardAna(contAna, "4111-0001");
    cardAna.plateste(50, "Librarie");

    // Item 5: copy constructor generat pentru Card -> card duplicat pe ACELASI cont.
    Card cardDuplicat(cardAna);
    cardDuplicat.plateste(120, "Supermarket");

    // Item 5: operator= NU este generat pentru Card (membru referinta + membru const):
    // Card cardMihai(contMihai, "4111-0002");
    // cardMihai = cardAna;              // eroare de compilare

    // Item 6: conturile si jurnalul NU pot fi copiate:
    // ContBancar clona(contAna);        // eroare: copy constructor sters (= delete)
    // contMihai = contAna;              // eroare: operator= sters (= delete)
    // Jurnal altJurnal(jurnal());       // eroare: Uncopyable(const Uncopyable&) e private

    std::cout << "\nSolduri finale:\n";
    std::cout << "  " << contAna.iban() << "  " << contAna.titular().nume() << ": " << contAna.sold() << " lei\n";
    std::cout << "  " << contMihai.iban() << "  " << contMihai.titular().nume() << ": " << contMihai.sold() << " lei\n";

    return 0;
}
