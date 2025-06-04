#include "DtDireccion.h"

// Constructor por defecto
DtDireccion::DtDireccion()
{
    this->nombreCalle = "";
    this->numero = 0;
    this->apartamento = false;
    this->calleEsquina = "";
    this->numeroEdificio = 0;
    this->nombreEdificio = "";
}

// Constructor con parámetros
DtDireccion::DtDireccion(string nombreCalle, int numero, bool apartamento, string calleEsquina, int numeroEdificio, string nombreEdificio)
{
    this->nombreCalle = nombreCalle;
    this->numero = numero;
    this->apartamento = apartamento;
    this->calleEsquina = calleEsquina;
    this->numeroEdificio = numeroEdificio;
    this->nombreEdificio = nombreEdificio;
}

// Destructor
DtDireccion::~DtDireccion()
{
}

// Getters
string DtDireccion::getnombreCalle()
{
    return nombreCalle;
}

int DtDireccion::getnumero()
{
    return numero;
}

bool DtDireccion::getapartamento()
{
    return apartamento;
}

string DtDireccion::getcalleEsquina()
{
    return calleEsquina;
}

int DtDireccion::getnumeroEdificio()
{
    return numeroEdificio;
}

string DtDireccion::getnombreEdificio()
{
    return nombreEdificio;
}
