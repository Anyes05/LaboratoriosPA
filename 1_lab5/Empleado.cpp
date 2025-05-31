#include "Empleado.h"

Empleado::Empleado(string nom, int id) {
    this->nombre = nom;
    this->id = id;
}
Empleado::~Empleado() {}

string Empleado::getNombre() {
    return this->nombre;
}

int Empleado::getIdEmpleado() {
    return this->id;
}

void Empleado::setNombre(string nom) {
    this->nombre = nom;
}

void Empleado::setIdEmpleado(int id) {
    this->id = id;
}

