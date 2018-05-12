cmake_minimum_required(VERSION 3.9)
project(Lexico)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lexico main.cpp parser.h parser.cpp token.h token.cpp automata.h Gramatica.h Gramatica.cpp formatedPrint.h simbolo.h simboloVariable.cpp simboloVariable.h tablaHash.h tablaHash.cpp)