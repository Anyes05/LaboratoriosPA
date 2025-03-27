#ifndef DTCLASE_H
#define DTCLASE_H


#include <string>
#include "Turno.h"

using namespace std;

class DtClase
{
private:
    int ID;
    string nombre;
    Turno turno;
public:
    DtClase(int, string, Turno);
    virtual ~DtClase();
    int getId();
    string getNombre();
    Turno getTurno();
};

#endif