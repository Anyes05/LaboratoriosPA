#ifndef FECHA_H
#define FECHA_H
#include <stdexcept>
using namespace std;

//como es necesario validar las fechas era necesario crear los gets y sets

class Fecha
{
    private:
        int dia;
        int mes;
        int anio;
    public:
        Fecha(int dia, int mes, int anio);
        Fecha();
        bool validar();

        int getDia();
        int getMes();
        int getAnio();

        int setDia();
        int setMes();
        int setAnio();

};

#endif