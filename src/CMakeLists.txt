cmake_minimum_required(VERSION 3.23)
project(ParseTree C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(ParseTree src/ParseNode.c src/ParseNode.h src/Symbol.c src/Symbol.h src/SearchDirectionType.h)
