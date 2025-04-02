#include <iostream>

#include "Fecha.h"

// Fecha .cpp

Fecha::Fecha(int dia, int mes, int anio)
{

    this->anio = anio;
    this->mes = mes;
    this->dia = dia;
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

bool Fecha::validar() 
{
    // Verificar año válido (puedes ajustar los límites según sea necesario)
    if (anio < 1900 || anio > 2100) 
    {
        throw invalid_argument("Año no válido");
    }

    // Verificar mes válido
    if (mes < 1 || mes > 12)
    {
        throw invalid_argument("Mes no válido");
    }

    // Verificar días válidos para el mes
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0))  // Año bisiesto
    {
        diasPorMes[1] = 29;  // Febrero tiene 29 días
    }

    if (dia < 1 || dia > diasPorMes[mes - 1])
    {
        throw invalid_argument("Día no válido para el mes");
    }

    return true;
}


Fecha::Fecha()
{
    this->anio = 0;
    this->dia = 0;
    this->mes = 0;
}
