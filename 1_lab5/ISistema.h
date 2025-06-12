#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
using namespace std;

#include "ICollection/interfaces/ICollectible.h"
#include "ICollection/interfaces/IDictionary.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/Integer.h"

#include "./datatypes/DtVenta.h"
#include "./datatypes/DtFactura.h"
#include "./datatypes/DtAsignacion.h"
#include "./datatypes/DtFacturaDomicilio.h"
#include "./datatypes/Transporte.h"
#include "./datatypes/DtCliente.h"

class DtVenta;

class ISistema
{
public:
    virtual ~ISistema();
    //virtual char normalizarCodigo(char codigo) = 0; // Normaliza el código del producto, si es un número lo convierte a char

    /*----- ALTA PRODUCTO -----*/
    virtual bool existeProducto(char codigo) = 0;
    virtual IDictionary *agregarMenu(char codigoMenu, string descripcion) = 0; // devuele una coleccion de DtComun
    virtual void seleccionarProductoComun(char codigoComun, int cantProducto) = 0;
    virtual void agregarProductoComun(char codigoComun, string descripcion, float precio) = 0;
    virtual void darAltaProducto() = 0;

    /*----- ALTA CLIENTE -----*/
    virtual DtCliente altaCliente(string, string, DtDireccion) = 0;
    virtual void confirmarAlta() = 0;
    virtual void cancelarAlta() = 0;
    virtual bool existeCliente(string) = 0;
    virtual void listarClientes() = 0;

    /*----- ALTA EMPLEADO -----*/
    virtual void agregarEmpleado(string nombre, int idIngresado) = 0;
    virtual void listarMedioTransporte() = 0; // devuelve una coleccion de DtMedioTransporte
    virtual void elegirMedio(int opcion) = 0;
    virtual void darAltaEmpleado() = 0;
    virtual void mostrarEmpleados() = 0;
    virtual bool existeEmpleado(int idEmpleado) = 0;
    virtual string transporteToString(Transporte t) = 0;

    /*------ ASIGNAR MESAS A MOZOS ------*/
    virtual ICollection *calcularAsignacion(int cantMesas, int cantMozos) = 0;

    /*------ INICIAR VENTA EN MESA ------*/
    virtual DtAsignacion* ingresarIdMozo(int idMozo) = 0;
    virtual void elegirMesas(int numero) = 0; // devuele una coleccion de DtMesas
    virtual void confirmarVentaEnMesa() = 0;

    /*------ VENTA A DOMICILIO ------*/
    virtual bool ventaDomicilio(char telefono) = 0; // Returns true if client exists, false otherwise
    virtual IDictionary *listarProductos() = 0;     // Returns a collection of DtProducto
    virtual void agregarProductoPedido(char codigo, int cantidad) = 0;
    virtual ICollection *listarRepartidores() = 0; // Returns a collection of DtRepartidor
    virtual void asignarRepartidorDomicilio(int idRepartidor) = 0;
    virtual DtFacturaDomicilio confirmarPedido() = 0;

    /*------ AGREGAR PRODUCTO A UNA VENTA ------*/
    virtual ICollection *listarParaAgregar(int idMesa) = 0;                       // devuele una coleccion de DtProducto
    virtual void seleccionarProductoAgregar(char codigo, int cantidad) = 0;
    virtual void confirmarAgregarProducto() = 0;

    /*------- QUITAR PRODUCTO A UNA VENTA -------*/
    virtual void ingresarMesa(int idMesa) = 0;
    virtual ICollection*productosVenta() = 0;                    // devuele una coleccion de DtProducto
    virtual void seleccionarProductoQuitar(char codigo, int cant) = 0;
    virtual void quitarProductoVenta() = 0;
    virtual ICollection* pedidosVentaActual() = 0; // funcion auxiliar, me sirve para ver la cant de pedido en la venta actual y mostrarlo
    // virtual void finalizarVenta(int nroMesa) = 0;
    // virtual void aplicarDescuento(int descuento) = 0;
    // virtual DtFactura generarFactura(DtVenta venta) = 0;
    // virtual ICollectible *mostrarProductos() = 0;                   // devuele una coleccion de DtProducto

    // virtual void seleccionarProductoBaja(string codigo) = 0;
    // virtual void darBajaProducto() = 0;
};

#endif