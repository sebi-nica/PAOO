#include "Student.h"

#include <algorithm>
#include <cstring>
#include <iostream>

unsigned Student::urmatorulId_ = 1;
unsigned Student::alocari_ = 0;
unsigned Student::eliberari_ = 0;

namespace {
const char* textSigur(const char* t) { return t ? t : "<gol>"; }
}

// ----------------------------------------------------------------- utilitare

char* Student::copiazaText(const char* text) {
    if (text == nullptr) text = "";
    char* rezultat = new char[std::strlen(text) + 1];
    ++alocari_;
    std::strcpy(rezultat, text);
    return rezultat;
}

int* Student::alocaNote(std::size_t capacitate) {
    int* p = new int[capacitate];
    ++alocari_;
    return p;
}

void Student::elibereaza() {
    if (nume_ != nullptr) { delete[] nume_; ++eliberari_; }
    if (note_ != nullptr) { delete[] note_; ++eliberari_; }
    nume_ = nullptr;
    note_ = nullptr;
    nrNote_ = 0;
    capacitate_ = 0;
}

void Student::cresteCapacitatea() {
    std::size_t capacitateNoua = capacitate_ == 0 ? 4 : capacitate_ * 2;
    int* noteNoi = alocaNote(capacitateNoua);
    if (note_ != nullptr) {
        std::copy(note_, note_ + nrNote_, noteNoi);
        delete[] note_;
        ++eliberari_;
    }
    note_ = noteNoi;
    capacitate_ = capacitateNoua;
}

// ---------------------------------------------------------------- constructor
// Toti membrii sunt initializati in LISTA DE INITIALIZARE (dupa ":"), nu prin
// atribuire in corpul constructorului:
//   * id_ este const -> compilatorul NU permite "id_ = ..." in corp;
//   * pointerii primesc direct o adresa valida; daca i-am lasa neinitializati,
//     destructorul ar face delete[] pe o adresa aleatoare -> crash.
Student::Student(const char* nume, std::size_t capacitateInitiala)
    : id_(urmatorulId_++),
      nume_(copiazaText(nume)),
      note_(alocaNote(capacitateInitiala == 0 ? 1 : capacitateInitiala)),
      nrNote_(0),
      capacitate_(capacitateInitiala == 0 ? 1 : capacitateInitiala)
{
    std::cout << "  [constructor]       Student #" << id_ << " '" << nume_
              << "' creat (heap: nume + loc pentru " << capacitate_ << " note)\n";
}

// ----------------------------------------------------------------- destructor
Student::~Student() {
    if (nume_ == nullptr && note_ == nullptr) {
        std::cout << "  [destructor]        Student #" << id_
                  << " (golit printr-un move) - nimic de eliberat\n";
    } else {
        std::cout << "  [destructor]        Student #" << id_ << " '" << nume_
                  << "' - delete[] pe nume si pe note\n";
    }
    elibereaza();
}

// ----------------------------------------------------------- copy constructor
// Copiere IN ADANCIME: obiectul nou primeste propriile zone de memorie, cu
// acelasi continut. Cele doua obiecte devin complet independente.
Student::Student(const Student& other)
    : id_(urmatorulId_++),
      nume_(copiazaText(other.nume_)),
      note_(alocaNote(other.capacitate_ == 0 ? 1 : other.capacitate_)),
      nrNote_(other.nrNote_),
      capacitate_(other.capacitate_ == 0 ? 1 : other.capacitate_)
{
    if (other.note_ != nullptr) std::copy(other.note_, other.note_ + other.nrNote_, note_);
    std::cout << "  [copy constructor]  Student #" << id_ << " '" << nume_
              << "' = COPIE a lui #" << other.id_ << " (memorie heap NOUA)\n";
}

// ----------------------------------------------------------- move constructor
// Nu aloca nimic: preia pointerii obiectului sursa si il lasa intr-o stare
// goala, dar valida (pointeri nullptr), ca destructorul lui sa nu elibereze
// memoria care acum ne apartine noua.
Student::Student(Student&& other) noexcept
    : id_(urmatorulId_++),
      nume_(other.nume_),
      note_(other.note_),
      nrNote_(other.nrNote_),
      capacitate_(other.capacitate_)
{
    other.nume_ = nullptr;
    other.note_ = nullptr;
    other.nrNote_ = 0;
    other.capacitate_ = 0;
    std::cout << "  [move constructor]  Student #" << id_ << " '" << textSigur(nume_)
              << "' a PRELUAT memoria lui #" << other.id_ << " (zero alocari)\n";
}

// ------------------------------------------------------------ copy assignment
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        // intai alocam si copiem, abia apoi eliberam vechea memorie
        int* noteNoi = alocaNote(other.capacitate_ == 0 ? 1 : other.capacitate_);
        char* numeNou = copiazaText(other.nume_);
        if (other.note_ != nullptr) std::copy(other.note_, other.note_ + other.nrNote_, noteNoi);
        std::size_t nr = other.nrNote_;
        std::size_t cap = other.capacitate_ == 0 ? 1 : other.capacitate_;

        elibereaza();
        nume_ = numeNou;
        note_ = noteNoi;
        nrNote_ = nr;
        capacitate_ = cap;
    }
    std::cout << "  [copy assignment]   Student #" << id_ << " a primit o copie a datelor lui #"
              << other.id_ << "\n";
    return *this;
}

// ------------------------------------------------------------ move assignment
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        elibereaza();
        nume_ = other.nume_;
        note_ = other.note_;
        nrNote_ = other.nrNote_;
        capacitate_ = other.capacitate_;
        other.nume_ = nullptr;
        other.note_ = nullptr;
        other.nrNote_ = 0;
        other.capacitate_ = 0;
    }
    std::cout << "  [move assignment]   Student #" << id_ << " a preluat datele lui #"
              << other.id_ << "\n";
    return *this;
}

// ------------------------------------------------------------ interfata
bool Student::adaugaNota(int nota) {
    if (nota < 1 || nota > 10) {
        std::cout << "    -> refuzat: nota " << nota << " nu este intre 1 si 10\n";
        return false;
    }
    if (nrNote_ == capacitate_) cresteCapacitatea();
    note_[nrNote_++] = nota;
    return true;
}

bool Student::modificaNota(std::size_t index, int notaNoua) {
    if (index >= nrNote_ || notaNoua < 1 || notaNoua > 10) {
        std::cout << "    -> refuzat: index sau nota invalida\n";
        return false;
    }
    note_[index] = notaNoua;
    return true;
}

bool Student::schimbaNume(const char* numeNou) {
    if (numeNou == nullptr || numeNou[0] == '\0') {
        std::cout << "    -> refuzat: numele nu poate fi gol\n";
        return false;
    }
    char* nou = copiazaText(numeNou);
    if (nume_ != nullptr) { delete[] nume_; ++eliberari_; }
    nume_ = nou;
    return true;
}

const char* Student::nume() const { return textSigur(nume_); }
unsigned Student::id() const { return id_; }
std::size_t Student::numarNote() const { return nrNote_; }
int Student::nota(std::size_t index) const { return index < nrNote_ ? note_[index] : 0; }
const void* Student::adresaNote() const { return note_; }

double Student::medie() const {
    if (nrNote_ == 0) return 0.0;
    double suma = 0;
    for (std::size_t i = 0; i < nrNote_; ++i) suma += note_[i];
    return suma / static_cast<double>(nrNote_);
}

void Student::afiseaza() const {
    std::cout << "    Student #" << id_ << " '" << nume() << "' note: [";
    for (std::size_t i = 0; i < nrNote_; ++i) std::cout << (i ? ", " : "") << note_[i];
    std::cout << "] medie " << medie() << "  (note la adresa " << adresaNote() << ")\n";
}

unsigned Student::alocari() { return alocari_; }
unsigned Student::eliberari() { return eliberari_; }
unsigned Student::blocuriActive() { return alocari_ - eliberari_; }
