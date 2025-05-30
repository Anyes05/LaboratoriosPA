#ifndef DTDIRECCION_H
#define DTDIRECCION_H

#include <iostream>

using namespace std;

class DtDireccion
{
private:
    string nombreCalle;
    int numero;
    string calleEsquina;
    bool apartamento;
    int numeroEdificio;
    string nombreEdificio;

public:
    DtDireccion();
    DtDireccion(string, int, bool, string, int, string);
    DtDireccion(string, int, string);
    ~DtDireccion();

    string getnombreCalle();
    int getnumero();
    bool getapartamento();
    string getcalleEsquina();
    int getnumeroEdificio();
    string getnombreEdificio();
};

#endif