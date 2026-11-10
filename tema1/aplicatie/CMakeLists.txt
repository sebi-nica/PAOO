# ============================================================================
#  PROIECTUL 2: aplicatie - executabil care FOLOSESTE biblioteca studentlib
# ============================================================================
cmake_minimum_required(VERSION 3.10)

project(aplicatie VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# De unde luam biblioteca (in aceasta ordine):
#  1. daca build-ul porneste din CMakeLists.txt-ul de sus, tinta exista deja;
#  2. altfel o cautam instalata (find_package, dupa "make install" in proiectul 1);
#  3. altfel construim proiectul 1 direct din folderul vecin.
if(NOT TARGET studentlib::studentlib)
    find_package(studentlib CONFIG QUIET)
    if(NOT studentlib_FOUND)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../biblioteca
                         ${CMAKE_CURRENT_BINARY_DIR}/biblioteca)
    endif()
endif()

set(APLICATIE_SURSE
    src/main.cpp
    src/StudentFaraCopy.h
)

add_executable(${PROJECT_NAME} ${APLICATIE_SURSE})

# Legarea cu biblioteca statica; calea spre Student.h vine automat (PUBLIC)
target_link_libraries(${PROJECT_NAME} PRIVATE studentlib::studentlib)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
