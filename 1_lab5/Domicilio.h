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
  Domicilio(int numero, float subTotal, float descuento, Cliente *cliente, Repartidor *repartidor); // constructor
  ~Domicilio();
  void setRepartidor(Repartidor *repartidor);
  DtRepartidor *getRepartidor();
  void setCliente(Cliente *cliente);
  DtCliente *getCliente();
  
  void agregarPedido(Pedido* pedido);
  DtFacturaDomicilio generarFacturaDomicilio(); // Debe existir
private:
  Cliente *cliente;
  Repartidor *repartidor;
  std::vector<Pedido*> pedidos; // o ICollection* pedidos si usas tu propia colección


};

#endif