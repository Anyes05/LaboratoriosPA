#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H

#include "Clase.h"

class Entrenamiento : public Clase {
    private:
        bool enRambla;
    public:
        int cupo();
        Entrenamiento(int, string, Turno, bool);

};


#endif