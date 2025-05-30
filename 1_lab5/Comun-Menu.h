#ifndef COMUN_MENU_H
#define COMUN_MENU_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
using namespace std;

class Comun_Menu : public ICollectible //una coleccion de productos
{
protected:
    int cantProducto;
public:
    Comun_Menu(int); //constructor
    virtual ~Comun_Menu(); //destructor
    //getterts y setters
    int getCantProducto();
    void setCantProducto(int);
    
};

#endif