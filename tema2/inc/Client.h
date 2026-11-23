#pragma once
#include <string>
#include <type_traits>

// Obiect valoare.
// Item 5: copy/assign/dtor generate de compilator sunt suficiente.
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

static_assert(std::is_copy_constructible<Client>::value, "copy constructor generat");
static_assert(std::is_copy_assignable<Client>::value, "copy assignment generat");
static_assert(std::is_destructible<Client>::value, "destructor generat");
// Item 5: ctor cu parametri -> fara ctor implicit
static_assert(!std::is_default_constructible<Client>::value, "fara constructor implicit");
