#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "datatypes/DtDireccion.h"
using namespace std;

class Cliente : public ICollectible // una coleccion de clientes. 
{
protected:
    char telefono;
    string nombre;
    DtDireccion direccion;
public:
    Cliente(char, string, DtDireccion); // constructor
    ~Cliente(); // destructor
    
    // Getters y setters
    string getNombre();
    char getTelefono();
    DtDireccion getDireccion();
    void setNombre(string); 
    void setTelefono(char);
    void setDireccion(DtDireccion);
};

#endif