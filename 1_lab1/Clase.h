#ifndef CLASE_H
#define CLASE_H
#include "Socio.h"
#include "DataTypes/DtClase.h"
#include <iostream>
#define MAX_SOCIOS 50
using namespace std;



class Clase
{
private:
    DtClase * clase;
public:
    Clase(DtClase*);
    Clase getClase();
    void setClase(DtClase*);
    string getNombre();
    Socio* cantCupos;
    virtual int cupo();
    ~Clase();
};


#endif