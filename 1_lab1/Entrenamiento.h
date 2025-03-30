#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H
#define MAX_SOCIESENT 20

#include "DataTypes/DtEntrenamiento.h"
#include "Clase.h"


class Entrenamiento : public Clase {
    public:
        Entrenamiento(int, string, Turno, bool);
        bool getEnRambla();
        void setEnRambla(bool);
        int cupo();
    private:
        bool enRambla;
};


#endif