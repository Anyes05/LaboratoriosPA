#include "Sistema.h"

Sistema *Sistema::instance = NULL;

Sistema::Sistema()
{
}

Sistema::~Sistema()
{
}

Sistema *Sistema::getInstance()
{
    if (instance == NULL)
        instance = new Sistema();
    return instance;
}

#include "Sistema.h"

// Declaraciones vacías para que el linker no dé error

bool Sistema::existeProducto(string codigo)
{
    return false; // por ahora, para compilar
}

ICollectible *Sistema::agregarMenu(string codigoMenu, string descripcion)
{
}

void Sistema::seleccionarProductoComun(string codigoComun, int cantProducto)
{
}

void Sistema::agregarProductoComun(string codigoComun, string descripcion, float precio)
{
}

void Sistema::darAltaProducto()
{
}

ICollectible *Sistema::listarParaAgregar(int idMesa)
{
}

void Sistema::seleccionarProductoAgregar(string codigo, int cantidad)
{
}

void Sistema::confirmarAgregarProducto()
{
}

void Sistema::ingresarMesa(int idMesa)
{
}

ICollectible *Sistema::productosVenta()
{
}

void Sistema::seleccionarProductoQuitar(string codigo, int cant)
{
}

void Sistema::quitarProductoVenta()
{
}

void Sistema::finalizarVenta(int nroMesa)
{
}

void Sistema::aplicarDescuento(int descuento)
{
}

DtFactura Sistema::generarFactura(DtVenta venta)
{
}

ICollectible *Sistema::mostrarProductos()
{
}

void Sistema::seleccionarProductoBaja(string codigo)
{
}

void Sistema::darBajaProducto()
{
}

ICollectible Sistema::ingresarIdMozo(int idMozo)
{
}

ICollectible Sistema::elegirMesas(int numero, int cantidad)
{
}

void Sistema::confirmarVentaEnMesa()
{
}
