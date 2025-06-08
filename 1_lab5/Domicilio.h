#ifndef DOMICLIO_H
#define DOMICLIO_H

#include "ICollection/interfaces/ICollectible.h"

#include "Cliente.h"
#include "Repartidor.h"
#include "Venta.h"

using namespace std;

class Domicilio : public Venta // una coleccion de ventas a domicilio
{
public:
  Domicilio(int numero, float subTotal, float descuento, Cliente *cliente, Repartidor *repartidor); // constructor, agregar "DtCliente cliente"
                                     // cuando se implemente
  virtual ~Domicilio();              // destructor
private:
  Cliente *cliente;
  Repartidor *repartidor;
  void setRepartidor(Repartidor *repartidor);
  Repartidor *getRepartidor();

  DtFacturaDomicilio generarFacturaDomicilio(); // Debe existir
};

#endif