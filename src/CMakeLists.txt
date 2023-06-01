cmake_minimum_required(VERSION 3.23)
project(ParseTree C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(ParseTree src/ParseNode.c src/ParseNode.h src/Symbol.c src/Symbol.h src/SearchDirectionType.h src/NodeCondition/IsLeaf.c src/NodeCondition/IsLeaf.h src/NodeCondition/IsEnglishLeaf.c src/NodeCondition/IsEnglishLeaf.h src/ConstituentSpan.c src/ConstituentSpan.h src/NodeCollector.c src/NodeCollector.h src/ParseTree.c src/ParseTree.h src/TreeBank.c src/TreeBank.h src/ParallelTreeBank.c src/ParallelTreeBank.h)
target_link_libraries(ParseTree ${CONAN_LIBS})
