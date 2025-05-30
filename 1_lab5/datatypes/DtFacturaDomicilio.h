#ifndef DTFACTURADOMICILIO_H
#define DTFACTURADOMICILIO_H

#include <iostream>
using namespace std;

#include "DtVenta.h"
#include "DtRepartidor.h"

class DtFacturaDomicilio {
private:
    DtVenta venta;
    DtRepartidor repartidor;

public:
    DtFacturaDomicilio();
    DtFacturaDomicilio(DtVenta venta, DtRepartidor repartidor);

    DtVenta getVenta();
    DtRepartidor getRepartidor();
};

#endif
