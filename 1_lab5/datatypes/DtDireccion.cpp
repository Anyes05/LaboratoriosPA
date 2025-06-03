#include "DtDireccion.h"
#include <iostream>

DtDireccion::DtDireccion(char calle, int num, bool apart, char esquina, int numEdificio, char nomEdificio){
    this->nombreCalle = calle;
    this->numero = num;
    this->apartamento = apart;
    this->calleEsquina = esquina;
    this->nombreEdificio = nomEdificio;
}
DtDireccion::DtDireccion() {
    // podés dejar valores vacíos o de prueba
    this->nombreCalle = "";
    this->numero = 0;
    this->apartamento = false;
    this->calleEsquina = "";
    this->nombreEdificio = "";
}


DtDireccion::DtDireccion(char calle, int num, char esquina){
    this->nombreCalle = calle;
    this->numero = num;
    this->calleEsquina = esquina;
}

DtDireccion::~DtDireccion(){}

char DtDireccion::getnombreCalle(){
    return this->nombreCalle;
}

int DtDireccion::getnumero(){
    return this->numero;
}

bool DtDireccion::getapartamento(){
    return this->apartamento;
}

char DtDireccion::getcalleEsquina(){
    return this->calleEsquina;
}

int DtDireccion::getnumeroEdificio(){
    return this->numeroEdificio;
}

char DtDireccion::getnombreEdificio(){
    return this->nombreEdificio;
}