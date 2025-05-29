#include "Cliente.h"

Cliente::Cliente(string nom, string tel) : nombre(nom), telefono(tel) {}

Cliente::~Cliente() {}

string Cliente::getNombre() {
    return nombre;
}

string Cliente::getTelefono() {
    return telefono;
}

void Cliente::setNombre(string nom) {
    nombre = nom;
}

void Cliente::setTelefono(string tel) {
    telefono = tel;
}

