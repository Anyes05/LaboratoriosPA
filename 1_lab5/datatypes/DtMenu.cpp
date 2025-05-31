#include "DtMenu.h"

DtMenu::DtMenu(string codigo, string descripcion, float precio, string nombre, float descuento) : DtProducto(codigo, descripcion, precio){
    this->nombre = nombre;
    this->descuentoMenu=descuento;
}

DtMenu::~DtMenu(){}

string DtMenu::getNombre(){
    return this->nombre;
}

float DtMenu::getDescuentoMenu(){
    return this->descuentoMenu;
}
