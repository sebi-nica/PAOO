#pragma once
#include <string>
#include <type_traits>
#include "Uncopyable.h"

// Jurnalul operatiilor.
// Item 6: necopiabil prin mostenire privata din Uncopyable.
class Jurnal : private Uncopyable {
public:
    Jurnal();
    void scrie(const std::string& mesaj);

private:
    int nrMesaje_;   // Item 4: initializat explicit
};

static_assert(!std::is_copy_constructible<Jurnal>::value, "jurnalul nu se copiaza");
static_assert(!std::is_copy_assignable<Jurnal>::value, "jurnalul nu se atribuie");

// Item 4: static local in loc de global -> construit la primul apel,
// evita ordinea nedefinita de initializare intre fisiere.
Jurnal& jurnal();
