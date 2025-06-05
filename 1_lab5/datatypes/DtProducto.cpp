#include "DtProducto.h"
#include <iostream>

using namespace std;

DtProducto::DtProducto(char codigo, string descripcion, float precio) {
    cout << "Debug DtProducto::Constructor: Iniciando construcción" << endl;
    cout << "Debug DtProducto::Constructor: Código: " << codigo << endl;
    cout << "Debug DtProducto::Constructor: Descripción: " << descripcion << endl;
    cout << "Debug DtProducto::Constructor: Precio: " << precio << endl;

    this->codigo = codigo;
    this->descripcion = descripcion;
    this->precio = precio;

    cout << "Debug DtProducto::Constructor: Construcción completada" << endl;
}

DtProducto::DtProducto() {
    this->codigo = '\0';
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
