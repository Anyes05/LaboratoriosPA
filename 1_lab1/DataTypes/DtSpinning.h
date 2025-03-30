#ifndef DTSPINNING_H
#define DTSPINNING_H
using namespace std;

#include "DtClase.h"

class DtSpinning : public DtClase
{
private:
    int cantBicicletas;
public:
    DtSpinning(int, string, Turno, int);
    ~DtSpinning();
    int getCantBicicleta();
    void setCantBicicleta(int cantBicicletas);

    void print(ostream &out) const override 
    {
        DtClase::print(out);
        out << "\nCantidad de bicicletas: " << cantBicicletas << endl;

    }
};

#endif