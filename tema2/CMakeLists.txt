cmake_minimum_required(VERSION 3.10)

project(tema2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tema2
    src/main.cpp
    src/Jurnal.cpp
    src/ContBancar.cpp
    src/Card.cpp
)
target_include_directories(tema2 PRIVATE inc)
