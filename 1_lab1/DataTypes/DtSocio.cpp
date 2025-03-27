#include <iostream>
#include "DtSocio.h"

DtSocio::DtSocio(int ci, string nom){
    this ->CI= ci;
    this->nombre = nom;
};

string DtSocio::getNombre(){
    return this->nombre;
};

string DtSocio::getCi(){
    return this->getCi();
};

DtSocio::~DtSocio(){}