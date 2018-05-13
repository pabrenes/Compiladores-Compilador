cmake_minimum_required(VERSION 3.9)
project(Lexico)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lexico main.cpp lexer/lexer.h lexer/lexer.cpp lexer/token.h lexer/token.cpp lexer/automata.h gramaticas/Gramatica.h gramaticas/Gramatica.cpp formatedPrint.h semantico/simbolos/simbolo.h semantico/simbolos/simboloVariable.cpp semantico/simbolos/simboloVariable.h semantico/tablaHash.h semantico/tablaHash.cpp gramaticas/GTablaFollows.h gramaticas/GTablaFollows.cpp gramaticas/nombresTerminales.h gramaticas/nombresTerminales.cpp semantico/erroresSemanticos.h semantico/simbolos/simboloConstante.cpp semantico/simbolos/simboloConstante.h semantico/simbolos/simboloTipoDefinido.cpp semantico/simbolos/simboloTipoDefinido.h)