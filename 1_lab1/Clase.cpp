#include "Clase.h"
using namespace std;

Clase::~Clase(){}

Clase::Clase (DtClase* c) {
    this->clase = c;
}

DtClase * Clase::getClase () {
    return this->clase;
}

std::string Clase::getNombre() {
    return this->clase->getNombre();
}

void Clase::agregarInscripto(Inscripcion* inscripcion) {
    for (int i = 0; i < getMaxInscriptos(); i++) { 
        if (this->inscriptos[i] == NULL){
            this->inscriptos[i] = inscripcion;
            return;
        }
    }
}

int Clase::cupo() {
    int cuposLibres = 0;
    for (int i = 0; i < getMaxInscriptos(); i++) { 
        cuposLibres += this->inscriptos[i] == NULL ? 1 : 0;
    }
    return cuposLibres;
}

Inscripcion** Clase::getInscriptos() {
    return this->inscriptos;
}