#ifndef SOCIO_H
#define SOCIO_H

#include <iostream>
using namespace std;

class Socio{
    private:
        string ci;
        string nombre;
    public:
        Socio(string, string);

        string getNombre();
        string getCi();

        void setNombre(string);
        void setCi(string);
        
        void mostrarSocio();
        virtual ~Socio();
};

#endif