#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
using namespace std;
class Factura : public ICollectible // una coleccion de facturas
{
    private:
        string codigo;
        //DtFecha fecha;
        //DtHora hora;
        //DtVenta venta;
        //DtProducto producto; // lista de productos vendidos
    public:
        Factura(string codigo); // constructor
        virtual ~Factura(); // destructor
        // getters y setters
        string getCodigo();
        // DtFecha getFecha(); 
        // DtHora getHora(); 
        // DtVenta getVenta(); 
        // DtProducto getProducto();
        void setCodigo(string codigo);
        void setFecha(/*DtFecha fecha*/); 
        void setHora(/*DtHora hora*/);
        void setVenta(/*DtVenta venta*/);
        void setProducto(/*DtProducto producto*/);
};

#endif
