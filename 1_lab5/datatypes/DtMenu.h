#ifndef DTMENU_H
#define DTMENU_H

#include "DtProducto.h"

class DtMenu : public DtProducto, public virtual ICollectible
{
private:
    string nombre;
    float descuentoMenu;

public:
    DtMenu(char, string, float, string, float);
    ~DtMenu();

    string getNombre();
    float getDescuentoMenu();
};

#endif