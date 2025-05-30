#include "DtDireccion.h"
#include <iostream>

DtDireccion::DtDireccion(string calle, int num, bool apart, string esquina, int numEdificio, string nomEdificio){
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


DtDireccion::DtDireccion(string calle, int num, string esquina){
    this->nombreCalle = calle;
    this->numero = num;
    this->calleEsquina = esquina;
}

DtDireccion::~DtDireccion(){}

string DtDireccion::getnombreCalle(){
    return this->nombreCalle;
}

int DtDireccion::getnumero(){
    return this->numero;
}

bool DtDireccion::getapartamento(){
    return this->apartamento;
}

string DtDireccion::getcalleEsquina(){
    return this->calleEsquina;
}

int DtDireccion::getnumeroEdificio(){
    return this->numeroEdificio;
}

string DtDireccion::getnombreEdificio(){
    return this->nombreEdificio;
}