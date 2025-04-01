#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include <iostream>
using namespace std;

#include "Clase.h"
#include "DataTypes/Fecha.h"
#include "Socio.h"

class Clase;
class Socio;
class Fecha;

class Inscripcion {

    private: 
        Fecha * fecha;
        Socio * socio;
        Clase * clase;

    public:
        Inscripcion (Fecha *, Socio*, Clase*);
        Socio *getSocio();
        Clase *getClase();
        Fecha *getFecha();
        void setFecha(Fecha *);
        void setSocio(Socio *);
        void setClase(Clase *);
        void mostrarInscripcion();
        ~Inscripcion();

};

#endif