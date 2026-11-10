#include "Jurnal.h"
#include <iostream>

Jurnal::Jurnal() : nrMesaje_(0) {
    std::cout << "[Jurnal] construit (la prima folosire)\n";
}

void Jurnal::scrie(const std::string& mesaj) {
    ++nrMesaje_;
    std::cout << "[Jurnal #" << nrMesaje_ << "] " << mesaj << "\n";
}

Jurnal& jurnal() {
    static Jurnal j;
    return j;
}
