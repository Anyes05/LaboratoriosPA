#include "Pedido.h"

Pedido::Pedido(int cantProductos) : cantProductos(cantProductos), producto(nullptr) {}
Pedido::~Pedido() {
    // ?? delete producto;  Liberar memoria del producto si fue asignado
}

int Pedido::getCantProductos() {
    return cantProductos;
}
void Pedido::setCantProductos(int cantProductos) {
    this->cantProductos = cantProductos;
}
Producto* Pedido::getProducto() {
    return producto;
}
void Pedido::setProducto(Producto* producto) {
    this->producto = producto;
}

bool Pedido::estaEnPedido(Producto* producto) {
    if (this->producto == nullptr) {
        return false;
    }
    return this->producto->getCodigo() == producto->getCodigo();
}

int Pedido::restarProductos(){} // tengo dudas acerca de donde viene la cant a eliminar