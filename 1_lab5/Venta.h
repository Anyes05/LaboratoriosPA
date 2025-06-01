#ifndef VENTA_H
#define VENTA_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "Factura.h" 
#include "ICollection/collections/ListNode.h" 
#include "ICollection/interfaces/IDictionary.h"
#include "ICollection/interfaces/OrderedKey.h" 
#include "ICollection/String.h"
#include "ICollection/String.cpp"

using namespace std;

class Venta : public ICollectible //una coleccion de ventas
{
private:
    int numero;
    float subTotal;
    float descuento;
    float total;
    Factura* factura;
    IDictionary * productos; // lista de productos 
public:
    Venta(int numero, float subTotal, float descuento); //constructor
    virtual ~Venta(); //destructor
    //getters y setters
    int getNumero();
    float getSubTotal();
    float getDescuento();
    float getTotal();
    Factura* getFactura(); 
    IDictionary * getProductos();
    void setNumero(int numero);
    void setSubTotal(float subTotal);
    void setDescuento(float descuento);
    void setTotal(float total);
    void setFactura(Factura* factura); 
    void setProductos(IDictionary * productos);
    //metodos
    void eliminarMenu();
    ListNode productosVenta();  
    bool activa();
    void eliminarProductoVenta();
        
};


#endif