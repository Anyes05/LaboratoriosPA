#include "Menu.h"

// Constructor
Menu::Menu(char codigo, string descripcion, float precio, string nombre, float descuento) : Producto(codigo, descripcion, precio)
{
    this->nombre = nombre;
    this->descuentoMenu = descuento;
    this->productosComunes = new OrderedDictionary();
    this->comun_menu = new OrderedDictionary();
}

// destrcutor
Menu::~Menu() {
    if (productosComunes != nullptr) {
        delete productosComunes;
        productosComunes = nullptr;
    }
    
    if (comun_menu != nullptr) {
        delete comun_menu;
        comun_menu = nullptr;
    }
}

// getters y setters

string Menu::getNombre()
{
    return this->nombre;
}

float Menu::getDescuentoMenu()
{
    return this->descuentoMenu;
}

IDictionary* Menu::getProductosComunes() {
    IDictionary* comunes = new OrderedDictionary();

    IIterator* it = productosComunes->getIterator();
    while (it->hasCurrent()) {
        ICollectible* ic = it->getCurrent();
        Comun* c = dynamic_cast<Comun*>(ic);

        if (c != nullptr) {
            DtComun* dt = (DtComun*)c->getDT(); // obtenemos el DTO
            char codChar = dt->getCodigo();     // suponemos que getCodigo devuelve un char
            char codStr[2] = { codChar, '\0' }; // lo convertimos a const char*
            IKey* key = new String(codStr);     // construimos el String válido
            comunes->add(key, dt);              // lo agregamos
        }

        it->next();
    }

    delete it;
    return comunes;
}

IDictionary *Menu::getComun_Menu()
{
    return this->comun_menu;
}

void Menu::setNombre(string nom)
{
    this->nombre = nom;
}

void Menu::setDescuentoMenu(float descMenu)
{
    this->descuentoMenu = descMenu;
}

void Menu::setProductosComunes(IDictionary *productosComunes)
{
    if (this->productosComunes != nullptr)
        delete this->productosComunes;
    this->productosComunes = productosComunes;
}

void Menu::darBaja()
{
    // lógica aquí
}

DtProducto* Menu::getDT() {
    // Devuelve un DtProducto con los datos del menú
    return new DtProducto(this->getCodigo(), this->getDescripcion(), this->getPrecio());
}

void Menu::agregarProducto(IDictionary *pc)
{
    IIterator *it = pc->getIterator();
    while (it->hasCurrent())
    {
        ICollectible *ic = it->getCurrent();
        Comun *comun = dynamic_cast<Comun *>(ic); // casteamos a tipo real

        if (comun != nullptr)
        {
            char codigoChar = comun->getCodigo(); 
            char codigoStr[2] = {codigoChar, '\0'}; // convertir char a const char*
            IKey *key = new String(codigoStr); //clave de tipo texto
            productosComunes->add(key, comun); //agregamos al diccionario
        }

        it->next();
    }
    delete it;
}

void Menu::darAltaMenu(Comun *comun, int cantidad)
{
    char codStr[2] = {comun->getCodigo(), '\0'};
    String *key = new String(codStr);
    productosComunes->add(key, comun);

    Comun_Menu *relacion = new Comun_Menu(cantidad, comun);
    comun_menu->add(key, relacion);
}