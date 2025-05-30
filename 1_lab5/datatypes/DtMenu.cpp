#include "DtMenu.h"

DtMenu::DtMenu(string codigo, string descripcion, float precio, int cant, int cantidadMenu) : DtProducto(codigo, descripcion, precio, cantidadMenu){
    this->cantidad = cantidadMenu;
}

DtMenu::~DtMenu(){}

int DtMenu::getCantidad(){
    return this->cantidad;
}