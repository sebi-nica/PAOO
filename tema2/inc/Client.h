#pragma once
#include <string>
#include <type_traits>

// Datele unui client. Este un simplu "obiect valoare": nu scriem copy
// constructor, operator= sau destructor.
//
// Item 5: compilatorul le genereaza singur, iar acestea copiaza/distrug
// membru cu membru (adica apeleaza functiile lui std::string). Pentru clasa
// asta comportamentul generat este exact cel corect, deci nu scriem nimic.
class Client {
public:
    Client(const std::string& nume, const std::string& cnp)
        : nume_(nume), cnp_(cnp) {}   // Item 4: lista de initializare

    const std::string& nume() const { return nume_; }
    const std::string& cnp() const { return cnp_; }

private:
    std::string nume_;
    std::string cnp_;
};

// Item 5: functiile generate de compilator
static_assert(std::is_copy_constructible<Client>::value, "copy constructor generat");
static_assert(std::is_copy_assignable<Client>::value, "copy assignment generat");
static_assert(std::is_destructible<Client>::value, "destructor generat");
// Item 5: am declarat un constructor cu parametri, deci compilatorul NU mai
// genereaza constructorul implicit (un client fara nume si CNP nu are sens).
static_assert(!std::is_default_constructible<Client>::value, "fara constructor implicit");
