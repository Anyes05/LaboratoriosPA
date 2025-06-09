#include "Domicilio.h"


Domicilio::Domicilio(int numero, float subTotal, float descuento, Cliente *cliente, Repartidor *repartidor)
    : Venta(numero, subTotal, descuento), cliente(cliente), repartidor(repartidor) {}

Domicilio::~Domicilio() {}

void Domicilio::setRepartidor(Repartidor *repartidor) {
    this->repartidor = repartidor;
}

void Domicilio::setCliente(Cliente *cliente) {
    this->cliente = cliente;
}

void Domicilio::agregarPedido(Pedido* pedido) {
    this->pedidos= new List(); // o usar tu ICollection
}

