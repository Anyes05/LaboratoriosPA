#include "DtFacturaDomicilio.h"

// Constructor por defecto
DtFacturaDomicilio::DtFacturaDomicilio() {}

// Constructor con parámetros
DtFacturaDomicilio::DtFacturaDomicilio(DtVenta venta, DtRepartidor repartidor) {
    this->venta = venta;
    this->repartidor = repartidor;
}

DtVenta DtFacturaDomicilio::getVenta() {
    return venta;
}

DtRepartidor DtFacturaDomicilio::getRepartidor() {
    return repartidor;
}
