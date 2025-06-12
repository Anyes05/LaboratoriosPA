#include <iostream>
#include "DtFactura.h"


DtFactura::DtFactura() {}

DtFactura::DtFactura(int codigoVenta, DtFecha fecha, ICollection* productos, float descuento, float subTotal) {
    this->codigoVenta = codigoVenta;
    this->fecha = fecha;
    this->productos = productos;
    this->descuento = descuento;
    this->subTotal = subTotal;

}

int DtFactura::getCodigoVenta() {
return codigoVenta;
}

DtFecha DtFactura::getFecha() {
    return fecha;
}

ICollection* DtFactura::getProductos() {
return productos;
}

float DtFactura::getDescuento() {
return descuento;
}

float DtFactura::getSubtotal() {
    return subTotal;
}

float DtFactura::getMontoConDescuento() {
    return subTotal * (1 - descuento / 100);
}

float DtFactura::getTotalConIVA() {
    return getMontoConDescuento() * 1.22;
}