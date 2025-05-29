#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
using namespace std;

class Cliente : public ICollectible // una coleccion de clientes. 
{
protected:
    string telefono;
    string nombre;
    // DtDireccion direccion;
public:
    Cliente(string, string /*,DtDireccion**/); // constructor
    ~Cliente(); // destructor
    // Getters y setters
    string getNombre();
    string getTelefono();
    void setNombre(string); 
    void setTelefono(string);
};

#endif