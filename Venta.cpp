#include "Venta.h"
#include <iostream>
using namespace std;

Venta::Venta(int numero, float subTotal, float descuento) {
    this->numero = numero;
    this->subTotal = subTotal;
    this->descuento = descuento;
    this->total = subTotal*0.22 - descuento; 
}

Venta::~Venta() {}

int Venta::getNumero() {
    return numero;
}

float Venta::getSubTotal() {
    return subTotal;
}

float Venta::getDescuento() {
    return descuento;
}

float Venta::getTotal() {
    return total;
}

void Venta::setNumero(int numero) {
    this->numero = numero;
}

void Venta::setSubTotal(float subTotal) {
    this->subTotal = subTotal;
}

void Venta::setDescuento(float descuento) {
    this->descuento = descuento;
}

void Venta::setTotal(float total) {
    this->total = total;
}


