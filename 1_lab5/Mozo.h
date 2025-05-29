#ifndef MOZO_H
#define MOZO_H

#include <iostream>
#include "ICollection/interfaces/ICollection.h"
#include "Empleado.h"
#include "Mesa.h"
using namespace std;

class Mozo : public Empleado 
{
private:
    int cantMesas; 
    ICollection* mesas;// referencia a mesa, coleccion
public:
    Mozo(string, int, int); // constructor
    ~Mozo(); // destructor
    // Getters y setters
    int getCantMesas();
    void setCantMesas(int); 
    // metodos adicionales
    // set<Mesas> buscarMesa(); ??
    void agregarMesa(Mesa*); // agrega una mesa a la coleccion de mesas del mozo
    void eliminarMesa(Mesa*); // elimina una mesa de la coleccion de mesas del mozo
};

#endif