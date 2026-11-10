// ============================================================================
//  Aplicatie demonstrativa PAOO - foloseste biblioteca statica studentlib
//
//  Rulare:  ./aplicatie           -> toate demonstratiile
//           ./aplicatie --crash   -> arata double free-ul REAL (programul cade)
// ============================================================================
#include "Student.h"            // header-ul exportat de biblioteca (proiectul 1)
#include "StudentFaraCopy.h"    // contra-exemplul (fara copy constructor)

#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

namespace {

void titlu(const char* text) {
    std::cout << "\n==================================================================\n"
              << " " << text
              << "\n==================================================================\n";
}

void heap(const char* moment) {
    std::cout << "    [heap] " << moment << ": " << Student::blocuriActive()
              << " blocuri alocate si neeliberate\n";
}

// ----------------------------------------------------------------------------
void demoIncapsulare() {
    titlu("2. INCAPSULARE");
    std::cout << "Datele (nume_, note_) sunt private; se modifica doar prin metode care\n"
                 "verifica valorile. Ex: 's.note_[0] = 99;' nu compileaza:\n"
                 "    error: 'int* Student::note_' is private within this context\n\n";

    Student s("Ana");
    s.adaugaNota(9);
    s.adaugaNota(10);
    std::cout << "  incerc sa adaug nota 15:\n";
    s.adaugaNota(15);
    std::cout << "  incerc sa pun un nume gol:\n";
    s.schimbaNume("");
    s.afiseaza();
    std::cout << "  -> obiectul a ramas intr-o stare corecta (nicio nota invalida).\n";
}

// ----------------------------------------------------------------------------
void demoInitializare() {
    titlu("3. INITIALIZAREA MEMBRILOR IN CONSTRUCTOR (lista de initializare)");
    std::cout << "Constructorul initializeaza toti membrii dupa ':' :\n"
                 "    Student(...) : id_(urmatorulId_++), nume_(copiazaText(nume)),\n"
                 "                   note_(alocaNote(cap)), nrNote_(0), capacitate_(cap) {}\n"
                 "De ce e nevoie:\n"
                 "  * id_ este 'const unsigned' -> 'id_ = 5;' in corpul constructorului\n"
                 "    da eroare de compilare (assignment of read-only member). Un membru\n"
                 "    const sau o referinta se pot initializa NUMAI in lista.\n"
                 "  * un pointer neinitializat contine o adresa aleatoare; destructorul\n"
                 "    ar face delete[] pe ea -> crash. Lista garanteaza valori valide.\n"
                 "  * fiecare membru e construit direct cu valoarea buna (nu intai cu una\n"
                 "    implicita si apoi suprascris).\n\n";

    Student a("Bogdan");
    Student b("Carmen", 2);
    std::cout << "  id-urile, fixate o data pentru totdeauna: " << a.id() << " si " << b.id()
              << "\n  numar note la inceput: " << a.numarNote() << " (nu valori aleatoare)\n";
}

// ----------------------------------------------------------------------------
void demoDestructor() {
    titlu("4. ELIBERAREA HEAP-ULUI IN DESTRUCTOR");
    heap("inainte");
    {
        std::cout << "  -- intru intr-un bloc { } --\n";
        Student temp("Temporar");
        temp.adaugaNota(7);
        heap("in interiorul blocului");
        std::cout << "  -- ies din bloc: destructorul e apelat automat --\n";
    }
    heap("dupa bloc");

    std::cout << "\n  Obiect creat cu new trebuie distrus cu delete:\n";
    Student* dinamic = new Student("Dinamic");
    heap("dupa new");
    delete dinamic;
    heap("dupa delete");

    std::cout << "\n  Creez si distrug 1000 de studenti (fara mesaje):\n";
    std::streambuf* vechi = std::cout.rdbuf(nullptr);   // opresc temporar afisarea
    for (int i = 0; i < 1000; ++i) {
        Student s("Anonim");
        for (int n = 1; n <= 10; ++n) s.adaugaNota(n);    // forteaza si realocari
    }
    std::cout.rdbuf(vechi);
    heap("dupa 1000 de studenti");
    std::cout << "  -> numarul de blocuri revine mereu la loc: nu exista memory leak.\n"
                 "     Fara 'delete[]' in destructor, fiecare student ar lasa 2+ blocuri\n"
                 "     pierdute (peste 2000 in bucla de mai sus).\n";
}

// ----------------------------------------------------------------------------
void primesteStudentPrinValoare(Student s) {
    std::cout << "    in functie am primit copia: ";
    s.afiseaza();
}

void demoCopyConstructor() {
    titlu("5. COPY CONSTRUCTOR");

    std::cout << "a) Ce se intampla FARA copy constructor (StudentFaraCopy):\n";
    {
        StudentFaraCopy original(10);
        StudentFaraCopy copie = original;   // copy constructor GENERAT -> shallow copy
        std::cout << "    adresa original: " << original.adresa()
                  << "\n    adresa copie:    " << copie.adresa()
                  << "   <- ACEEASI adresa!\n";
        copie.setNota(3);
        std::cout << "    am schimbat nota DOAR in copie (3), dar originalul are acum: "
                  << original.nota() << "  <- s-a stricat si originalul!\n"
                  << "    la iesirea din bloc ambele obiecte apeleaza delete pe aceeasi adresa:\n";
    }

    std::cout << "\nb) CU copy constructor scris corect (Student, deep copy):\n";
    {
        Student original("Dan");
        original.adaugaNota(8);
        original.adaugaNota(9);
        Student copie = original;            // apeleaza Student(const Student&)
        copie.schimbaNume("Dan (copie)");
        copie.modificaNota(0, 3);
        original.afiseaza();
        copie.afiseaza();
        std::cout << "    -> adrese diferite, modificarea copiei nu afecteaza originalul,\n"
                     "       iar fiecare destructor elibereaza doar memoria lui:\n";
    }

    std::cout << "\nc) Copy constructor-ul e apelat si implicit, la transmiterea prin valoare:\n";
    {
        Student s("Elena");
        s.adaugaNota(10);
        primesteStudentPrinValoare(s);
        std::cout << "    (copia din functie a fost distrusa la iesirea din functie)\n";
    }
}

// ----------------------------------------------------------------------------
Student creeazaBursier(const char* nume) {
    Student s(nume, 8);
    for (int n : {10, 10, 9, 10}) s.adaugaNota(n);
    return s;   // la return se muta (sau compilatorul elimina complet copia - RVO)
}

void demoMoveConstructor() {
    titlu("6. MOVE CONSTRUCTOR");

    std::cout << "a) Copiere vs mutare intr-un vector:\n";
    std::vector<Student> grupa;
    grupa.reserve(2);

    Student x("Florin");
    x.adaugaNota(7);
    Student y("Gabriela");
    y.adaugaNota(9);

    unsigned inainte = Student::alocari();
    grupa.push_back(x);                     // copy constructor
    std::cout << "    push_back(x)            -> alocari noi pe heap: "
              << Student::alocari() - inainte << "\n";

    inainte = Student::alocari();
    grupa.push_back(std::move(y));          // move constructor
    std::cout << "    push_back(std::move(y)) -> alocari noi pe heap: "
              << Student::alocari() - inainte << "\n";

    std::cout << "    y dupa mutare (gol, dar valid):\n";
    y.afiseaza();
    std::cout << "    -> mutarea nu copiaza datele, doar preia pointerii. La obiecte mari\n"
                 "       (mii de note) diferenta de timp si memorie e uriasa.\n";

    std::cout << "\nb) Vectorul isi mareste capacitatea: elementele vechi sunt MUTATE,\n"
                 "   nu copiate, pentru ca move constructor-ul e marcat noexcept:\n";
    inainte = Student::alocari();
    grupa.push_back(Student("Horia"));      // obiect temporar -> move automat
    std::cout << "    alocari noi: " << Student::alocari() - inainte
              << " (doar cele 2 ale lui Horia, nimic pentru studentii existenti)\n";

    std::cout << "\nc) Returnarea unui obiect dintr-o functie:\n";
    Student bursier = creeazaBursier("Ioana");
    bursier.afiseaza();

    std::cout << "\nd) Move assignment (operator=):\n";
    Student z("Ion");
    z = std::move(bursier);
    z.afiseaza();

    std::cout << "\n  -- sfarsitul functiei: se distrug toate obiectele --\n";
}

// ----------------------------------------------------------------------------
void demoCrash() {
    titlu("DOUBLE FREE REAL (fara copy constructor)");
    StudentFaraCopy::modSigur = false;
    StudentFaraCopy original(10);
    StudentFaraCopy copie = original;
    std::cout << "  Ambele obiecte au pointerul " << original.adresa()
              << ".\n  Urmeaza 2 x delete pe aceeasi adresa...\n" << std::flush;
}

} // namespace

int main(int argc, char* argv[]) {
    if (argc > 1 && std::strcmp(argv[1], "--crash") == 0) {
        demoCrash();
        return 0;
    }

    titlu("1. BUILD CU CMAKE: aplicatia ruleaza legata de libstudentlib.a");
    std::cout << "Clasa Student vine din biblioteca statica (proiectul 1), prin Student.h.\n"
                 "Fiecare constructor/destructor afiseaza un mesaj ca sa se vada cand e apelat.\n";

    demoIncapsulare();
    demoInitializare();
    demoDestructor();
    demoCopyConstructor();
    demoMoveConstructor();

    titlu("REZUMAT");
    std::cout << "  alocari totale pe heap:   " << Student::alocari()
              << "\n  eliberari totale:         " << Student::eliberari()
              << "\n  blocuri ramase pierdute:  " << Student::blocuriActive()
              << (Student::blocuriActive() == 0 ? "  -> nicio scurgere de memorie\n" : "\n");
    return 0;
}
