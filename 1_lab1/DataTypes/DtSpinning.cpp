#include <iostream>
#include "DtSpinning.h"

DtSpinning::DtSpinning(int id, string nom, Turno trno, int cantBici):DtClase (id, nom, trno){
    this->cantBicicleta = cantBici;
}

DtSpinning::~DtSpinning(){}

int DtSpinning::getCantBicicleta() {
    return this->cantBicicleta;
}