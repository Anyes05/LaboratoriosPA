#include "DtCliente.h"

DtCliente::DtCliente() {}

DtCliente::DtCliente(char telefono, string nombre, DtDireccion direccion) {
    this->telefono = telefono;
    this->nombre = nombre;
    this->direccion = direccion;
}

char DtCliente::getTelefono() {
    return telefono;
}

string DtCliente::getNombre() {
    return nombre;
}

DtDireccion DtCliente::getDireccion() {
    return direccion;
}
