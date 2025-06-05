#include "Comun-Menu.h"
#include <iostream>

using namespace std;

//constructor
Comun_Menu::Comun_Menu(int cant, Comun * pc){
    cout << "Debug Comun_Menu::Constructor: Iniciando construcción" << endl;
    cout << "Debug Comun_Menu::Constructor: Cantidad: " << cant << endl;
    cout << "Debug Comun_Menu::Constructor: Producto común: " << (pc != nullptr ? "válido" : "null") << endl;
    
    this->productoComun = pc;
    this->cantProducto = cant;
    
    cout << "Debug Comun_Menu::Constructor: Construcción completada" << endl;
}

//destructor
Comun_Menu::~Comun_Menu(){}

int Comun_Menu::getCantProducto(){
    return this->cantProducto;
}

void Comun_Menu::setCantProducto(int cant){
    this->cantProducto=cant;
}