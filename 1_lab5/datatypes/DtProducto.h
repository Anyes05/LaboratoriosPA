#ifndef DTPRODUCTO_H
#define DTPRODUCTO_H

#include <iostream>
#include "../ICollection/interfaces/ICollectible.h"

using namespace std;

class DtProducto : public ICollectible
{
private:
    char codigo;
    string descripcion;
    float precio;
public:
    DtProducto(char, string, float);
    virtual ~DtProducto();
    DtProducto();
    char getCodigo();
    string getdescripcion();
    float getprecio();
};

#endif