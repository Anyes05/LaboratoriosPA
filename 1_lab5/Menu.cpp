#include "Menu.h"

// Constructor
Menu::Menu(char codigo, string desc, float precio, string nom, float descMenu) : Producto(codigo, desc, precio)
{
    cout << "Debug Menu::Constructor: Iniciando construcción del menú" << endl;
    cout << "Debug Menu::Constructor: Código: " << codigo << endl;
    cout << "Debug Menu::Constructor: Descripción: " << desc << endl;
    cout << "Debug Menu::Constructor: Precio: " << precio << endl;
    cout << "Debug Menu::Constructor: Nombre: " << nom << endl;
    cout << "Debug Menu::Constructor: Descuento: " << descMenu << endl;

    this->nombre = nom;
    this->descuentoMenu = descMenu;
    
    cout << "Debug Menu::Constructor: Creando diccionario de productos comunes" << endl;
    this->productosComunes = new OrderedDictionary();
    cout << "Debug Menu::Constructor: Creando diccionario de comun_menu" << endl;
    this->comun_menu = new OrderedDictionary();
    cout << "Debug Menu::Constructor: Construcción completada" << endl;
}

// destrcutor
Menu::~Menu() {
    cout << "Debug Menu::Destructor: Iniciando destrucción" << endl;
    
    if (productosComunes != nullptr) {
        cout << "Debug Menu::Destructor: Liberando productosComunes" << endl;
        delete productosComunes;
        productosComunes = nullptr;
    }
    
    if (comun_menu != nullptr) {
        cout << "Debug Menu::Destructor: Liberando comun_menu" << endl;
        delete comun_menu;
        comun_menu = nullptr;
    }
    
    cout << "Debug Menu::Destructor: Destrucción completada" << endl;
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
    cout << "Debug Menu::darAltaMenu: Iniciando" << endl;
    cout << "Debug Menu::darAltaMenu: Código del producto común: " << comun->getCodigo() << endl;
    cout << "Debug Menu::darAltaMenu: Cantidad: " << cantidad << endl;

    // 1. Agregar el producto común al diccionario de productos comunes
    char codStr[2] = {comun->getCodigo(), '\0'};
    IKey *key = new String(codStr);
    cout << "Debug Menu::darAltaMenu: Agregando producto común al diccionario" << endl;
    productosComunes->add(key, comun);
    cout << "Debug Menu::darAltaMenu: Producto común agregado exitosamente" << endl;

    // 2. Crear la relación Comun_Menu y agregarla
    cout << "Debug Menu::darAltaMenu: Creando relación Comun_Menu" << endl;
    Comun_Menu *relacion = new Comun_Menu(cantidad, comun);
    cout << "Debug Menu::darAltaMenu: Agregando relación al diccionario" << endl;
    comun_menu->add(key, relacion);
    cout << "Debug Menu::darAltaMenu: Relación agregada exitosamente" << endl;
}