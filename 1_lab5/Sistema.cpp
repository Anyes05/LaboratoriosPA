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

// Declaraciones vacías para que el linker no dé error

bool Sistema::existeProducto(string codigo)
{
    IIterator *it = productos->getIterator();
    while(it->hasCurrent()){
        Producto *p = dynamic_cast<Producto *>(it->getCurrent());
        if(p != nullptr && !p->noExiste(codigo)) { // !noExiste -> sí existe  el producto
            delete it;
            return true;
        }
        it->next();
    }
    delete it;
    return false; // si no existe el codigo devuleve false
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

// ASIGNAR MESAS A MOZOS
// si no hay ventas sin facturar, o sea que en los links de "actual" no hay venta?
// la cantidad de mozos deberia de estar relacionada de alguna forma con la cantidad que estan dados de alta?
/*
DtAsignacion ** calcularAsignacion(int cantMesas, int cantMozos) {
    if (cantMesas <= 0 || cantMozos <= 0) { // podria ir en la capa de presentacion
        throw std::invalid_argument("La cantidad de mesas y mozos debe ser mayor a cero.");
    }
    int mesasPorMozo = cantMesas / cantMozos; // mesasXmozo
    int mesasExtra = cantMesas % cantMozos; // Mesas restantes

    DtAsignacion **asignaciones = new DtAsignacion*[cantMozos];
    int mesaActual = 1;

    IIterator* it = mozos->getIterator();
    int i = 0;

    while (it->hasCurrent() && i < cantMozos) {
        Mozo* mozo = dynamic_cast<Mozo*>(it->getCurrent());
        int cantidad = mesasPorMozo + (i < mesasExtra ? 1 : 0);
        int* mesasAsignadas = new int[cantidad];

        for (int j = 0; j < cantidad; j++) {
            mesasAsignadas[j] = mesaActual;
            Mesa* nuevaMesa = new Mesa(mesaActual);
            mozo->agregarMesa(nuevaMesa);
            mesaActual++;
        }

        asignaciones[i] = new DtAsignacion(mozo->getId(), mesasAsignadas, cantidad, false);
        delete[] mesasAsignadas;
        it->next();
        i++;
    }
    delete it;
    return asignaciones; // devuelve un arreglo de punteros a DtAsignacion
    
}
*/

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
