#pragma once
#include <string>
#include <type_traits>
#include "Uncopyable.h"

// Jurnalul bancii: toate operatiile sunt inregistrate aici.
// Item 6: exista un singur jurnal, copierea lui nu are sens. Aici folosim
// varianta din carte: mostenire privata din Uncopyable.
class Jurnal : private Uncopyable {
public:
    Jurnal();
    void scrie(const std::string& mesaj);

private:
    int nrMesaje_;   // Item 4: tip built-in -> trebuie initializat explicit in constructor
};

static_assert(!std::is_copy_constructible<Jurnal>::value, "jurnalul nu se copiaza");
static_assert(!std::is_copy_assignable<Jurnal>::value, "jurnalul nu se atribuie");

// Item 4: in loc de un obiect global (static non-local) folosim un obiect
// static LOCAL intors prin referinta. Este construit garantat la primul apel.
//
// De ce conteaza: constructorul lui ContBancar scrie in jurnal. Daca jurnalul
// ar fi o variabila globala intr-un .cpp, iar un cont ar fi o variabila globala
// in alt .cpp, ordinea in care sunt construite ar fi nedefinita, iar contul
// ar putea folosi jurnalul inainte ca acesta sa existe.
Jurnal& jurnal();
