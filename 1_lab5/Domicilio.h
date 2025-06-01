#ifndef DOMICLIO_H
#define DOMICLIO_H
#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "Venta.h"
#include "Cliente.h"
#include "Repartidor.h"
using namespace std;

class Domicilio : public Venta // una coleccion de ventas a domicilio
{
public:
    Domicilio(int numero, float subTotal, float descuento, Cliente *cliente, Repartidor *repartidor); // constructor, agregar "DtCliente cliente" cuando se implemente
    virtual ~Domicilio(); // destructor
private:
    Cliente * cliente;
    Repartidor * repartidor;
};

#endif 