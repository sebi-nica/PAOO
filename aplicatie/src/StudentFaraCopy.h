#ifndef STUDENT_FARA_COPY_H
#define STUDENT_FARA_COPY_H

#include <iostream>
#include <set>

// ---------------------------------------------------------------------------
// CONTRA-EXEMPLU, scris GRESIT intentionat.
//
// Clasa aloca memorie pe heap si o elibereaza in destructor, dar NU are copy
// constructor propriu. Compilatorul genereaza atunci unul implicit, care copiaza
// membru cu membru -> se copiaza doar ADRESA din pointer (shallow copy).
// Rezultat: doua obiecte arata spre ACEEASI memorie, iar la distrugere aceeasi
// memorie e eliberata de doua ori (double free -> programul e oprit de sistem).
//
// In modul "sigur" (implicit) destructorul detecteaza a doua eliberare si doar
// o raporteaza, ca demonstratia sa poata continua. Cu argumentul --crash se
// face double free-ul real.
// ---------------------------------------------------------------------------
class StudentFaraCopy {
public:
    static bool modSigur;

    explicit StudentFaraCopy(int nota) : nota_(new int(nota)) {
        eliberate().erase(nota_);
        std::cout << "  [constructor]       StudentFaraCopy - aloca un int pe heap la "
                  << nota_ << "\n";
    }

    // !!! LIPSESTE copy constructor-ul -> se foloseste cel generat de compilator

    ~StudentFaraCopy() {
        if (modSigur && eliberate().count(nota_) != 0) {
            std::cout << "  [destructor]        StudentFaraCopy - !!! DOUBLE FREE: memoria de la "
                      << nota_ << " a fost DEJA eliberata de alt obiect!\n"
                      << "                      (fara protectie, aici programul s-ar opri brusc)\n";
            return;
        }
        std::cout << "  [destructor]        StudentFaraCopy - delete pe " << nota_ << "\n";
        if (modSigur) eliberate().insert(nota_);
        delete nota_;
    }

    void setNota(int n) { *nota_ = n; }
    int nota() const { return *nota_; }
    const void* adresa() const { return nota_; }

private:
    int* nota_;

    static std::set<const int*>& eliberate() {
        static std::set<const int*> adrese;
        return adrese;
    }
};

inline bool StudentFaraCopy::modSigur = true;

#endif // STUDENT_FARA_COPY_H
