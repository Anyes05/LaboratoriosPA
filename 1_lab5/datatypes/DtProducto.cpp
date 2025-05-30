#include "DtProducto.h"
#include <iostream>

DtProducto::DtProducto(string codigo, string desc, float precio, int cant){
    this->codigo = codigo;
    this->descripcion = desc;
    this->precio = precio;
    this->cantVendido = cant;
}

DtProducto::~DtProducto(){}

string DtProducto::getCodigo(){
    return this->codigo;
}

string DtProducto::getdescripcion(){
    return this->descripcion;
}

float DtProducto::getprecio(){
    return this->precio;
}

int DtProducto::getcantVendido(){
    return this->cantVendido;
}