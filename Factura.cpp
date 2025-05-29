#include "Factura.h"
#include <iostream>
using namespace std;

Factura::Factura(string codigo) { // agregar DtFecha, DtHora, DtVenta, DtProducto cuando se implementen
    this->codigo = codigo;
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

// DtProducto Factura::getProducto() {
//     return producto;
// }

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

// void Factura::setProducto(DtProducto producto) {
//     this->producto = producto;
// }

