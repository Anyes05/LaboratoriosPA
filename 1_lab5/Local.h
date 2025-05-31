#ifndef LOCAL_H
#define LOCAL_H
#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "Venta.h"
using namespace std;

class Local : public Venta // una coleccion de ventas locales
{
public:
    Local(int numero, float subTotal, float descuento); // constructor
    virtual ~Local(); // destructor
private:
    ICollection * mesas;
};

#endif