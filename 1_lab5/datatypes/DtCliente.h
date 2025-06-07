#ifndef DTCLIENTE_H
#define DTCLIENTE_H

#include <iostream>
#include <string>
using namespace std;

#include "DtDireccion.h"

class DtCliente {
private:
    string telefono;
    string nombre;
    DtDireccion direccion;

public:
    DtCliente();
    DtCliente(string telefono, string nombre, DtDireccion direccion);
    string getTelefono();
    string getNombre();
    DtDireccion getDireccion();
};

#endif
