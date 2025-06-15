#ifndef DTPEDIDO_H
#define DTPEDIDO_H

#include <string>
#include "../ICollection/interfaces/ICollectible.h"

using namespace std;

class DtPedido : public ICollectible {
private:
    int codigoProducto;
    string descripcion;
    float precioUnitario;
    int cantidad;

public:
    DtPedido(int codigoProducto, string descripcion, float precioUnitario, int cantidad);

    int getCodigoProducto();
    string getDescripcion();
    float getPrecioUnitario();
    int getCantidad();
};

#endif
