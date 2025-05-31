#ifndef MENU_H
#define MENU_H

#include "Producto.h"
#include "Comun.h"
#include "./datatypes/DtProducto.h"

#include "ICollection/interfaces/ICollection.h"
#include "ICollection/collections/List.h"

class DtProducto;

class Menu : public Producto //una coleccion de Menu
{
private:
    string nombre;
    float descuentoMenu;
    ICollection * productosComunes; //coleccion de productos comunes que tiene un menu
    ICollection * comun_menu; //coleccion de comun_menu indica la cant de Productos l
public:
    Menu(string, string, float, string, float);
    ~Menu();

    string getNombre();
    float getDescuentoMenu();
    ICollection *getProductosComunes();
    ICollection *getComun_Menu();

    void setNombre(string);
    void setDescuentoMenu(float);
    void setProductosComunes(ICollection *productosComunes);
    void setComun_Menu(ICollection *comun_menu);

    void darBaja(); //funcion heredada y polimorfica
    bool contieneProducto(DtProducto);//creo que se pdeberia pasar solamente un codigo en esta y la siguiente funcion
    void eliminarProdcuto(DtProducto);
    bool esVacio(Menu*);
    void darAltaMenu(string codigoMenu, string descripcion);
    
};

#endif