#include "Producto.h"

using namespace std;

//constructor
Producto::Producto(char codigo, string descripcion, float precio)
{
    this->codigo = codigo;
    this->descripcion = descripcion;
    this->precio = precio;
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
