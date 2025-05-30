#ifndef DTCOMUN_H
#define DTCOMUN_H

#include "DtProdcuto.h"

class DtComun : public DtProducto, public virtual ICollectible{
    private:

    public:
        DtComun(string, string, float, int);
        ~DtComun();
};

#endif