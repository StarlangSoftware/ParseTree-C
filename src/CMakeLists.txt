cmake_minimum_required(VERSION 3.23)
project(ParseTree)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(dictionary_c REQUIRED)

add_library(ParseTree ParseNode.c ParseNode.h Symbol.c Symbol.h SearchDirectionType.h NodeCondition/IsLeaf.c NodeCondition/IsLeaf.h NodeCondition/IsEnglishLeaf.c NodeCondition/IsEnglishLeaf.h ConstituentSpan.c ConstituentSpan.h NodeCollector.c NodeCollector.h ParseTree.c ParseTree.h TreeBank.c TreeBank.h ParallelTreeBank.c ParallelTreeBank.h)
target_link_libraries(ParseTree dictionary_c::dictionary_c)
