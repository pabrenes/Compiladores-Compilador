//
// Created by Pablo Brenes on 12 may 2018.
//

#ifndef LEXICO_SIMBOLOCONSTANTE_H
#define LEXICO_SIMBOLOCONSTANTE_H

#include "simbolo.h"

class simboloConstante : public simbolo{

public:
    int tipo;

    simboloConstante();
    simboloConstante(std::string idenfiticador);

};


#endif //LEXICO_SIMBOLOCONSTANTE_H
