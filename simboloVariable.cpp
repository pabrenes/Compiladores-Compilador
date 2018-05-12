//
// Created by Pablo Brenes on 12 may 2018.
//

#include "simboloVariable.h"
#include <utility>

using namespace std;

simboloVariable::simboloVariable(string idenfiticador, int tipo) {
    this->identificador = std::move(idenfiticador);
    this->clasificador = 1;
    this->tipo = tipo;
}
