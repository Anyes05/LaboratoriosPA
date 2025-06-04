#include "DtMenu.h"

DtMenu::DtMenu(char codigo, string descripcion, float precio, string nombre, float descuento) : DtProducto(codigo, descripcion, precio){
    this->nombre = nombre;
    this->descuentoMenu=descuento;
}
DtMenu::DtMenu() {
    this->nombre = "";
    this->descuentoMenu= 0.0;
}


DtMenu::~DtMenu(){}

string DtMenu::getNombre(){
    return this->nombre;
}

float DtMenu::getDescuentoMenu(){
    return this->descuentoMenu;
}
