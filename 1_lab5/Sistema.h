#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Venta.h"
#include "Mozo.h"
#include "Mesa.h"
#include "Producto.h"

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    IDictionary *productos;
    IDictionary *ventas;
    IDictionary *mozos;
    IDictionary *mesas;

public:
    ~Sistema();
    static Sistema *getInstance();

    /*------ ALTA PRODCUTO -----*/
    bool existeProducto(string codigo); //retorna true si existe un producto con es codigo
    ICollectible *agregarMenu(string codigoMenu, string descripcion); // devuele una coleccion de DtComun
    void seleccionarProductoComun(string codigoComun, int cantProducto);
    void agregarProductoComun(string codigoComun, string descripcion, float precio);
    void darAltaProducto();
    
    ICollectible *listarParaAgregar(int idMesa); // devuele una coleccion de DtProducto
    void seleccionarProductoAgregar(string codigo, int cantidad);
    void confirmarAgregarProducto();
    void ingresarMesa(int idMesa);
    ICollectible *productosVenta(); // devuele una coleccion de DtProducto
    void seleccionarProductoQuitar(string codigo, int cant);
    void quitarProductoVenta();
    void finalizarVenta(int nroMesa);
    void aplicarDescuento(int descuento);
    DtFactura generarFactura(DtVenta venta);
    ICollectible *mostrarProductos(); // devuele una coleccion de DtProducto
    void seleccionarProductoBaja(string codigo);
    void darBajaProducto();
    ICollectible ingresarIdMozo(int idMozo);            // devuele una coleccion de DtAsignacion
    ICollectible elegirMesas(int numero, int cantidad); // devuele una coleccion de DtMesas
    void confirmarVentaEnMesa();
};

#endif