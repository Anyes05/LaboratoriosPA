#include "Entrenamiento.h"

Entrenamiento::Entrenamiento(DtEntrenamiento*dt) : Clase(dt){
    this->dtEntrenamiento = dt;
    this->inscriptos = new Inscripcion*[getMaxInscriptos()] { NULL };
}

int Entrenamiento::getMaxInscriptos(){
    return this->dtEntrenamiento->getEnRambla() ? 20 : 10;
}

int Entrenamiento::cupo(){
    if (this->enRambla)
        return 20 - this->cantInscriptos;
    else
        return 10 - this->cantInscriptos;
}