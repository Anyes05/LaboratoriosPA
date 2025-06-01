#ifndef MENU_H
#define MENU_H

#include "Producto.h"
#include "Comun.h"
#include "./datatypes/DtProducto.h"
#include "./datatypes/DtComun.h"

#include "ICollection/interfaces/ICollection.h"
#include "ICollection/collections/OrderedDictionary.h"

class DtProducto;

class Menu : public Producto // una coleccion de Menu
{
private:
    string nombre;
    float descuentoMenu;
    IDictionary *productosComunes; // coleccion de productos comunes que tiene un menu
    IDictionary *comun_menu;       // coleccion de comun_menu indica la cant de Productos l
public:
    Menu(char, string, float, string, float);
    ~Menu();

    string getNombre();
    float getDescuentoMenu();
    IDictionary *getProductosComunes();
    IDictionary *getComun_Menu();

    void setNombre(string);
    void setDescuentoMenu(float);
    void setProductosComunes(IDictionary *productosComunes);
    void setComun_Menu(IDictionary *comun_menu);

    void darBaja();                    // funcion heredada y polimorfica
    bool contieneProducto(DtProducto); // creo que se pdeberia pasar solamente un codigo en esta y la siguiente funcion
    void eliminarProdcuto(DtProducto);
    bool esVacio(Menu *);
    void darAltaMenu(char codigoMenu, string descripcion);
    
    void agregarMenu(char codigoMenu, string descripcion);
    DtProducto *getDT();
    void agregarProducto(IDictionary *pc);
};

#endif