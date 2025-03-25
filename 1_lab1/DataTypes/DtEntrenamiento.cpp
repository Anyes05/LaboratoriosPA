#include <iostream>
#include "DtEntrenamiento.h"

DtEntrenamiento::DtEntrenamiento(int id, string nom, Turno trno, bool rambla):DtClase (id, nom, trno){
    this->enRambla = rambla;
}

DtEntrenamiento::~DtEntrenamiento(){}

bool DtEntrenamiento::getEnRambla() {
    return this->enRambla;
}
