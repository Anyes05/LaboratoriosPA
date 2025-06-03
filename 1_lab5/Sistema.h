#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Venta.h"
#include "Mozo.h"
#include "Mesa.h"
#include "Producto.h"
#include "Menu.h"
#include "datatypes/DtAsignacion.h"
#include "ICollection/Integer.h"
#include "Cliente.h"
#include "datatypes/DtCliente.h"

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    IDictionary *productos = new OrderedDictionary();
    IDictionary *ventas = new OrderedDictionary();
    IDictionary *mozos = new OrderedDictionary();
    IDictionary *mesas = new OrderedDictionary();
    IDictionary *clientes = new OrderedDictionary();

    // Variables para recordar la selección
    Comun *productoComunSeleccionado = nullptr;
    IDictionary *productosSeleccionados = new OrderedDictionary(); // clave: código, valor: cantidad (Integer)
    int cantidadProductoComunSeleccionada = 0;
    Menu *menuRecordado = nullptr;
    IDictionary *productosComunSeleccionados = new OrderedDictionary();

    Cliente *clienteTemp = nullptr; //guadra cliente temporalmente hasta confirmar

public:
    ~Sistema();
    static Sistema *getInstance();

    /*------ ALTA PRODCUTO -----*/

    bool existeProducto(char codigo);                              // retorna true si existe un producto con es codigo
    IDictionary *agregarMenu(char codigoMenu, string descripcion); // devuele una coleccion de DtComun
    void seleccionarProductoComun(char codigoComun, int cantProducto);
    void agregarProductoComun(char codigoComun, string descripcion, float precio);
    void darAltaProducto();

    /*------ ASIGNAR MESAS A MOZOS ------*/
    DtAsignacion **calcularAsignacion(int cantMesas, int cantMozos);

    /*------ INICIAR VENTA EN MESA ------*/
    DtAsignacion ingresarIdMozo(int idMozo); // devuele un DtAsignacion
    ICollection *elegirMesas(int numero);    // devuele una coleccion de DtMesas
    // void confirmarVentaEnMesa();

    // ICollectible *listarParaAgregar(int idMesa); // devuele una coleccion de DtProducto
    // void seleccionarProductoAgregar(char codigo, int cantidad);
    // void confirmarAgregarProducto();
    // void ingresarMesa(int idMesa);
    // ICollectible *productosVenta(); // devuele una coleccion de DtProducto
    // void seleccionarProductoQuitar(char codigo, int cant);
    // void quitarProductoVenta();
    // void finalizarVenta(int nroMesa);
    // void aplicarDescuento(int descuento);
    // DtFactura generarFactura(DtVenta venta);
    // ICollectible *mostrarProductos(); // devuele una coleccion de DtProducto
    // void seleccionarProductoBaja(char codigo);
    // void darBajaProducto();

    DtCliente altaCliente(char, string, DtDireccion);
    void confirmarAlta();
    void cancelarAlta();
    bool existeCliente(char);
};

#endif