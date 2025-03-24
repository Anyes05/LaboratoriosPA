#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H
#define MAX_SOCIESENT 20

#include "Clase.h"


class Entrenamiento : public Clase {
    private:
        bool enRambla;
        Socio* [MAX_SOCIOSENT];
    public:
        int cupo();
        Entrenamiento(int, string, Turno, bool);


};


#endif