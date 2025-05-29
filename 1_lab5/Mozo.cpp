#include "Mozo.h"

Mozo::Mozo(string nombre, int idEmpleado, int cantMesas) : Empleado(nombre, idEmpleado), cantMesas(cantMesas) {}

Mozo::~Mozo() {}

int Mozo::getCantMesas() {
    return cantMesas;
}

void Mozo::setCantMesas(int cantMesas) {
    this->cantMesas = cantMesas;
}

void Mozo::agregarMesa(Mesa* mesa) {
    mesas->add(mesa); 
}

void Mozo::eliminarMesa(Mesa* mesa) {
    if (mesa == nullptr) {
        throw std::invalid_argument("No hay mesas para eliminar.");
    }
    if (!mesas->member(mesa)) {
        throw std::invalid_argument("La mesa no existe en la colección.");
    }
    mesas->remove(mesa); 
}