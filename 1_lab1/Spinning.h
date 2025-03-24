#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H

#include "Clase.h"

class Spinning : public Clase {
    private:
        int cantBicicletas();
    public:
        int cupo();
        Spinning (int, string, Turno, int);
            
};



#endif