//
// Created by Pablo Brenes on 12 may 2018.
//

#include "simboloTipoDefinido.h"

simboloTipoDefinido::simboloTipoDefinido() {
    clasificador = _simboloTipoDefinido;
}

simboloTipoDefinido::simboloTipoDefinido(std::string identificador) {
    clasificador = _simboloTipoDefinido;
    this->identificador = identificador;
}
