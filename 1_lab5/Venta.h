#ifndef VENTA_H
#define VENTA_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
using namespace std;

class Venta : public ICollectible //una coleccion de ventas
{
private:
    int numero;
    float subTotal;
    float descuento;
    float total;
public:
    Venta(int numero, float subTotal, float descuento); //constructor
    virtual ~Venta(); //destructor
    //getters y setters
    int getNumero();
    float getSubTotal();
    float getDescuento();
    float getTotal();
    void setNumero(int numero);
    void setSubTotal(float subTotal);
    void setDescuento(float descuento);
    void setTotal(float total);
    //metodos
    void eliminarMenu();
    //DtProducto productosVenta();  // Devuelve una lista de productos vendidos??
    bool activa();
    void eliminarProductoVenta();
        
};


#endif