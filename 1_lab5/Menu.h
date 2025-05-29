#ifndef MENU_H
#define MENU_H

#include "Producto.h"
#include "Comun.h"
#include "./datatypes/DtProdcuto.h"

#include "../ICollection/interfaces/ICollection.h"
#include "../ICollection/collections/List.h"

class DtProducto;

class Menu : public Producto, public virtual ICollectible  //una coleccion de Menu
{
private:
    string nombre;
    string descripcionMenu;
    ICollection * productosComunes; //coleccion de productos comunes que tiene un menu
    ICollection * comun_menu; //coleccion de comun_menu indica la cant de Productos l
public:
    Menu(string, string, float, string, string);
    ~Menu();

    string getNombre();
    string getDescripcionMenu();
    ICollection *getProductosComunes();

    void setNombre(string);
    void setDescrpcionMenu(string);
    void setProductosComunes(ICollection *productosComunes);

    void darBaja(); //funcion heredada y polimorfica
    bool contieneProducto(DtProducto);//creo que se pdeberia pasar solamente un codigo en esta y la siguiente funcion
    void eliminarProdcuto(DtProducto);
    bool esVacio(Menu*);
    void darAltaMenu(string codigoMenu, string descripcion);
    
};

#endif