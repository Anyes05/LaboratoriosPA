#include <iostream>
#include "DtClase.h"

DtClase::DtClase(int id, string nom, Turno trno){
    this ->ID= id;
    this->nombre = nom;
    this->turno = trno;
}

DtClase::~DtClase(){}