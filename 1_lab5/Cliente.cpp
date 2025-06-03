#include "Cliente.h"

Cliente::Cliente(char nom, char tel, DtDireccion dir) : nombre(nom), telefono(tel), direccion(dir) {}

Cliente::~Cliente() {}

char Cliente::getNombre() {
    return nombre;
}

char Cliente::getTelefono() {
    return telefono;
}

DtDireccion Cliente::getDireccion() {
    return direccion;
}   

void Cliente::setNombre(char nom) {
    nombre = nom;
}

void Cliente::setTelefono(char tel) {
    telefono = tel;
}

void Cliente::setDireccion(DtDireccion dir) {
    direccion = dir;
}
