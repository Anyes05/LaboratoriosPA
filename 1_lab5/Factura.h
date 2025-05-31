#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include "ICollection/collections/List.h"
#include "datatypes/DtFecha.h"
#include "datatypes/DtHora.h"
#include "datatypes/DtVenta.h"
#include "datatypes/DtProducto.h"
#include "datatypes/DtHora.h"

using namespace std;


class Factura
{
    private:
        string codigo;
        DtFecha fecha;
        DtHora hora;
        DtVenta venta; // hace falta un dtVenta? siempre accedo desde venta a factura, creo que sobra 
        ICollection * productos;// lista de productos vendidos
    public:
        Factura(string, DtFecha, DtHora); // constructor
        virtual ~Factura(); // destructor
        // getters y setters
        string getCodigo();
        ICollection * getProductos();
        DtFecha getFecha(); 
        DtHora getHora(); 
        DtVenta getVenta(); 
        DtProducto getProducto();
        void setCodigo(string codigo);
        void setProductos(ICollection * productos);
        void setFecha(DtFecha fecha); 
        void setHora(DtHora hora);
        void setVenta(DtVenta venta);
        void setProducto(DtProducto producto);
};

#endif
