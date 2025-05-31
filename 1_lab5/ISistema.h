#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
using namespace std;
#include "ICollection/interfaces/ICollectible.h"
#include "./datatypes/DtVenta.h"
#include "./datatypes/DtFactura.h"
class DtVenta;

class ISistema
{
public:
    ~ISistema();
    virtual bool existeProducto(string codigo) = 0;
    virtual ICollectible *agregarMenu(string codigoMenu, string descripcion) = 0; // devuele una coleccion de DtComun
    virtual void seleccionarProductoComun(string codigoComun, int cantProducto) = 0;
    virtual void agregarProductoComun(string codigoComun, string descripcion, float precio) = 0;
    virtual void darAltaProducto() = 0;
    virtual ICollectible *listarParaAgregar(int idMesa) = 0;                       // devuele una coleccion de DtProducto
    virtual void seleccionarProducto(int idMesa, string codigo, int cantidad) = 0; // es igual a otro metodo
    virtual void confirmarAgregarProducto() = 0;
    virtual void ingresarMesa(int idMesa) = 0;
    virtual ICollectible *productosVenta() = 0;                    // devuele una coleccion de DtProducto
    virtual void seleccionarProducto(string codigo, int cant) = 0; // es igual a otro metodo
    virtual void confirmar(string codigo, int cant) = 0;           // que es lo que confirma?
    virtual void finalizarVenta(int nroMesa) = 0;
    virtual void aplicarDescuento(int descuento) = 0;
    virtual DtFactura generarFactura(DtVenta venta) = 0;
    virtual ICollectible *mostrarProductos() = 0;                   // devuele una coleccion de DtProducto
    virtual void seleccionarProducto(string codigo) = 0;            // OTRA VEZ SELECCIONAR PRODUCTO T-T
    virtual void confirmar() = 0;                                   // que nos esta confirmando?
    virtual ICollectible ingresarIdMozo(int idMozo) = 0;            // devuele una coleccion de DtAsignacion
    virtual ICollectible elegirMesas(int numero, int cantidad) = 0; // devuele una coleccion de DtMesas
    virtual void confirmarVentaEnMesa() = 0;
};

#endif