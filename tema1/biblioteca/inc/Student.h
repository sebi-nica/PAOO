#ifndef STUDENT_H
#define STUDENT_H

#include <cstddef>

// Student cu nume si note pe heap; implementeaza regula celor 5.
class Student {
public:
    explicit Student(const char* nume, std::size_t capacitateInitiala = 4);

    ~Student();

    // deep copy
    Student(const Student& other);

    // preia resursele, fara alocari
    Student(Student&& other) noexcept;

    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;

    // Modificari validate
    bool adaugaNota(int nota);
    bool modificaNota(std::size_t index, int notaNoua);
    bool schimbaNume(const char* numeNou);

    const char* nume() const;
    unsigned id() const;
    std::size_t numarNote() const;
    int nota(std::size_t index) const;
    double medie() const;
    const void* adresaNote() const;   // pentru demo
    void afiseaza() const;

    // Statistici heap
    static unsigned alocari();
    static unsigned eliberari();
    static unsigned blocuriActive();

private:
    static char* copiazaText(const char* text);
    static int* alocaNote(std::size_t capacitate);
    void elibereaza();
    void cresteCapacitatea();

    // Ordinea declararii = ordinea initializarii
    const unsigned id_;          // const -> doar in lista de initializare
    char* nume_;                 // heap
    int* note_;                  // heap
    std::size_t nrNote_;
    std::size_t capacitate_;

    static unsigned urmatorulId_;
    static unsigned alocari_;
    static unsigned eliberari_;
};

#endif // STUDENT_H
