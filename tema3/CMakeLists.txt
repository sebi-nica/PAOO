cmake_minimum_required(VERSION 3.10)

project(tema3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tema3
        src/main.cpp
        src/Persoana.cpp
        src/Student.cpp
)
target_include_directories(tema3 PRIVATE inc)
