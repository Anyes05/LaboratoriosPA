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
    char nombre;
    DtDireccion direccion;
public:
    Cliente(char, char, DtDireccion); // constructor
    ~Cliente(); // destructor
    
    // Getters y setters
    char getNombre();
    char getTelefono();
    DtDireccion getDireccion();
    void setNombre(char); 
    void setTelefono(char);
    void setDireccion(DtDireccion);
};

#endif