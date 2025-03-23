#include <iostream>

#include "Fecha.h"

// Fecha .cpp

Fecha::Fecha(int dia, int mes, int anio)
{

    this->anio = anio;
    this->mes = mes;
    this->dia = dia;

    if(!this->validar()) {
        throw invalid_argument("Fecha no valida");
    }
}

int Fecha::setDia()
{
    return this->dia;
}
int Fecha::setMes()
{
    return this->mes;
}
int Fecha::setAnio()
{
    return this->anio;
}

int Fecha::getDia()
{
    return this->dia;
}
int Fecha::getMes()
{
    return this->mes;
}

int Fecha::getAnio()
{
    return this->anio;
}

bool Fecha::validar() {
    if(this->dia > 31 || this->mes > 12 || this->anio < 1900) {
        return false;
    }

    return true;
}

Fecha::Fecha()
{
    this->anio = 0;
    this->dia = 0;
    this->mes = 0;
}
