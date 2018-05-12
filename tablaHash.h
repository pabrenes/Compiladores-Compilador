//
// Created by Pablo Brenes on 12 may 2018.
//

#ifndef LEXICO_TABLAHASH_H
#define LEXICO_TABLAHASH_H

#include <vector>
#include <algorithm>
#include "simboloVariable.h"

using namespace std;

struct tablaHash {
    unsigned int largoHash;
    vector<vector<simbolo*>>* arreglo;

    tablaHash(unsigned int _largoHash);

    uint32_t hashF(const string key, size_t length);

    void insertar(simbolo *simbolo);

    bool buscar(string key);

};

#endif //LEXICO_TABLAHASH_H
