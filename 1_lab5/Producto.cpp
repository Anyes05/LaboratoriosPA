#include "Producto.h"

//constructor
Producto::Producto(char cod, string desc, float pre){
    this->codigo= cod;
    this->descripcion=desc;
    this->precio=pre;
}

//destructor
Producto::~Producto(){}

char Producto::getCodigo(){
    return this->codigo;
}
string Producto::getDescripcion(){
    return this->descripcion;
}
float Producto::getPrecio(){
    return this->precio;
}

void Producto::setCodigo(char cod){
    this-> codigo=cod;
}

void Producto::setDescripcion(string desc){
    this-> descripcion=desc;
}

void Producto::setPrecio(float pre){
    this->precio=pre;
}

bool Producto::noExiste(char cod){
    return this->getCodigo() != cod;
}
