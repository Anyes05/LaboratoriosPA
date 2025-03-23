#ifndef DTSPINNING_H
#define DTSPINNING_H
using namespace std;

#include "DtClase.h"

class DtSpinning : public DtClase
{
private:
    int cantBicicleta;

public:
    DtSpinning(int, string, Turno, int);
    ~DtSpinning();
};

#endif