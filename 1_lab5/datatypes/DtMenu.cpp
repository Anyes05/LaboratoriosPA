#include "DtMenu.h"
#include <iostream>

using namespace std;

DtMenu::DtMenu(char codigo, string descripcion, float precio, string nombre, float descuento) : DtProducto(codigo, descripcion, precio) {
    cout << "Debug DtMenu::Constructor: Iniciando construcción" << endl;
    cout << "Debug DtMenu::Constructor: Código: " << codigo << endl;
    cout << "Debug DtMenu::Constructor: Descripción: " << descripcion << endl;
    cout << "Debug DtMenu::Constructor: Precio: " << precio << endl;
    cout << "Debug DtMenu::Constructor: Nombre: " << nombre << endl;
    cout << "Debug DtMenu::Constructor: Descuento: " << descuento << endl;

    this->nombre = nombre;
    this->descuentoMenu = descuento;
    
    cout << "Debug DtMenu::Constructor: Construcción completada" << endl;
}

DtMenu::DtMenu() : DtProducto('\0', "", 0.0) {
    cout << "Debug DtMenu::Constructor: Iniciando construcción por defecto" << endl;
    this->nombre = "";
    this->descuentoMenu = 0.0;
    cout << "Debug DtMenu::Constructor: Construcción por defecto completada" << endl;
}

DtMenu::~DtMenu(){}

string DtMenu::getNombre(){
    return this->nombre;
}

float DtMenu::getDescuentoMenu(){
    return this->descuentoMenu;
}
