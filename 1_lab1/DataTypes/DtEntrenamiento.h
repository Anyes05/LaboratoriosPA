#ifndef DTENTRENAMIENTO_H
#define DTENTRENAMIENTO_H
using namespace std;

#include "DtClase.h"

class DtEntrenamiento : public DtClase
{
private:
    bool enRambla;

public:
    DtEntrenamiento(int, string, Turno, bool);
    ~DtEntrenamiento();
    bool getEnRambla();
};

#endif