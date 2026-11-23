# Executabilul care foloseste studentlib
cmake_minimum_required(VERSION 3.10)

project(aplicatie VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tinta existenta -> biblioteca instalata -> build din folderul vecin
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

target_link_libraries(${PROJECT_NAME} PRIVATE studentlib::studentlib)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
