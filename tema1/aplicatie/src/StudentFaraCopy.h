#ifndef STUDENT_FARA_COPY_H
#define STUDENT_FARA_COPY_H

#include <iostream>
#include <set>

// Contra-exemplu: fara copy constructor -> shallow copy -> double free.
// modSigur doar raporteaza a doua eliberare; --crash o face real.
class StudentFaraCopy {
public:
    static bool modSigur;

    explicit StudentFaraCopy(int nota) : nota_(new int(nota)) {
        eliberate().erase(nota_);
        std::cout << "  [constructor]       StudentFaraCopy - aloca un int pe heap la "
                  << nota_ << "\n";
    }

    // lipseste intentionat copy constructor-ul

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
