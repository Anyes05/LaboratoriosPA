#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H
#define MAX_SOCIESENT 20

#include "DataTypes/DtEntrenamiento.h"
#include "Clase.h"


class Entrenamiento : public Clase {
    public:
        Entrenamiento(DtEntrenamiento*);
        bool getEnRambla();
        int getMaxInscriptos();
    private:
        DtEntrenamiento* dtEntrenamiento;
};


#endif