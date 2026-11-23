#include <iostream>
#include "Card.h"
#include "Client.h"
#include "ContBancar.h"
#include "Jurnal.h"

int main() {
    std::cout << "Pornire aplicatie...\n";

    Client ana("Ana Popescu", "2950101123456");
    Client mihai("Mihai Ionescu", "1880505654321");

    // Item 4: jurnalul se construieste aici, la prima folosire
    ContBancar contAna("RO01PAOO0001", ana);
    ContBancar contMihai("RO01PAOO0002", mihai);

    // Item 5: copy ctor generat pentru Client
    Client anaCopie = ana;
    std::cout << "Copie client (generata de compilator): " << anaCopie.nume() << "\n";

    contAna.depune(1000);
    contMihai.depune(250);
    contAna.retrage(200);
    contMihai.retrage(500);              // refuzata: fonduri insuficiente

    Card cardAna(contAna, "4111-0001");
    cardAna.plateste(50, "Librarie");

    // Item 5: copy ctor generat -> card pe acelasi cont
    Card cardDuplicat(cardAna);
    cardDuplicat.plateste(120, "Supermarket");

    // Item 5: Card nu are operator=:
    // Card cardMihai(contMihai, "4111-0002");
    // cardMihai = cardAna;

    // Item 6: nu se compileaza:
    // ContBancar clona(contAna);        // = delete
    // contMihai = contAna;              // = delete
    // Jurnal altJurnal(jurnal());       // Uncopyable: private

    std::cout << "\nSolduri finale:\n";
    std::cout << "  " << contAna.iban() << "  " << contAna.titular().nume() << ": " << contAna.sold() << " lei\n";
    std::cout << "  " << contMihai.iban() << "  " << contMihai.titular().nume() << ": " << contMihai.sold() << " lei\n";

    return 0;
}
