#include "Producto.h"

Producto::Producto(string cod, string desc, float pre){
    this->codigo= cod;
    this->descripcion=desc;
    this->precio=pre;
}

Producto::~Producto(){}

string Producto::getCodigo(){
    return this->codigo;
}
string Producto::getDescripcion(){
    return this->descripcion;
}
float Producto::getPrecio(){
    return this->precio;
}

void Producto::setCodigo(string cod){
    this-> codigo=cod;
}

void Producto::setDescripcion(string desc){
    this-> descripcion=desc;
}

void Producto::setPrecio(float pre){
    this->precio=pre;
}