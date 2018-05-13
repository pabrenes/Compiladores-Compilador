//
// Created by Pablo Brenes on 12 may 2018.
//

#ifndef PRUEBASHASH_SIMBOLO_H
#define PRUEBASHASH_SIMBOLO_H

#include <string>

class simbolo {

public:
    static const int _simboloConstante = 0;
    static const int _simboloTipoDefinido = 1;
    static const int _simboloVariable = 2;

    std::string identificador;
    int clasificador;

};


#endif //PRUEBASHASH_SIMBOLO_H
