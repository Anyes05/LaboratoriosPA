#ifndef SPINNING_H
#define SPINNING_H

#include "DataTypes/DtSpinning.h"
#include "Clase.h"

class Spinning : public Clase {
    public:
        Spinning (int, string, Turno, int);
        int getCantidadBicicletas();
        void setCantidadBicicletas(int);
        int cupo();
    private:
        int cantBicicletas;
};

#endif