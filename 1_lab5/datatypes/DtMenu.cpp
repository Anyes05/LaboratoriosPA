#include "DtMenu.h"

using namespace std;

DtMenu::DtMenu(char codigo, string descripcion, float precio, string nombre, float descuento) : DtProducto(codigo, descripcion, precio)
{
    this->nombre = nombre;
    this->descuentoMenu = descuento;
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
