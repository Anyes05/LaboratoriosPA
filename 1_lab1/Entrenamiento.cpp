#include "Entrenamiento.h"

Entrenamiento::Entrenamiento(int ID, string nombre, Turno turno, bool enRambla) : Clase(ID, nombre, turno) {
    this->enRambla = enRambla;
    this->cantInscriptos = 0;
    this->inscriptos = new Inscripcion*[cupo()] { NULL };
}

bool Entrenamiento::getEnRambla(){
    return this->enRambla;
}

void Entrenamiento::setEnRambla(bool enRambla){
    this->enRambla = enRambla;
}

int Entrenamiento::cupo(){
    if (this->enRambla)
        return 20 - this->cantInscriptos;
    else
        return 10 - this->cantInscriptos;
}


DtClase Entrenamiento::getInfo(){
    return DtEntrenamiento(getID(), getNombre(), getTurno(), getEnRambla());
}