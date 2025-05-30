#ifndef DTCOMUN_H
#define DTCOMUN_H

#include "DtProducto.h"

class DtComun : public DtProducto{
    private:

    public:
        DtComun(string, string, float, int);
        ~DtComun();
};

#endif