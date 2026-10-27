#ifndef STUDENT_H
#define STUDENT_H

#include <cstddef>

// ---------------------------------------------------------------------------
// Clasa Student - exportata de biblioteca statica "studentlib".
//
// Un student are un nume (sir de caractere alocat pe HEAP) si un tablou de
// note (tot pe HEAP, cu capacitate care creste automat).
// Pentru ca administreaza memorie dinamica, clasa implementeaza explicit
// "regula celor 5": destructor, copy constructor, move constructor,
// copy assignment si move assignment.
// ---------------------------------------------------------------------------
class Student {
public:
    // Constructor: initializeaza TOTI membrii in lista de initializare.
    explicit Student(const char* nume, std::size_t capacitateInitiala = 4);

    // Destructor: elibereaza memoria de pe heap.
    ~Student();

    // Copy constructor: copiere in adancime (deep copy).
    Student(const Student& other);

    // Move constructor: "fura" resursele obiectului temporar, fara alocari.
    Student(Student&& other) noexcept;

    // Operatorii de atribuire (completeaza regula celor 5).
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;

    // --- Interfata publica (incapsulare: datele se modifica doar prin aceste
    //     metode, care verifica valorile primite) ---
    bool adaugaNota(int nota);
    bool modificaNota(std::size_t index, int notaNoua);
    bool schimbaNume(const char* numeNou);

    const char* nume() const;
    unsigned id() const;
    std::size_t numarNote() const;
    int nota(std::size_t index) const;
    double medie() const;
    const void* adresaNote() const;   // doar pentru demonstratii (afisare adresa)
    void afiseaza() const;

    // --- Statistici despre memoria heap folosita de toti studentii ---
    static unsigned alocari();
    static unsigned eliberari();
    static unsigned blocuriActive();

private:
    static char* copiazaText(const char* text);
    static int* alocaNote(std::size_t capacitate);
    void elibereaza();
    void cresteCapacitatea();

    // ATENTIE: ordinea declararii = ordinea in care se initializeaza membrii.
    const unsigned id_;          // const -> POATE fi initializat DOAR in lista de initializare
    char* nume_;                 // heap
    int* note_;                  // heap
    std::size_t nrNote_;
    std::size_t capacitate_;

    static unsigned urmatorulId_;
    static unsigned alocari_;
    static unsigned eliberari_;
};

#endif // STUDENT_H
