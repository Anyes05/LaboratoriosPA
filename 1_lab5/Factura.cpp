#include "Factura.h"

using namespace std;

Factura::Factura(string codigo, DtFecha fecha, DtHora hora, DtVenta venta) : codigo(codigo), fecha(fecha), hora(hora), venta(venta)
{
    this->productos = new List(); // Inicializar con una instancia de ICollection
}

Factura::~Factura() {}

string Factura::getCodigo() {
    return codigo;
}

DtFecha Factura::getFecha() {
    return fecha;
}

DtHora Factura::getHora() {
    return hora; 
}

DtVenta Factura::getVenta() {
    return venta;
}


ICollection* Factura::getProductos() {
    return this->productos;
}

void Factura::setCodigo(string codigo) {
    this->codigo = codigo;
}

void Factura::setFecha(DtFecha fecha) {
    this->fecha = fecha;
}

void Factura::setHora(DtHora hora) {
    this->hora = hora;
}

void Factura::setVenta(DtVenta venta) {
    this->venta = venta;
}

void Factura::setProductos(ICollection * productos) {
    this->productos = productos;
}

