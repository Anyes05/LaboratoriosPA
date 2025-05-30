#include "DtProducto.h"

DtProducto::DtProducto(string codigo, string desc, float precio, int cant){
    this->codigo = codigo;
    this->descripcion = desc;
    this->precio = precio;
    this->cantVendido = cant;
}
DtProducto::DtProducto() {
    this->codigo = "";
    this->descripcion = "";
    this->precio = 0.0;
    this->cantVendido = 0;
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