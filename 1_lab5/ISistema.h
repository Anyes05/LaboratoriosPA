#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include <set>
using namespace std;
#include "ICollection/interfaces/ICollectible.h"
#include "ICollection/interfaces/IDictionary.h"
#include "ICollection/interfaces/ICollection.h"

#include "./datatypes/DtVenta.h"
#include "./datatypes/DtFactura.h"
#include "./datatypes/DtAsignacion.h"

#include "./datatypes/DtMedioTransporte.h"
#include "ICollection/interfaces/ICollection.h"
#include "./datatypes/Transporte.h"

#include "./datatypes/DtCliente.h"

class DtVenta;

class ISistema
{
public:
    virtual ~ISistema();
    virtual bool existeProducto(char codigo) = 0;
    virtual IDictionary *agregarMenu(char codigoMenu, string descripcion) = 0; // devuele una coleccion de DtComun
    virtual void seleccionarProductoComun(char codigoComun, int cantProducto) = 0;
    virtual void agregarProductoComun(char codigoComun, string descripcion, float precio) = 0;
    virtual void darAltaProducto() = 0;

    virtual DtAsignacion **calcularAsignacion(int cantMesas, int cantMozos) = 0;

    virtual DtAsignacion ingresarIdMozo(int idMozo) = 0;
    virtual ICollection *elegirMesas(int numero) = 0; // devuele una coleccion de DtMesas
    // virtual void confirmarVentaEnMesa() = 0;

    virtual void agregarEmpleado(string nombre) = 0;
    virtual set<Transporte> listarMedioTransporte() = 0; // devuelve una coleccion de DtMedioTransporte
    virtual void elegirMedio(Transporte medio) = 0;
    virtual void darAltaEmpleado() = 0;
    virtual void mostrarEmpleados() = 0;

    virtual DtCliente altaCliente(char, string, DtDireccion) = 0;
    virtual void confirmarAlta() = 0;
    virtual void cancelarAlta() = 0;
    virtual bool existeCliente(char) = 0;

    // virtual ICollectible *listarParaAgregar(int idMesa) = 0;                       // devuele una coleccion de DtProducto
    // virtual void seleccionarProductoAgregar(char codigo, int cantidad) = 0;
    // virtual void confirmarAgregarProducto() = 0;
    // virtual void ingresarMesa(int idMesa) = 0;
    // virtual ICollectible *productosVenta() = 0;                    // devuele una coleccion de DtProducto
    // virtual void seleccionarProductoQuitar(char codigo, int cant) = 0;
    // virtual void quitarProductoVenta() = 0;
    // virtual void finalizarVenta(int nroMesa) = 0;
    // virtual void aplicarDescuento(int descuento) = 0;
    // virtual DtFactura generarFactura(DtVenta venta) = 0;
    // virtual ICollectible *mostrarProductos() = 0;                   // devuele una coleccion de DtProducto

    // virtual void seleccionarProductoBaja(string codigo) = 0;
    // virtual void darBajaProducto() = 0;

};

#endif