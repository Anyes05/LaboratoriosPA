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

/*----- DAR DE ALTA PRODUCTO -----*/

bool Sistema::existeProducto(char codigo)
{
    IIterator *it = productos->getIterator();
    while (it->hasCurrent())
    {
        Producto *p = dynamic_cast<Producto *>(it->getCurrent());
        if (p != nullptr && !p->noExiste(codigo))
        { // !noExiste -> sí existe  el producto
            delete it;
            return true;
        }
        it->next();
    }
    delete it;
    return false; // si no existe el codigo devuleve false
}

IDictionary *Sistema::agregarMenu(char codigoMenu, string descripcion)
{
    // Crear el menú
    Menu *nuevoMenu = new Menu(codigoMenu, descripcion, /*precio*/ 0, /*nombre*/ "", /*descuento*/ 0);

    // Guardar en productos
    char codStr[2] = {codigoMenu, '\0'};
    IKey *key = new String(codStr);
    productos->add(key, nuevoMenu);

    // Listar todos los productos comunes y devolverlos como DtComun
    IIterator *it = productos->getIterator();
    OrderedDictionary *listaDtComunes = new OrderedDictionary();

    while (it->hasCurrent())
    {
        Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
        Comun *comun = dynamic_cast<Comun *>(prod);
        if (comun != nullptr)
        {
            DtComun *dt = dynamic_cast<DtComun *>(comun->getDT());
            // Usa el código del producto común como clave
            char codComunStr[2] = {comun->getCodigo(), '\0'};
            IKey *keyComun = new String(codComunStr);
            listaDtComunes->add(keyComun, dt);
        }
        it->next();
    }
    delete it;

    // Devolver la colección de DtComun
    return listaDtComunes;
}
void Sistema::seleccionarProductoComun(char codigoComun, int cantProducto)
{
    // Buscar el producto Comun en la colección de productos
    char codStr[2] = {codigoComun, '\0'};
    IKey *key = new String(codStr);

    if (!productos->member(key))
    {
        delete key;
        throw invalid_argument("No existe un producto Comun con ese código.");
    }

    Producto *prod = dynamic_cast<Producto *>(productos->find(key));
    Comun *comun = dynamic_cast<Comun *>(prod);

    if (comun == nullptr)
    {
        delete key;
        throw invalid_argument("El producto con ese código no es de tipo Comun.");
    }

    // Recordar el objeto Comun y la cantidad seleccionada
    productoComunSeleccionado = comun;
    cantidadProductoComunSeleccionada = cantProducto;

    delete key;
}

void Sistema::agregarProductoComun(char codigoComun, string descripcion, float precio) {
    // Verificar si ya existe un producto con ese código usando tu función
    if (existeProducto(codigoComun)) {
        throw invalid_argument("Ya existe un producto con ese código.");
    }

    // Crear el producto Comun
    Comun* nuevoComun = new Comun(codigoComun, descripcion, precio);

    // Guardar en la colección de productos
    char codStr[2] = {codigoComun, '\0'};
    IKey* key = new String(codStr);

    productos->add(key, nuevoComun);
}

// void Sistema::darAltaProducto()
// {
// }

// ASIGNAR MESAS A MOZOS
// si no hay ventas sin facturar, o sea que en los links de "actual" no hay venta?
// la cantidad de mozos deberia de estar relacionada de alguna forma con la cantidad que estan dados de alta?
DtAsignacion **Sistema::calcularAsignacion(int cantMesas, int cantMozos)
{
    if (cantMesas <= 0 && cantMozos <= 0)
    { // primero chequeo que las cantidades que me pasan sean validas
        throw std::invalid_argument("La cantidad de mesas y mozos debe ser mayor a cero.");
    } // podria ir en la capa de presentacion(?
    int mesasPorMozo = cantMesas / cantMozos; // mesasXmozo
    int mesasExtra = cantMesas % cantMozos;   // Mesas restantes

    if (mozos == nullptr)
    { // chequeo si hay mozos en la coleccion. o podria utilizar el metodo isEmpty() de IDictionary
        throw std::runtime_error("La colección de mozos no está inicializada.");
    }
    if (mozos->getSize() <= cantMozos)
    { // chequeo si hay suficientes mozos. No podria pasar por parametro una cantMozos mayor a los que estan dados de alta en la coleccion mozos
        throw std::runtime_error("No hay suficientes mozos para asignar las mesas.");
    }

    DtAsignacion **asignaciones = new DtAsignacion *[cantMozos]; // creo un arreglo de punteros a DtAsignacion, que sera lo que devuelva al final de la funcion
    int mesaActual = 1;

    // tengo que crear la coleccion mesa e ir añadiando las mesas a cada mozo segun la cantidad de mesas que se me pasan en cantMesas
    // de esto en realidad se encarga el mozo, con la funcion agregarMesa
    IIterator *it = mozos->getIterator();
    int i = 0;

    while (it->hasCurrent() && i < cantMozos)
    {
        Mozo *mozo = dynamic_cast<Mozo *>(it->getCurrent());
        int cantidad = mesasPorMozo + (i < mesasExtra ? 1 : 0);
        int *mesasAsignadas = new int[cantidad];

        for (int j = 0; j < cantidad; j++)
        {
            mesasAsignadas[j] = mesaActual;
            Mesa *nuevaMesa = new Mesa(mesaActual);
            mozo->agregarMesa(nuevaMesa);

            // tambien tengo que agregar la mesa a la coleccion global del sistema
            IKey *keyMesa = new Integer(mesaActual);
            /*this-> ?*/ mesas->add(keyMesa, nuevaMesa); // agrego la mesa a la coleccion de mesas del sistema

            mesaActual++;
        }

        asignaciones[i] = new DtAsignacion(mozo->getIdEmpleado(), mesasAsignadas, cantidad, false);
        delete[] mesasAsignadas;
        it->next();
        i++;
    }
    delete it;
    return asignaciones; // devuelve un arreglo de punteros a DtAsignacion
}

// ICollectible *Sistema::listarParaAgregar(int idMesa)
// {
// }

// void Sistema::seleccionarProductoAgregar(char codigo, int cantidad)
// {
// }

// void Sistema::confirmarAgregarProducto()
// {
// }

// void Sistema::ingresarMesa(int idMesa)
// {
// }

// ICollectible *Sistema::productosVenta()
// {
// }

// void Sistema::seleccionarProductoQuitar(char codigo, int cant)
// {
// }

// void Sistema::quitarProductoVenta()
// {
// }

// void Sistema::finalizarVenta(int nroMesa)
// {
// }

// void Sistema::aplicarDescuento(int descuento)
// {
// }

// DtFactura Sistema::generarFactura(DtVenta venta)
// {
// }

// ICollectible *Sistema::mostrarProductos()
// {
// }

// void Sistema::seleccionarProductoBaja(char codigo)
// {
// }

// void Sistema::darBajaProducto()
// {
// }

// INICIAR VENTA EN MESA

DtAsignacion Sistema::ingresarIdMozo(int idMozo)
{
    IIterator *it = mozos->getIterator();
    while (it->hasCurrent())
    {
        Mozo *mozo = dynamic_cast<Mozo *>(it->getCurrent()); // chequeo de que mozo sea un puntero a Mozo y no a otro tipo de empleado
        if (mozo != nullptr && mozo->getIdEmpleado() == idMozo)
        {
            delete it;
            int *mesasAsignadas = mozo->getMesasId();                                                // obtiene las mesas asignadas al mozo
            return DtAsignacion(mozo->getIdEmpleado(), mesasAsignadas, mozo->getCantMesas(), false); // retorno dtasignacion con el id del mozo, las mesas asignadas y la cantidad de mesas
        }
        it->next();
    }
    // **IMPORTANTE**: si no encontrás el mozo, igualmente debes devolver algo, porque el retorno es no void
    return DtAsignacion(); // o lanza excepción si querés
}

// ICollectible Sistema::elegirMesas(int numero, int cantidad)
// {
// }

// void Sistema::confirmarVentaEnMesa()
// {
// }
