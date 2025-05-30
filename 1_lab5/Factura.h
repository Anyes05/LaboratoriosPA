#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "ICollection/collections/ListIterator.h" 

using namespace std;
class Factura : public ICollectible // una coleccion de facturas
{
    private:
        string codigo;
        //DtFecha fecha;
        //DtHora hora;
        //DtVenta venta;
        ListIterator productos;// lista de productos vendidos
    public:
        Factura(string codigo, const ListIterator& productos); // constructor
        virtual ~Factura(); // destructor
        // getters y setters
        string getCodigo();
        ListIterator getProductos();
        // DtFecha getFecha(); 
        // DtHora getHora(); 
        // DtVenta getVenta(); 
        // DtProducto getProducto();
        void setCodigo(string codigo);
        void setProductos(ListIterator productos);
        void setFecha(/*DtFecha fecha*/); 
        void setHora(/*DtHora hora*/);
        void setVenta(/*DtVenta venta*/);
        void setProducto(/*DtProducto producto*/);
};

#endif
