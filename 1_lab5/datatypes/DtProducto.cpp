#include "DtProducto.h"

DtProducto::DtProducto(char codigo, string desc, float precio){
    this->codigo = codigo;
    this->descripcion = desc;
    this->precio = precio;
}
DtProducto::DtProducto() {
    this->codigo = codigo;
    this->descripcion = "";
    this->precio = 0.0;
}

DtProducto::~DtProducto(){}

char DtProducto::getCodigo(){
    return this->codigo;
}

string DtProducto::getdescripcion(){
    return this->descripcion;
}

float DtProducto::getprecio(){
    return this->precio;
}
