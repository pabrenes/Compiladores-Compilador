//
// Created by Pablo Brenes on 12 may 2018.
//

#ifndef PRUEBASHASH_SIMBOLOVARIABLE_H
#define PRUEBASHASH_SIMBOLOVARIABLE_H

#include "simbolo.h"

class simboloVariable : public simbolo{

public:
    int tipo;

    simboloVariable();
    simboloVariable(std::string idenfiticador);

};


#endif //PRUEBASHASH_SIMBOLOVARIABLE_H
