#pragma once
#include <string>
#include <type_traits>
#include "Client.h"

class ContBancar {
public:
    ContBancar(const std::string& iban, const Client& titular);

    // Item 6: un cont bancar este unic. O copie ar insemna doi "clone" cu
    // acelasi IBAN si aceiasi bani -> interzicem explicit functiile pe care
    // compilatorul le-ar genera altfel.
    ContBancar(const ContBancar&) = delete;
    ContBancar& operator=(const ContBancar&) = delete;

    void depune(int suma);
    bool retrage(int suma);

    const std::string& iban() const { return iban_; }
    const Client& titular() const { return titular_; }
    int sold() const { return sold_; }

private:
    // Item 4: membrii sunt initializati in ORDINEA DECLARARII de mai jos,
    // indiferent de ordinea din lista de initializare a constructorului.
    const std::string iban_;   // const -> poate fi doar initializat, nu atribuit
    Client titular_;           // fara constructor implicit -> obligatoriu in lista
    int sold_;                 // built-in -> fara initializare ar avea o valoare oarecare
};

static_assert(!std::is_copy_constructible<ContBancar>::value, "contul nu se copiaza");
static_assert(!std::is_copy_assignable<ContBancar>::value, "contul nu se atribuie");
