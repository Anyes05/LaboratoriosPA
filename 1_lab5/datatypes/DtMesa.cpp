#include "DtMesa.h"

DtMesa::DtMesa(int id){
    return this->idMesa = id;
}

DtMesa::~DtMesa(){}

int DtMesa::getIdMesa(){
    return this->idMesa;
}