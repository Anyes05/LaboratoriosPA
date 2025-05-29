#include "Domicilio.h"
#include <iostream>
using namespace std;

Domicilio::Domicilio(int numero, float subTotal, float descuento) : Venta(numero, subTotal, descuento) {
    //this->cliente = cliente;  agregar DtCliente cliente cuando se implemente.
};

Domicilio::~Domicilio() {}

