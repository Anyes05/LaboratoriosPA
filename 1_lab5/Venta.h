#ifndef VENTA_H
#define VENTA_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "Factura.h" // incluir la clase Factura
#include "ICollection/collections/ListNode.h" // incluir la clase ListNode
using namespace std;

class Venta : public ICollectible //una coleccion de ventas
{
private:
    int numero;
    float subTotal;
    float descuento;
    float total;
    Factura* factura;
    ListIterator productos; // lista de productos 
public:
    Venta(int numero, float subTotal, float descuento, ListIterator productos); //constructor
    virtual ~Venta(); //destructor
    //getters y setters
    int getNumero();
    float getSubTotal();
    float getDescuento();
    float getTotal();
    Factura* getFactura(); 
    ListIterator getProductos();
    void setNumero(int numero);
    void setSubTotal(float subTotal);
    void setDescuento(float descuento);
    void setTotal(float total);
    void setFactura(Factura* factura); 
    void setProductos(ListIterator productos);
    //metodos
    void eliminarMenu();
    ListNode productosVenta();  // Devuelve una lista de productos vendidos??
    bool activa();
    void eliminarProductoVenta();
        
};


#endif