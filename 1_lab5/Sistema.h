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
        static Sistema * instance;
public:
    ~Sistema();
    static Sistema *getInstance();
    bool existeProducto(string codigo);
    ICollectible *agregarMenu(string codigoMenu, string descripcion); // devuele una coleccion de DtComun
    void seleccionarProductoComun(string codigoComun, int cantProducto);
    void agregarProductoComun(string codigoComun, string descripcion, float precio);
    void darAltaProducto();
    ICollectible *listarParaAgregar(int idMesa);                       // devuele una coleccion de DtProducto
    void seleccionarProducto(int idMesa, string codigo, int cantidad); // es igual a otro metodo
    void confirmarAgregarProducto();
    void ingresarMesa(int idMesa);
    ICollectible *productosVenta();                    // devuele una coleccion de DtProducto
    void seleccionarProducto(string codigo, int cant); // es igual a otro metodo
    void confirmar(string codigo, int cant);           // que es lo que confirma?
    void finalizarVenta(int nroMesa);
    void aplicarDescuento(int descuento);
    DtFactura generarFactura(DtVenta venta);
    ICollectible *mostrarProductos();                   // devuele una coleccion de DtProducto
    void seleccionarProducto(string codigo);            // OTRA VEZ SELECCIONAR PRODUCTO T-T
    void confirmar();                                   // que nos esta confirmando?
    ICollectible ingresarIdMozo(int idMozo);            // devuele una coleccion de DtAsignacion
    ICollectible elegirMesas(int numero, int cantidad); // devuele una coleccion de DtMesas
    void confirmarVentaEnMesa();
};

#endif