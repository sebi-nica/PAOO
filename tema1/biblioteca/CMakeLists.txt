# ============================================================================
#  PROIECTUL 1: studentlib - biblioteca STATICA + header-ul Student.h
# ============================================================================
cmake_minimum_required(VERSION 3.10)

project(studentlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(STUDENTLIB_SURSE
    src/Student.cpp
    inc/Student.h
)

# STATIC -> se genereaza libstudentlib.a
add_library(${PROJECT_NAME} STATIC ${STUDENTLIB_SURSE})

# Alias cu namespace, ca proiectul care o foloseste sa scrie mereu
# studentlib::studentlib (fie ca o ia din add_subdirectory, fie din find_package)
add_library(studentlib::studentlib ALIAS ${PROJECT_NAME})

# inc/ e PUBLIC: cine leaga biblioteca primeste automat calea spre Student.h
# src/ e PRIVATE: doar biblioteca il vede
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# ---------------------------------------------------------------------------
# EXPORT: "make install" copiaza libstudentlib.a + Student.h si genereaza un
# fisier de configurare, astfel incat alt proiect sa poata scrie:
#     find_package(studentlib)
# ---------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME}
    EXPORT studentlibTargets
    ARCHIVE DESTINATION lib
)
install(FILES inc/Student.h DESTINATION include)
install(EXPORT studentlibTargets
    FILE studentlibConfig.cmake
    NAMESPACE studentlib::
    DESTINATION lib/cmake/studentlib
)
