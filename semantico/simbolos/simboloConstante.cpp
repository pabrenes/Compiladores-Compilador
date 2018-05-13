//
// Created by Pablo Brenes on 12 may 2018.
//

#include "simboloConstante.h"

simboloConstante::simboloConstante() {
    this->clasificador = _simboloConstante;
}

simboloConstante::simboloConstante(std::string idenfiticador) {
    this->identificador = std::move(idenfiticador);
    this->clasificador = _simboloConstante;
}
