#include "Venta.h"
#include <iostream>
using namespace std;

Venta::Venta(int numero, float subTotal, float descuento, ListIterator productos) : productos(productos) {
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

ListIterator Venta::getProductos() {
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

void Venta::setProductos(ListIterator productos) {
    this->productos = productos;
}

