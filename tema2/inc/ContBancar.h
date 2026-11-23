#pragma once
#include <string>
#include <type_traits>
#include "Client.h"

class ContBancar {
public:
    ContBancar(const std::string& iban, const Client& titular);

    // Item 6: contul e unic -> fara copiere
    ContBancar(const ContBancar&) = delete;
    ContBancar& operator=(const ContBancar&) = delete;

    void depune(int suma);
    bool retrage(int suma);

    const std::string& iban() const { return iban_; }
    const Client& titular() const { return titular_; }
    int sold() const { return sold_; }

private:
    // Item 4: initializati in ordinea declararii
    const std::string iban_;
    Client titular_;           // fara ctor implicit
    int sold_;                 // built-in -> initializat explicit
};

static_assert(!std::is_copy_constructible<ContBancar>::value, "contul nu se copiaza");
static_assert(!std::is_copy_assignable<ContBancar>::value, "contul nu se atribuie");
