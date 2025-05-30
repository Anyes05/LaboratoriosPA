#ifndef DTMEDIOTRANSPORTE_H
#define DTMEDIOTRANSPORTE_H

#include <iostream>
#include <string>
using namespace std;

class DtMedioTransporte {
private:
    string medioTransporte;

public:
    DtMedioTransporte();
    DtMedioTransporte(string medioTransporte);

    string getMedioTransporte();
};

#endif
