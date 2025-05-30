#ifndef DTREPARTIDOR_H
#define DTREPARTIDOR_H

#include <iostream>
#include <string>
using namespace std;

class DtRepartidor {
private:
    int idRepartidor;
    string nombre;
    string transporte;

public:
    DtRepartidor();
    DtRepartidor(int idRepartidor, string nombre, string transporte);

    int getIdRepartidor();
    string getNombre();
    string getTransporte();
};

#endif
