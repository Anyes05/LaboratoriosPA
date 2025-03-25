#include "Entrenamiento.h"

Entrenamiento::Entrenamiento(DtEntrenamiento*dt) : Clase(dt){
    this->dtEntrenamiento = dt;
    this->inscriptos = new Inscripcion*[getMaxInscriptos()] { NULL };
}

int Entrenamiento::getMaxInscriptos(){
    return this->dtEntrenamiento->getEnRambla() ? 20 : 10;
}

