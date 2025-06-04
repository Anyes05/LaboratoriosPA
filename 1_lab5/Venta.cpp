#include "Venta.h"
#include <iostream>
using namespace std;

Venta::Venta(int numero, float subTotal, float descuento) {
    this->numero = numero;
    this->subTotal = subTotal;
    this->descuento = descuento;
    this->total = subTotal*0.22 - descuento;
    this->factura = nullptr; 
}

Venta::~Venta() {}

int Venta::getNumero() {
    return numero;
}

float Venta::getSubTotal() {
    return subTotal;
}

float Venta::getDescuento() {
    return descuento;
}

float Venta::getTotal() {
    return total;
}

Factura* Venta::getFactura() {
    return factura;
}

IDictionary* Venta::getProductos() {
    return productos;
}

void Venta::setNumero(int numero) {
    this->numero = numero;
}

void Venta::setSubTotal(float subTotal) {
    this->subTotal = subTotal;
}

void Venta::setDescuento(float descuento) {
    this->descuento = descuento;
}

void Venta::setTotal(float total) {
    this->total = total;
}

void Venta::setFactura(Factura* factura) {
    this->factura = factura;
}

void Venta::setProductos(IDictionary * productos) {
    this->productos = productos;
}

bool Venta::getActiva() {
    return (factura == nullptr); // Si no hay factura, la venta está activa
}

void Venta::setActiva(bool activa) {
    if (activa) {
        factura = nullptr; // Si se activa, no hay factura
    } else {
        activa = false; 
    }
}


/*
void Venta::eliminarProductoVenta() {
    if (productos->isEmpty()) {
        cout << "No hay productos para eliminar." << endl;
        return;
    }
    IKey* key = new String(codigoProducto); 
    if (productos->member(key)) {
        productos->remove(key);
        cout << "Producto con código " << codigoProducto << " eliminado de la venta." << endl;
    } 
    else {
        cout << "No se encontró el producto con código " << codigoProducto << "." << endl;
    }
    
}
*/

