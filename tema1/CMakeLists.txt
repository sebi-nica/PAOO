# ============================================================================
#  Solutia completa: construieste ambele proiecte dintr-o singura comanda
#      mkdir build && cd build && cmake .. && make
# ============================================================================
cmake_minimum_required(VERSION 3.10)

project(PAOO_Tema LANGUAGES CXX)

add_subdirectory(biblioteca)   # proiectul 1 -> libstudentlib.a
add_subdirectory(aplicatie)    # proiectul 2 -> executabilul "aplicatie"
