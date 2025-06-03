#ifndef DTCLIENTE_H
#define DTCLIENTE_H

#include <iostream>
#include <string>
using namespace std;

#include "DtDireccion.h"

class DtCliente {
private:
    char telefono;
    char nombre;
    DtDireccion direccion;

public:
    DtCliente();
    DtCliente(char telefono, char nombre, DtDireccion direccion);
    char getTelefono();
    char getNombre();
    DtDireccion getDireccion();
};

#endif
