#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"

#include "Cliente.h"
#include "Local.h"
#include "Menu.h"
#include "Mesa.h"
#include "Mozo.h"
#include "Producto.h"
#include "Repartidor.h"
#include "Venta.h"
#include "Domicilio.h"
#include "Factura.h" 

#include "datatypes/DtComun.h"
#include "datatypes/DtMenu.h"

class Sistema : public ISistema {
private:
  Sistema();
  static Sistema *instance;
  IDictionary *productos;
  IDictionary *ventas;
  IDictionary *repartidores;
  IDictionary *empleados;
  IDictionary *mozos;
  IDictionary *mesas;
  ICollection *clientes;

  ICollection *mesasElegidasParaVenta;
  int idMozoSeleccionado;
  DtComun *productoComunTemp;
  DtMenu *menuTemp;
  IDictionary *productosComunSeleccionados;
  string nomEmp;
  Transporte medioSeleccionado;
  int ultimoIdEmpleado;
  Transporte medios[3];
  int cantidadMedios;
  int idE;
  DtCliente *clienteTemp;
  IDictionary *productosEnPedidoDomicilio;
  int idRepartidorSeleccionado;

public:
  ~Sistema();
  static Sistema *getInstance();

  /*------ ALTA PRODCUTO -----*/
  bool existeProducto(
      char codigo); // retorna true si existe un producto con es codigo
  IDictionary *
  agregarMenu(char codigoMenu,
              string descripcion); // devuele una coleccion de DtComun
  void seleccionarProductoComun(char codigoComun, int cantProducto);
  void agregarProductoComun(char codigoComun, string descripcion, float precio);
  void darAltaProducto();

  /*----- ALTA CLIENTE -----*/
  DtCliente altaCliente(string, string, DtDireccion);
  void confirmarAlta();
  void cancelarAlta();
  bool existeCliente(string);
  void listarClientes();

  /*------ ALTA EMPLEADO ------*/
  void agregarEmpleado(string nombre, int idIngresado);
  void listarMedioTransporte(); // devuelve una coleccion de DtMedioTransporte
  void elegirMedio(int opcion);
  void darAltaEmpleado();
  void mostrarEmpleados();
  bool existeEmpleado(int idEmpleado);
  string transporteToString(Transporte t);

  /*------ ASIGNAR MESAS A MOZOS ------*/
  ICollection *calcularAsignacion(int cantMesas, int cantMozos);

  /*------ INICIAR VENTA EN MESA ------*/
  DtAsignacion ingresarIdMozo(int idMozo); // devuele un DtAsignacion
  void elegirMesas(int numero);            // devuele una coleccion de DtMesas
  void confirmarVentaEnMesa();

  /*------ VENTA A DOMICILIO ------*/
  bool ventaDomicilio(string telefono); // Retorna true si el cliente existe
  IDictionary *listarProductos();       // retorna una coleccion de DtProducto
  void agregarProductoPedido(char codigo, int cantidad);
  ICollection *listarRepartidores(); // Retruna una coleccion de Dtrepartidor
  void asignarRepartidorDomicilio(int idRepartidor);
  DtFacturaDomicilio confirmarPedido();

  // ICollectible *listarParaAgregar(int idMesa); // devuele una coleccion de
  // DtProducto void seleccionarProductoAgregar(char codigo, int cantidad); void
  // confirmarAgregarProducto(); void ingresarMesa(int idMesa); ICollectible
  // *productosVenta(); // devuele una coleccion de DtProducto void
  // seleccionarProductoQuitar(char codigo, int cant); void
  // quitarProductoVenta(); void finalizarVenta(int nroMesa); void
  // aplicarDescuento(int descuento); DtFactura generarFactura(DtVenta venta);
  // ICollectible *mostrarProductos(); // devuele una coleccion de DtProducto
  // void seleccionarProductoBaja(char codigo);
  // void darBajaProducto();
};

#endif