#include "Spinning.h"

Spinning::Spinning(DtSpinning*dt) : Clase(dt){
    this->dtSpinning = dt;
    this->inscriptos = new Inscripcion*[getMaxInscriptos()] { NULL };
}

int Spinning::getMaxInscriptos() {
    return this->dtSpinning->getCantBicicleta();
}

int Spinning::getCantidadBicicletas(){
    return this->dtSpinning->getCantBicicleta();
}