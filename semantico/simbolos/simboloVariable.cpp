//
// Created by Pablo Brenes on 12 may 2018.
//

#include "simboloVariable.h"

simboloVariable::simboloVariable() {
    this->clasificador = _simboloVariable;
}

simboloVariable::simboloVariable(std::string idenfiticador) {
    this->identificador = std::move(idenfiticador);
    this->clasificador = _simboloVariable;
    this->tipo = tipo;
}
