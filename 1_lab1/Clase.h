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
    Clase(DtClase *);
    ~Clase();
    DtClase *getClase();
    string getNombre();
    void agregarInscripto(Inscripcion *inscripcion);
    virtual int cupo() = 0;
    Inscripcion** getInscriptos();
    virtual int getMaxInscriptos() = 0;
protected:
    // Arreglo que contiene punteros a las posibles incripciones a esta clase
    Inscripcion **inscriptos;
    int cantInscriptos;
private:
    DtClase *clase;
};

#endif
