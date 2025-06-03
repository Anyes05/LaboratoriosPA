#ifndef DTDIRECCION_H
#define DTDIRECCION_H

#include <iostream>

using namespace std;

class DtDireccion
{
private:
    char nombreCalle;
    int numero;
    char calleEsquina;
    bool apartamento;
    int numeroEdificio;
    char nombreEdificio;

public:
    DtDireccion();
    DtDireccion(char, int, bool, char, int, char);
    DtDireccion(char, int, char);
    ~DtDireccion();

    char getnombreCalle();
    int getnumero();
    bool getapartamento();
    char getcalleEsquina();
    int getnumeroEdificio();
    char getnombreEdificio();
};

#endif