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
    std::cout << "[Depuración] Destructor de Menu llamado para: " << this->nombre << " (" << this->getCodigo() << ")" << std::endl;
    std::cout << "[Depuración] Direcciones antes de liberar: productosComunes=" << productosComunes << ", comun_menu=" << comun_menu << std::endl;
    if (productosComunes != nullptr) {
        delete productosComunes;
        productosComunes = nullptr;
        std::cout << "[Depuración] productosComunes liberado." << std::endl;
    }
    if (comun_menu != nullptr) {
        delete comun_menu;
        comun_menu = nullptr;
        std::cout << "[Depuración] comun_menu liberado." << std::endl;
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

bool Menu::contieneProducto(char codigo)
{
    char codStr[2] = {codigo, '\0'};
    IKey *key = new String(codStr);
    bool existe = this->productosComunes->member(key);
    delete key;
    return existe;
}

void Menu::eliminarProductoComun(char codigo)
{
    std::cout << "[Depuración] INICIO eliminarProductoComun para código: " << codigo << std::endl;
    std::cout << "[Depuración] Direcciones: productosComunes=" << productosComunes << ", comun_menu=" << comun_menu << std::endl;
    char codStr[2] = {codigo, '\0'};
    IKey *key = new String(codStr);

    // 1. Eliminar de comun_menu
    if (comun_menu) {
        std::cout << "[Depuración] comun_menu existe. Buscando clave..." << std::endl;
        if (comun_menu->member(key)) {
            std::cout << "[Depuración] Clave encontrada en comun_menu. Intentando hacer cast a Comun_Menu..." << std::endl;
            Comun_Menu* relacion = dynamic_cast<Comun_Menu*>(comun_menu->find(key));
            if (relacion) {
                std::cout << "[Depuración] Cast a Comun_Menu exitoso. Eliminando relación..." << std::endl;
                comun_menu->remove(key);
                std::cout << "[Depuración] Relación eliminada. Liberando memoria de la relación..." << std::endl;
                delete relacion;
                std::cout << "[Depuración] Memoria de la relación liberada." << std::endl;
            } else {
                std::cout << "[Advertencia] No se pudo hacer cast a Comun_Menu para código: " << codigo << std::endl;
            }
        } else {
            std::cout << "[Advertencia] Clave NO encontrada en comun_menu para código: " << codigo << std::endl;
        }
    } else {
        std::cout << "[Error] comun_menu es nullptr!" << std::endl;
    }

    // 2. Eliminar de productosComunes
    if (productosComunes) {
        std::cout << "[Depuración] productosComunes existe. Buscando clave..." << std::endl;
        if (productosComunes->member(key)) {
            std::cout << "[Depuración] Clave encontrada en productosComunes. Eliminando referencia..." << std::endl;
            productosComunes->remove(key); // Solo elimina la referencia, NO el objeto
            std::cout << "[Depuración] Referencia eliminada de productosComunes." << std::endl;
        } else {
            std::cout << "[Advertencia] Clave NO encontrada en productosComunes para código: " << codigo << std::endl;
        }
    } else {
        std::cout << "[Error] productosComunes es nullptr!" << std::endl;
    }

    delete key;
    std::cout << "[Depuración] FIN eliminarProductoComun para código: " << codigo << std::endl;
}

bool Menu::esVacio(Menu *menu)
{
    return menu->getProductosComunes()->isEmpty();
}

void Menu::darBaja()
{
    // Eliminar todas las referencias a productos comunes
    IIterator *it = productosComunes->getIterator();
    while (it->hasCurrent())
    {
        Comun* comun = dynamic_cast<Comun*>(it->getCurrent());
        if (comun != nullptr) {
            char codigoChar = comun->getCodigo();
            char codigoStr[2] = {codigoChar, '\0'};
            IKey* key = new String(codigoStr);
            it->next(); // Avanzar antes de eliminar
            productosComunes->remove(key);
            delete key;
        } else {
            it->next();
        }
    }
    delete it;

    // Eliminar todas las relaciones Comun_Menu y liberar memoria
    IIterator* it2 = comun_menu->getIterator();
    while (it2->hasCurrent())
    {
        Comun_Menu* relacion = dynamic_cast<Comun_Menu*>(it2->getCurrent());
        if (relacion != nullptr) {
            char codigoChar = relacion->getComun()->getCodigo();
            char codigoStr[2] = {codigoChar, '\0'};
            IKey* key = new String(codigoStr);
            it2->next(); // Avanzar antes de eliminar
            comun_menu->remove(key);
            delete relacion; // LIBERAR MEMORIA
            delete key;
        } else {
            it2->next();
        }
    }
    delete it2;
}

DtProducto* Menu::getDT() {
    return new DtMenu(
        this->getCodigo(),
        this->getDescripcion(),
        this->getPrecio(),
        this->getCantidadVendida(), 
        this->getNombre(),
        this->getDescuentoMenu()
    );
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
            char codStr1[2] = {comun->getCodigo(), '\0'};
            String *key1 = new String(codStr1);
            productosComunes->add(key1, comun);
        }

        it->next();
    }
    delete it;
}

void Menu::darAltaMenu(Comun *comun, int cantidad)
{
    char codStr1[2] = {comun->getCodigo(), '\0'};
    String *key1 = new String(codStr1);
    productosComunes->add(key1, comun);

    char codStr2[2] = {comun->getCodigo(), '\0'};
    String *key2 = new String(codStr2);
    Comun_Menu *relacion = new Comun_Menu(cantidad, comun);
    comun_menu->add(key2, relacion);
}