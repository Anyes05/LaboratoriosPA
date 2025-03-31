#ifndef CLASE_H
#define CLASE_H

#include <iostream>
#include "Socio.h"
#include "Inscripcion.h"
#include "DataTypes/DtClase.h"

#define MAX_SOCIOS 50

using namespace std;

class Inscripcion;

class Clase
{
public:
    Clase(int, string, Turno);
    ~Clase();
    int getID();
    Turno getTurno();
    string getNombre();
    void setID(int id);
    void setNombre(string nombre);
    void setTurno(Turno turno);
    void agregarInscripto(Inscripcion *inscripcion);
    virtual int cupo() = 0;
    Inscripcion** getInscriptos();
    int cantInscriptos;

    virtual DtClase getInfo() const = 0;

protected:
    // Arreglo que contiene punteros a las posibles incripciones a esta clase
    Inscripcion **inscriptos;
private:
    int ID;
    string nombre;
    Turno turno;
};

#endif
