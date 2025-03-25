#include "Inscripcion.h"
#include <iostream>

using namespace std;

Inscripcion::Inscripcion(Fecha *f, Socio *s, DtClase *c)
{
    this->fecha = f;
    this->socio = s;
    this->clase = c;
}

Socio *Inscripcion::getSocio()
{
    return this->socio;
}

DtClase *Inscripcion::getClase()
{
    return this->clase;
}

Fecha *Inscripcion::getFecha()
{
    return this->fecha;
}

void Inscripcion::setFecha(Fecha *f)
{
    this->fecha = f;
}

void Inscripcion::setSocio(Socio *s)
{
    this->socio = s;
}

void Inscripcion::mostrarInscripcion()
{
    cout << "Fecha de inscripción: " << fecha->getDia() << "/"
         << fecha->getMes() << "/" << fecha->getAnio() << endl;
    cout << "Socio: " << socio->getNombre() << " (CI: " << socio->getCi() << ")" << endl;
    cout << "Clase: " << clase->getNombre() << " (ID: " << clase->getId() << ")" << endl; 
}

// Destructor
Inscripcion::~Inscripcion() {}