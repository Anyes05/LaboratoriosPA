#include "Comun-Menu.h"

//constructor
Comun_Menu::Comun_Menu(int cant){
    this->cantProducto= cant;

}

//destructor
Comun_Menu::~Comun_Menu(){}

int Comun_Menu::getCantProducto(){
    return this->cantProducto;
}

void Comun_Menu::setCantProducto(int cant){
    this->cantProducto=cant;
}