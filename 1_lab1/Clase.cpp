#include "Clase.h"
using namespace std;

Clase::~Clase(){}

Clase::Clase(int id, string nombre, Turno turno)
{
    this->ID = id;
    this->nombre = nombre;
    this->turno = turno;
    this->cantInscriptos = 0;  // Inicializa el número de inscriptos en 0
    this->capacidadInscriptos = MAX_SOCIOS;  // Establece una capacidad máxima
    this->inscriptos = new Inscripcion*[this->capacidadInscriptos];  // Asigna memoria para los inscriptos
}

std::string Clase::getNombre() {
    return this->nombre;
}

int Clase::getID() {
    return this->ID;
}

Turno Clase::getTurno() {
    return this->turno;
}

int Clase::getCantInscriptos(){
    return this->cantInscriptos;
}

void Clase::setCantInscriptos(int cantIns){
    this->cantInscriptos = cantIns;
}

void Clase::setID(int id) {
    this->ID = id;
}

void Clase::setNombre(string nombre) {
    this->nombre = nombre;
}

void Clase::setTurno(Turno t) {
    this->turno = t;
}

void Clase::agregarInscripto(Inscripcion *inscripcion)
{
    if (cantInscriptos >= capacidadInscriptos)
    {
        throw std::invalid_argument("No hay espacio suficiente para agregar más inscripciones");
    }

    inscriptos[cantInscriptos] = inscripcion;  // Asignar la nueva inscripción al arreglo
    cantInscriptos++;  // Incrementar la cantidad de inscriptos

    // Si se alcanza la capacidad máxima, podrías aumentar el tamaño del arreglo
    if (cantInscriptos == capacidadInscriptos)
    {
        // Aumentar la capacidad del arreglo dinámico
        capacidadInscriptos *= 2;  // Duplicamos la capacidad
        Inscripcion** nuevoArreglo = new Inscripcion*[capacidadInscriptos];

        // Copiar las inscripciones existentes al nuevo arreglo
        for (int i = 0; i < cantInscriptos; i++)
        {
            nuevoArreglo[i] = inscriptos[i];
        }

        // Liberar la memoria del arreglo antiguo
        delete[] inscriptos;

        // Asignar el nuevo arreglo
        inscriptos = nuevoArreglo;
    }
}

Inscripcion** Clase::getInscriptos() {
    return this->inscriptos;
}