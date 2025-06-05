#include "Producto.h"
#include <iostream>

using namespace std;

//constructor
Producto::Producto(char cod, string desc, float prec)
{
    cout << "Debug Producto::Constructor: Iniciando construcción" << endl;
    cout << "Debug Producto::Constructor: Código: " << cod << endl;
    cout << "Debug Producto::Constructor: Descripción: " << desc << endl;
    cout << "Debug Producto::Constructor: Precio: " << prec << endl;

    this->codigo = cod;
    this->descripcion = desc;
    this->precio = prec;

    cout << "Debug Producto::Constructor: Construcción completada" << endl;
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
