#include "DtPedido.h"

DtPedido::DtPedido(int codigoProducto, string descripcion, float precioUnitario, int cantidad) {
    this->codigoProducto = codigoProducto;
    this->descripcion = descripcion;
    this->precioUnitario = precioUnitario;
    this->cantidad = cantidad;
}

int DtPedido::getCodigoProducto() {
    return this->codigoProducto;
}

string DtPedido::getDescripcion() {
    return this->descripcion;
}

float DtPedido::getPrecioUnitario() {
    return this->precioUnitario;
}

int DtPedido::getCantidad() {
    return this->cantidad;
}
