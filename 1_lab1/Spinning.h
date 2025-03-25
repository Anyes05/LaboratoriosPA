#ifndef SPINNING_H
#define SPINNING_H

#include "DataTypes/DtSpinning.h"
#include "Clase.h"

class Spinning : public Clase {
    public:
        Spinning (DtSpinning*);
        int getCantidadBicicletas();
        int getMaxInscriptos();
    private:
        DtSpinning* dtSpinning;
};

#endif