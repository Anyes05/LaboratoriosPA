#include "Domicilio.h"


Domicilio::Domicilio(int numero, float subTotal, float descuento, Cliente * cliente, Repartidor * repartidor) : Venta(numero, subTotal, descuento) {
    this->cliente = cliente;
    this->repartidor = repartidor;
};

Domicilio::~Domicilio() {}

