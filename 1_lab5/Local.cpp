#include "Local.h"
#include <iostream>
using namespace std;

Local::Local(int numero, float subTotal, float descuento) : Venta(numero, subTotal, descuento) {
    this->mesas = new List(); 
}

Local::~Local() {}

