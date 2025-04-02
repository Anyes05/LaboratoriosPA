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
    int getCantInscriptos();
    void setCantInscriptos(int cantInscriptos);
    void setID(int id);
    void setNombre(string nombre);
    void setTurno(Turno turno);
    void agregarInscripto(Inscripcion *inscripcion);
    Inscripcion** getInscriptos();
    virtual int cupo() = 0;
    virtual DtClase getInfo() = 0;

protected:
    Inscripcion** inscriptos;  // Arreglo dinámico de punteros a Inscripcion
    int cantInscriptos;  // Cantidad de inscriptos actuales
    int capacidadInscriptos;  // Capacidad máxima del arreglo (por ejemplo, MAX_SOCIOS)
private:
    int ID;
    string nombre;
    Turno turno;
};

#endif
