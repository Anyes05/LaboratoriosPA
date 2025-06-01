#include "Mozo.h"
#include "ICollection/interfaces/OrderedKey.h"
#include "ICollection/interfaces/IKey.h"
#include "ICollection/interfaces/IDictionary.h"
#include "ICollection/Integer.h"
#include "ICollection/Integer.cpp"

Mozo::Mozo(string nombre, int idEmpleado, int cantMesas) : Empleado(nombre, idEmpleado), cantMesas(cantMesas) {}

Mozo::~Mozo() {}

int Mozo::getCantMesas() {
    return cantMesas;
}

void Mozo::setCantMesas(int cantMesas) {
    this->cantMesas = cantMesas;
}

// void Mozo::agregarMesa(Mesa* mesa) {
//     IKey* k = new Integer(mesa->getNumeroMesa());
//     this->mesas->add(k, mesa); // Agrega la mesa al diccionario usando su número como clave
// }

// void Mozo::eliminarMesa(Mesa* mesa) {
//     if (mesa == nullptr) {
//         throw std::invalid_argument("No hay mesas para eliminar.");
//     }
//     IKey* k = new Integer(mesa->getNumeroMesa());
//     if (!mesas->member(k)) {
//         delete k; // Liberar memoria del objeto clave
//         throw std::invalid_argument("La mesa no existe en la colección.");
//     }
//     mesas->remove(k); 
//     delete k;
// }