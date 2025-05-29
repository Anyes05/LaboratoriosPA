#ifndef REPARTIDOR_H
#define REPARTIDOR_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "Empleado.h"
using namespace std;

class Repartidor : public Empleado
{
private:
    string medioDeTransporte; // podria ser un enumerado, no?
public:
    Repartidor(string, int, string); // constructor
    ~Repartidor(); // destructor
    // Getters y setters
    string getTransporte();
    void setTransporte(string); 
};

#endif