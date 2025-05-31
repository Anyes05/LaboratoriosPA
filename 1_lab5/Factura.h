#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "ICollection/collections/List.h"
#include "DataTypes/DtFecha.h"
#include "DataTypes/DtHora.h"
#include "DataTypes/DtVenta.h"
#include "DataTypes/DtProducto.h"
#include "DataTypes/DtHora.h"

using namespace std;
class Factura : public ICollectible // una coleccion de facturas
{
    private:
        string codigo;
        DtFecha fecha;
        DtHora hora;
        DtVenta venta; 
        ICollection * productos;// lista de productos vendidos
    public:
        Factura(string, DtFecha, DtHora, DtVenta); // constructor
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
