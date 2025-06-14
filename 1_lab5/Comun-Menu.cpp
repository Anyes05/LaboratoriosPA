#include "Comun-Menu.h"

using namespace std;

//constructor
Comun_Menu::Comun_Menu(int cant, Comun *pc)
{
    this->productoComun = pc;
    this->cantProducto = cant;
}

//destructor
Comun_Menu::~Comun_Menu(){}

int Comun_Menu::getCantProducto(){
    return this->cantProducto;
}

void Comun_Menu::setCantProducto(int cant){
    this->cantProducto=cant;
}

Comun * Comun_Menu::getComun(){ // 
    return this->productoComun;
}