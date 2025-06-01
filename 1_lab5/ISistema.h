#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
using namespace std;
#include "ICollection/interfaces/ICollectible.h"
#include "ICollection/interfaces/IDictionary.h"
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
    virtual void seleccionarProductoAgregar(string codigo, int cantidad) = 0;
    virtual void confirmarAgregarProducto() = 0;
    virtual void ingresarMesa(int idMesa) = 0;
    virtual ICollectible *productosVenta() = 0;                    // devuele una coleccion de DtProducto
    virtual void seleccionarProductoQuitar(string codigo, int cant) = 0;
    virtual void quitarProductoVenta() = 0;         
    virtual void finalizarVenta(int nroMesa) = 0;
    virtual void aplicarDescuento(int descuento) = 0;
    virtual DtFactura generarFactura(DtVenta venta) = 0;
    virtual ICollectible *mostrarProductos() = 0;                   // devuele una coleccion de DtProducto
    virtual void seleccionarProductoBaja(string codigo) = 0;           
    virtual void darBajaProducto() = 0;                                 
    virtual ICollectible ingresarIdMozo(int idMozo) = 0;            // devuele una coleccion de DtAsignacion
    virtual ICollectible elegirMesas(int numero, int cantidad) = 0; // devuele una coleccion de DtMesas
    virtual void confirmarVentaEnMesa() = 0;

    virtual DtAsignacion ** calcularAsignacion(int cantMesas, int cantMozos) = 0;
};

#endif