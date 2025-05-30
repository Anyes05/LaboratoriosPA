#ifndef DTFACTURA_H
#define DTFACTURA_H

#include <iostream>
#include <string>
using namespace std;

#include "DtFecha.h"
#include "DtProducto.h"

//#include "DtFecha.h"

class DtFactura
{
private:
    int codigoVenta;
    DtFecha fecha;
    DtProducto producto;
    float descuento; 
    float subTotal;
 

public:
    DtFactura();
    DtFactura(int codigoVenta, DtFecha fecha, DtProducto producto, float descuento, float subtotal);
    int getCodigoVenta();
    DtFecha getFecha();
    DtProducto getProducto();
    float getDescuento();
    float getSubtotal();
    float getMontoConDescuento(); // calculado
    float getTotalConIVA();       // calculado
};





#endif