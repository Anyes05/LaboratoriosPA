#ifndef DTMENU_H
#define DTMENU_H

#include "DtProdcuto.h"

class DtMenu : public DtProducto, public virtual ICollectible{
    private:
        int cantidad;
    public:
        DtMenu(string, string, float, int, int);
        ~DtMenu();

        int getCantidad();
};

#endif