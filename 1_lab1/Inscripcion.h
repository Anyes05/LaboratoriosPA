#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include <iostream>
using namespace std;

#include "Clase.h"
#include "DataTypes/Fecha.h"
#include "Socio.h"


class Inscripcion {

    private: 
        Fecha * fecha;
        Socio * socio;
        DtClase * clase;

    public:
        Inscripcion (Fecha *, Socio*, DtClase*);
        Socio *getSocio();
        DtClase *getClase();
        Fecha *getFecha();
        void setFecha(Fecha *);
        void setSocio(Socio *);
        void mostrarInscripcion();
        ~Inscripcion();

};

#endif