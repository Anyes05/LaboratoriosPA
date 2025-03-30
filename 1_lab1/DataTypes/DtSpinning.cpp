#include <iostream>
#include "DtSpinning.h"

DtSpinning::DtSpinning(int id, string nom, Turno trno, int cantBici):DtClase (id, nom, trno){
    this->cantBicicletas = cantBici;
}

DtSpinning::~DtSpinning(){}

int DtSpinning::getCantBicicleta() {
    return this->cantBicicletas;
}

void DtSpinning::setCantBicicleta(int cantBicicletas) {
    this->cantBicicletas = cantBicicletas;
}