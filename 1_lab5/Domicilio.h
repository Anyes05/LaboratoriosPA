#ifndef DOMICLIO_H
#define DOMICLIO_H
#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "Venta.h"
using namespace std;

class Domicilio : public Venta // una coleccion de ventas a domicilio
{
public:
    Domicilio(int numero, float subTotal, float descuento); // constructor, agregar "DtCliente cliente" cuando se implemente
    virtual ~Domicilio(); // destructor
private:
    //DtCliente cliente; // cliente al que se le hace la venta a domicilio. O directamente un puntero a cliente?
    //Asumo que como local apunta a mozo, domicilio apunta a repartidor. Asi que referencia a repartidor
};

#endif 