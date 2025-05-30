#include "Factura.h"
#include <iostream>
#include "ICollection/collections/ListIterator.h"
#include "ICollection/interfaces/ICollectible.h"
using namespace std;

Factura::Factura(string codigo, const ListIterator& productos) : codigo(codigo), productos(productos) { // agregar DtFecha, DtHora, DtVenta, DtProducto cuando se implementen
}

Factura::~Factura() {}

string Factura::getCodigo() {
    return codigo;
}

// DtFecha Factura::getFecha() {
//     return fecha;
// }

// DtHora Factura::getHora() {
//     return hora; 
// }

// DtVenta Factura::getVenta() {
//     return venta;
// }


ListIterator Factura::getProductos() {
    return productos;
}

void Factura::setCodigo(string codigo) {
    this->codigo = codigo;
}

// void Factura::setFecha(DtFecha fecha) {
//     this->fecha = fecha;
// }

// void Factura::setHora(DtHora hora) {
//     this->hora = hora;
// }

// void Factura::setVenta(DtVenta venta) {
//     this->venta = venta;
// }

void Factura::setProductos(ListIterator productos) {
    this->productos = productos;
}

