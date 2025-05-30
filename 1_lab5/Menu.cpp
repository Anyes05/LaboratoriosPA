#include "Menu.h"

// Constructor
Menu::Menu(string codigo, string desc, float precio, string nom, float descMenu) : Producto(codigo, descripcion, precio)
{
    this->nombre=nom;
    this->descuentoMenu = descMenu;
    this-> productosComunes= new List(); // Inicializar con una instancia de ICollection
    this->comun_menu = new List(); 
}

// destrcutor
Menu::~Menu(){}


//getters y setters

string Menu::getNombre(){
    return this->nombre;
}

float Menu::getDescuentoMenu(){
    return this->descuentoMenu;
}

ICollection *Menu::getProductosComunes(){
    return this->productosComunes;
}

ICollection *Menu::getComun_Menu(){
    return this->comun_menu;
}

void Menu::setNombre(string nom){
    this->nombre=nom;
}

void Menu::setDescuentoMenu(float descMenu){
    this->descuentoMenu=descMenu;
}

void Menu::setProductosComunes(ICollection *productosComunes){
    if(this->productosComunes!= nullptr)
        delete this->productosComunes;
    this->productosComunes = productosComunes;
}

void Menu::darBaja() {
    // lógica aquí
}
