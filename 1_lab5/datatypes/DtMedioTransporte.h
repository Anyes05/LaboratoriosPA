#ifndef DTMEDIOTRANSPORTE_H
#define DTMEDIOTRANSPORTE_H

#include <iostream>
#include <string>
using namespace std;
#include "../ICollection/interfaces/ICollectible.h"

class DtMedioTransporte: public ICollectible {
private:
    string medioTransporte;

public:
    DtMedioTransporte();
    DtMedioTransporte(string medioTransporte);

    string getMedioTransporte();
};

#endif
