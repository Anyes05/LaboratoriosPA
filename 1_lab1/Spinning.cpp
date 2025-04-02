#include "Spinning.h"

Spinning::Spinning(int ID, string nombre, Turno turno, int cantBicicletas) : Clase(ID, nombre, turno)
{
    this->cantBicicletas = cantBicicletas;
    this->cantInscriptos = 0;
    this->inscriptos = new Inscripcion *[cantBicicletas]
    { NULL };
}

int Spinning::getCantidadBicicletas()
{
    return this->cantBicicletas;
}

void Spinning::setCantidadBicicletas(int cantBicicletas)
{
    this->cantBicicletas = cantBicicletas;
}

int Spinning::cupo()
{
    return this->cantBicicletas - this->cantInscriptos;
}

DtClase Spinning::getInfo()
{
    return DtSpinning(getID(), getNombre(), getTurno(), getCantidadBicicletas());
}
