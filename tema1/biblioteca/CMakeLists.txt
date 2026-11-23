# Biblioteca statica studentlib
cmake_minimum_required(VERSION 3.10)

project(studentlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(STUDENTLIB_SURSE
    src/Student.cpp
    inc/Student.h
)

add_library(${PROJECT_NAME} STATIC ${STUDENTLIB_SURSE})

# Acelasi nume ca dupa find_package
add_library(studentlib::studentlib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Instalare + export pentru find_package(studentlib)
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
