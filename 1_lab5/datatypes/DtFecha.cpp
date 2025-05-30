#include "DtFecha.h"

#include <iostream>

DtFecha::DtFecha(int dia, int mes, int anio){
    this->anio = anio;
    this->mes = mes;
    this->dia = dia;
}

DtFecha::DtFecha(){
    this->anio = 0;
    this->dia = 0;
    this->mes = 0;
}

int DtFecha::setDia(int dia){
    return this->dia = dia;
}

int DtFecha::setMes(int mes){
    return this->mes = mes;
}

int DtFecha::setAnio(int anio){
    return this->anio = anio;
}

int DtFecha::getDia(){
    return this->dia;
}

int DtFecha::getMes(){
    return this->mes;
}

int DtFecha::getAnio(){
    return this->anio;
}

bool DtFecha::validar(){
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

