#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
using namespace std;

class Empleado : public ICollectible // una coleccion de empleados
{
protected:
    string nombre;
    int id;
public:
    Empleado(string, int); // constructor
    virtual ~Empleado(); // destructor
    // Getters y setters
    string getNombre();
    int getIdEmpleado();
    void setNombre(string); 
    void setIdEmpleado(int);
};

#endif