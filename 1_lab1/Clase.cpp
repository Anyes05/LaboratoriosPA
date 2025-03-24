#include "Clase.h"
using namespace std;

Clase::~Clase(){};

Clase::Clase (int ident, string nom, Turno turno) {
    this->id = ident;
    this->nombre = nom;
    this->turno = turno;
}

int Clase::getId () {
    return this->id;
}

string Clase::getNombre() {
    return this->nombre;
}

Turno Clase::getTurno () {
    return this->turno;
}

void Clase::setId (int ident) {
    this->id = ident;
}

void Clase::setNombre (string nom) {
    this->nombre = nom;
}

void Clase::setTurno (Turno turno) {
    this->turno = turno;
}

