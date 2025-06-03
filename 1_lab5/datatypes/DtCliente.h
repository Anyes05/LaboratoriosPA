#ifndef DTCLIENTE_H
#define DTCLIENTE_H

#include <iostream>
#include <string>
using namespace std;

#include "DtDireccion.h"

class DtCliente {
private:
    char telefono;
    string nombre;
    DtDireccion direccion;

public:
    DtCliente();
    DtCliente(char telefono, string nombre, DtDireccion direccion);
    char getTelefono();
    string getNombre();
    DtDireccion getDireccion();
};

#endif
