#include "Clase.h"
using namespace std;

Clase::~Clase(){}

Clase::Clase (int id, string nombre, Turno t) {
    this->ID = id;
    this->nombre = nombre;
    this->turno = t;
    this->cantInscriptos = 0;
    this->inscriptos = new Inscripcion*[MAX_SOCIOS] { NULL };
}

std::string Clase::getNombre() {
    return this->nombre;
}

int Clase::getID() {
    return this->ID;
}

Turno Clase::getTurno() {
    return this->turno;
}

void Clase::setID(int id) {
    this->ID = id;
}

void Clase::setNombre(string nombre) {
    this->nombre = nombre;
}

void Clase::setTurno(Turno t) {
    this->turno = t;
}

void Clase::agregarInscripto(Inscripcion* inscripcion) {
    for (int i = 0; i < cantInscriptos; i++) { 
        if (this->inscriptos[i] == NULL){
            this->inscriptos[i] = inscripcion;
            return;
        }
    }
}

Inscripcion** Clase::getInscriptos() {
    return this->inscriptos;
}