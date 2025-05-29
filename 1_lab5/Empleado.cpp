#include "Empleado.h"

Empleado::Empleado(string nom, int id) {
    this->nombre = nom;
    this->idEmpleado = id;
}
Empleado::~Empleado() {}

string Empleado::getNombre() {
    return this->nombre;
}

int Empleado::getIdEmpleado() {
    return this->idEmpleado;
}

void Empleado::setNombre(string nom) {
    this->nombre = nom;
}

void Empleado::setIdEmpleado(int id) {
    this->idEmpleado = id;
}

