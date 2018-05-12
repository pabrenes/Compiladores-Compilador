//
// Created by Pablo Brenes on 12 may 2018.
//

#include "tablaHash.h"

tablaHash::tablaHash(unsigned int _largoHash) {
    largoHash = _largoHash;
    arreglo = new vector<vector<simbolo*>>(largoHash);
}

uint32_t hashF(const string key, size_t length) {
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

void tablaHash::insertar(simbolo *simbolo){
    uint32_t hash = hashF(simbolo->identificador, simbolo->identificador.length()) % largoHash;
    arreglo->at(hash).push_back(simbolo);
}

bool tablaHash::buscar(string key) {
    uint32_t hash = hashF(key, key.length()) % largoHash;
    for (auto &i : arreglo->at(hash)) {
        if (i->identificador == key)
            return true;
    }
    return false;
}