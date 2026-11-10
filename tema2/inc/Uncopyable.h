#pragma once

// Item 6, varianta din carte (stil C++98): copy constructor-ul si operator=
// sunt declarate PRIVATE si nu sunt definite. O clasa care mosteneste din
// Uncopyable nu mai poate fi copiata, pentru ca functiile generate de
// compilator pentru ea ar trebui sa le apeleze pe acestea, care sunt inaccesibile.
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};
