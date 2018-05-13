//
// Created by Pablo Brenes on 12 may 2018.
//

#ifndef LEXICO_SIMBOLOTIPODEFINIDO_H
#define LEXICO_SIMBOLOTIPODEFINIDO_H

#include "simbolo.h"

class simboloTipoDefinido : public simbolo {

public:
    int tipoBase;

    simboloTipoDefinido();
    simboloTipoDefinido(std::string identificador);
};


#endif //LEXICO_SIMBOLOTIPODEFINIDO_H
