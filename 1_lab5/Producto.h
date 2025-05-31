#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "./datatypes/DtProducto.h"
using namespace std;

class Producto : public ICollectible // una coleccion de productos
{
protected:
    string codigo;
    string descripcion;
    float precio;

public:
    Producto(string, string, float); // constructor
    virtual ~Producto();             // destructor
    // getterts y setters
    string getCodigo();
    string getDescripcion();
    float getPrecio();
    void setCodigo(string);
    void setDescripcion(string);
    void setPrecio(float);
    // metodos
    bool esProductoBaja();
    bool esMenu(string codigo);
    bool noExiste(string codigo);
    void cancelarBaja();
    virtual void darBaja() = 0;
    virtual DtProducto *getDT() = 0; 
};

#endif