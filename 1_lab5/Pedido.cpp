#include "Pedido.h"

Pedido::Pedido(Producto* producto, int cantidad) : producto(producto), cantProductos(cantidad) {}

Pedido::~Pedido() {}

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

int Pedido::restarProductos(){
    // lógica pendiente
    return 0; // o el valor adecuado
} // tengo dudas acerca de donde viene la cant a eliminar