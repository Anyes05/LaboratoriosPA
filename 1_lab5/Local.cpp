#include "Local.h"
using namespace std;

Local::Local(int numero, float subTotal, float descuento) : Venta(numero, subTotal, descuento) {
    this->mesas = new List(); 
}

Local::~Local() {}

ICollection *Local::getMesas() {
    return mesas;
}

void Local::setMesas(ICollection *mesas) {
    this->mesas = mesas;
}

void Local::agregarMesa(ICollectible *mesa) {
    if (mesa != nullptr) {
        mesas->add(mesa);
    } else {
        throw invalid_argument("La mesa no puede ser nula.");
    }
}

Mozo *Local::getMozo() {
    return mozo;
}

void Local::setMozo(Mozo *mozo) {
    this->mozo = mozo;
}

void Local::agregarPedido(Pedido *pedido) {
    // Llamar al método de la clase padre (Venta)
    Venta::agregarPedido(pedido);
}


