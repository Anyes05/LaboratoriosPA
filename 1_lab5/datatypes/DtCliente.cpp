#include "DtCliente.h"

DtCliente::DtCliente() {}

DtCliente::DtCliente(char telefono, char nombre, DtDireccion direccion) {
    this->telefono = telefono;
    this->nombre = nombre;
    this->direccion = direccion;
}

char DtCliente::getTelefono() {
    return telefono;
}

char DtCliente::getNombre() {
    return nombre;
}

DtDireccion DtCliente::getDireccion() {
    return direccion;
}
