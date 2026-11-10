# Tema PAOO – bibliotecă statică + aplicație C++ (CMake)

Aplicația demonstrează: build cu CMake, încapsulare, inițializarea membrilor în constructor,
eliberarea heap-ului în destructor, copy constructor și move constructor.
Fiecare constructor și destructor afișează un mesaj, ca să se vadă exact când e apelat.

## Structura

```
PAOO/
├── CMakeLists.txt              # construiește ambele proiecte dintr-o comandă
├── build.sh                    # script: configurează, compilează și rulează
├── biblioteca/                 # PROIECTUL 1 -> bibliotecă statică libstudentlib.a
│   ├── CMakeLists.txt
│   ├── inc/Student.h           # header-ul exportat
│   └── src/Student.cpp
└── aplicatie/                  # PROIECTUL 2 -> executabil care folosește biblioteca
    ├── CMakeLists.txt
    └── src/
        ├── main.cpp            # demonstrațiile
        └── StudentFaraCopy.h   # contra-exemplu: clasă FĂRĂ copy constructor
```

## Build și rulare (Linux)

```bash
sudo apt install build-essential cmake git     # o singură dată
./build.sh
```

sau manual:

```bash
mkdir build && cd build
cmake ..
make
./aplicatie/aplicatie            # toate demonstrațiile
./aplicatie/aplicatie --crash    # double free REAL: programul e oprit de sistem
```

Proiectele se pot construi și separat. Biblioteca se instalează, apoi aplicația o găsește cu `find_package`:

```bash
cmake -S biblioteca -B build-lib -DCMAKE_INSTALL_PREFIX=$PWD/install
cmake --build build-lib && cmake --install build-lib     # -> install/lib/libstudentlib.a + install/include/Student.h
cmake -S aplicatie -B build-app -DCMAKE_PREFIX_PATH=$PWD/install
cmake --build build-app && ./build-app/aplicatie
```

Dacă biblioteca nu e instalată, `aplicatie/CMakeLists.txt` o construiește automat din folderul vecin.

## Unde se găsește fiecare cerință

| # | Cerință | Unde | Ce demonstrează |
|---|---------|------|-----------------|
| 1 | Build cu CMake | cele 3 `CMakeLists.txt` | `add_library(... STATIC)`, `target_include_directories` (PUBLIC/PRIVATE), `install`/`EXPORT`, `target_link_libraries` |
| 2 | Încapsulare | `Student.h` | datele sunt `private`; `adaugaNota(15)` și `schimbaNume("")` sunt refuzate, așa că obiectul rămâne valid |
| 3 | Inițializare în constructor | `Student.cpp`, constructorii | `id_` e `const`, deci poate fi inițializat **doar** în lista de inițializare; un pointer neinițializat ar duce la `delete[]` pe o adresă aleatoare |
| 4 | Heap eliberat în destructor | `~Student()` | contorul de blocuri heap revine la 0 după fiecare bloc `{}`, după `new`/`delete` și după 1000 de obiecte; valgrind nu raportează scurgeri |
| 5 | Copy constructor | `Student(const Student&)` și `StudentFaraCopy` | fără el: aceeași adresă, modificarea copiei strică originalul, apoi **double free**. Cu el: copie în adâncime, obiecte independente |
| 6 | Move constructor | `Student(Student&&) noexcept` | `push_back(x)` face 2 alocări, `push_back(std::move(y))` face 0; la realocarea vectorului elementele sunt mutate (datorită `noexcept`); sursa rămâne goală, dar validă |

Clasa respectă **regula celor 5**: are și copy/move assignment.
