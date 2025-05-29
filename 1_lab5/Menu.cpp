#include "Menu.h"

// Constructor
Menu::Menu(string codigo, string descripcion, float precio, string nom, string descMenu) : Producto(codigo, descripcion, precio)
{
    this->nombre=nom;
    this->descripcionMenu = descMenu;
    this-> productosComunes= new List(); // Inicializar con una instancia de ICollection
}

// destrcutor
Menu::~Menu(){}


//getters y setters

string Menu::getNombre(){
    return this->nombre;
}

string Menu::getDescripcionMenu(){
    return this->descripcionMenu;
}

ICollection *Menu::getProductosComunes(){
    return this->productosComunes;
}

void Menu::setNombre(string nom){
    this->nombre=nom;
}

void Menu::setDescrpcionMenu(string descMenu){
    this->descripcionMenu=descMenu;
}

void Menu::setProductosComunes(ICollection *productosComunes){
    if(this->productosComunes!= nullptr)
        delete this->productosComunes;
    this->productosComunes = productosComunes;
}
