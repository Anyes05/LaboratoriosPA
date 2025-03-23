#ifndef DTCLASE_H
#define DTCLASE_H
using namespace std;

#include "Turno.h"

class DtClase
{
protected:
    int ID;
    string nombre;
    Turno turno;

public:
    DtClase(int, string, Turno);
    ~DtClase();
};

#endif