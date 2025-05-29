#include "Repartidor.h"

Repartidor::Repartidor(string nom, int id, string transporte) : Empleado(nom, id) {
    this->medioDeTransporte = transporte;
}

Repartidor::~Repartidor() {}

string Repartidor::getTransporte() {
    return this->medioDeTransporte;
}

void Repartidor::setTransporte(string transporte) {
    this->medioDeTransporte = transporte;
}