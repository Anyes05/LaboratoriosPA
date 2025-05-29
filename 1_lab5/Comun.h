#ifndef COMUN_H
#define COMUN_H

#include "Producto.h"

class Comun : public Producto, public virtual ICollectible  //una coleccion de Comun
{
private:

public:
    Comun(string, string, float);
    ~Comun();

    void eliminarProducto();
    void agregarProdcutoComun(string codigoComun, string descripcion, float precio);
    void darBaja(); //funcion heredada y polimorfica
    void agregarCant();
    
};

#endif