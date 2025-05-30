#ifndef DTPRODUCTO_H
#define DTPRODUCTO_H

#include <iostream>
#include "../ICollection/interfaces/ICollectible.h"

using namespace std;

class DtProducto : public ICollectible
{
private:
    string codigo;
    string descripcion;
    float precio;
    int cantVendido;

public:
    DtProducto(string, string, float, int);
    virtual ~DtProducto();
    DtProducto();
    string getCodigo();
    string getdescripcion();
    float getprecio();
    int getcantVendido();
};

#endif