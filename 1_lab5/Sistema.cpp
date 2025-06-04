#include "Sistema.h"

Sistema *Sistema::instance = NULL;

Sistema::Sistema()
{
    productos = new OrderedDictionary();
    ventas = new OrderedDictionary();
    mozos = new OrderedDictionary();
    mesas = new OrderedDictionary();
    repartidores = new OrderedDictionary();
    empleados = new OrderedDictionary();
    medios = new List();

    // Inicializar los punteros temporales a nullptr
    productoComunTemp = nullptr;
    menuTemp = nullptr;
    productosComunSeleccionados = new OrderedDictionary();

    mesasElegidasParaVenta = nullptr;
    idMozoSeleccionado = 0;
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

bool Sistema::existeProducto(char codigo) {
    // Verificar que la instancia del sistema existe
    if (instance == nullptr) {
        return false;
    }
    try {
        IIterator *it = productos->getIterator();
        if (it == nullptr) {
            return false;
        }

        while (it->hasCurrent()) {
            ICollectible* current = it->getCurrent();
            if (current == nullptr) {
                it->next();
                continue;
            }

            Producto *p = dynamic_cast<Producto *>(current);
            if (p != nullptr && !p->noExiste(codigo)) {
                delete it;
                return true;
            }
            it->next();
        }
        delete it;
        return false;
    } catch (const exception& e) {
        cout << "Error en existeProducto: " << e.what() << endl;
        return false;
    }
}

IDictionary *Sistema::agregarMenu(char codigoMenu, string descripcion)
{
    if (existeProducto(codigoMenu))
    {
        throw invalid_argument("Ya existe un producto con ese código.");
    }
    // Guardar los datos en el datatype
    menuTemp = new DtMenu(codigoMenu, descripcion, 0, "", 0.0);

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
void Sistema::seleccionarProductoComun(char codigoComun, int cantProducto) {
    // Verificar que tenemos un menú temporal
    if (menuTemp == nullptr) {
        throw invalid_argument("No hay un menú en proceso de creación.");
    }

    // Verificar que el diccionario de selección existe
    if (productosComunSeleccionados == nullptr) {
        productosComunSeleccionados = new OrderedDictionary();
    }

    // Verificar que el producto existe
    char codStr[2] = {codigoComun, '\0'};
    IKey* key = new String(codStr);
    
    if (!productos->member(key)) {
        delete key;
        throw invalid_argument("No existe un producto común con ese código.");
    }

    // Obtener el producto
    Producto* prod = dynamic_cast<Producto*>(productos->find(key));
    Comun* comun = dynamic_cast<Comun*>(prod);

    if (comun == nullptr) {
        delete key;
        throw invalid_argument("El producto con ese código no es de tipo común.");
    }

    // Manejar la cantidad
    if (productosComunSeleccionados->member(key)) {
        // Si ya existe, obtener la cantidad actual
        Integer* cantActual = dynamic_cast<Integer*>(productosComunSeleccionados->find(key));
        if (cantActual != nullptr) {
            // Eliminar la entrada existente
            productosComunSeleccionados->remove(key);
            // Crear nueva entrada con la suma de cantidades
            productosComunSeleccionados->add(key, new Integer(cantActual->getValue() + cantProducto));
            delete cantActual; // Liberar la memoria del Integer anterior
        }
    } else {
        // Si no existe, agregar nueva entrada
        productosComunSeleccionados->add(key, new Integer(cantProducto));
    }
}

void Sistema::agregarProductoComun(char codigoComun, string descripcion, float precio)
{
    // Primero verificar si ya existe
    if (existeProducto(codigoComun))
    {
        throw invalid_argument("Ya existe un producto con ese código.");
    }

    try
    {
        // Eliminar la instancia anterior si existe
        if (productoComunTemp != nullptr)
        {
            delete productoComunTemp;
            productoComunTemp = nullptr;
        }

        // Crear nueva instancia
        productoComunTemp = new DtComun(codigoComun, descripcion, precio);
    }
    catch (const exception &e)
    {
        // Si algo falla, asegurarse de limpiar
        if (productoComunTemp != nullptr)
        {
            delete productoComunTemp;
            productoComunTemp = nullptr;
        }
        throw; // Re-lanzar la excepción
    }
}

void Sistema::darAltaProducto()
{
    if (productoComunTemp->getCodigo() != '\0')
    {
        // Crear y agregar producto común
        Comun *nuevoComun = new Comun(
            productoComunTemp->getCodigo(),
            productoComunTemp->getdescripcion(),
            productoComunTemp->getprecio());

        char codStr[2] = {productoComunTemp->getCodigo(), '\0'};
        IKey *key = new String(codStr);
        productos->add(key, nuevoComun);

        // Limpiar datos temporales
        productoComunTemp = nullptr;
    }
    else if (menuTemp->getCodigo() != '\0' && productosComunSeleccionados != nullptr && !productosComunSeleccionados->isEmpty())
    {
        // Calcular precio total del menú
        float precioTotal = 0.0;
        IIterator *it = productosComunSeleccionados->getIterator();
        while (it->hasCurrent())
        {
            IKey *key = dynamic_cast<IKey *>(it->getCurrent());
            Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));

            String *strKey = dynamic_cast<String *>(key);
            char codigo = strKey->getValue()[0];
            IKey *prodKey = new String(strKey->getValue());
            Comun *comun = dynamic_cast<Comun *>(productos->find(prodKey));

            if (comun != nullptr && cantidad != nullptr)
            {
                precioTotal += comun->getPrecio() * cantidad->getValue();
            }
            delete prodKey;
            it->next();
        }
        delete it;

        // Crear menú con descuento fijo de 10%
        Menu *nuevoMenu = new Menu(
            menuTemp->getCodigo(),
            menuTemp->getdescripcion(),
            precioTotal,
            menuTemp->getNombre(),
            0.10 // 10% de descuento
        );

        // Agregar productos comunes al menú
        it = productosComunSeleccionados->getIterator();
        while (it->hasCurrent())
        {
            IKey *key = dynamic_cast<IKey *>(it->getCurrent());
            Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));

            String *strKey = dynamic_cast<String *>(key);
            char codigo = strKey->getValue()[0];
            IKey *prodKey = new String(strKey->getValue());
            Comun *comun = dynamic_cast<Comun *>(productos->find(prodKey));

            if (comun != nullptr && cantidad != nullptr)
            {
                nuevoMenu->darAltaMenu(comun, cantidad->getValue());
            }
            delete prodKey;
            it->next();
        }
        delete it;

        // Agregar menú a la colección de productos
        char codStr[2] = {menuTemp->getCodigo(), '\0'};
        IKey *keyMenu = new String(codStr);
        productos->add(keyMenu, nuevoMenu);

        // Limpiar datos temporales
        menuTemp = nullptr;
        productosComunSeleccionados = nullptr;
    }
}

// ASIGNAR MESAS A MOZOS
// si no hay ventas sin facturar, o sea que en los links de "actual" no hay venta?
// la cantidad de mozos deberia de estar relacionada de alguna forma con la cantidad que estan dados de alta?
ICollection *Sistema::calcularAsignacion(int cantMesas, int cantMozos)
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

    ICollection *asignaciones = new List(); // creo un arreglo de punteros a DtAsignacion, que sera lo que devuelva al final de la funcion
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

        asignaciones->add(new DtAsignacion(mozo->getIdEmpleado(), mesasAsignadas, cantidad, false));
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
            int *mesasAsignadas = mozo->getMesasId();
            idMozoSeleccionado = idMozo;                                                             // obtiene las mesas asignadas al mozo
            return DtAsignacion(mozo->getIdEmpleado(), mesasAsignadas, mozo->getCantMesas(), false); // retorno dtasignacion con el id del mozo, las mesas asignadas y la cantidad de mesas
        }
        it->next();
    }
    if (it != nullptr)
    {
        delete it;
        throw std::runtime_error("No existe un mozo con el ID especificado.");
    }
}

ICollection *Sistema::elegirMesas(int numero)
{
    if (mesas == nullptr || mesas->isEmpty())
    {
        throw std::runtime_error("No hay mesas disponibles.");
    }
    ICollection *mesasSeleccionadas = new List(); // Colección para almacenar las mesas elegidas
    IIterator *it = mesas->getIterator();
    while (it->hasCurrent())
    {
        Mesa *mesa = dynamic_cast<Mesa *>(it->getCurrent());
        if (mesa != nullptr && mesa->getLocal() == nullptr && mesa->getNumeroMesa() == numero)
        {
            mesasSeleccionadas->add(mesa); // Agrega la mesa a la colección de mesas elegidas
        }
        it->next();
    }
    delete it;
    if (mesasSeleccionadas->isEmpty())
    {
        delete mesasSeleccionadas; // Si no se encontraron mesas, se elimina la colección vacía
        throw std::runtime_error("No se encontraron mesas con el número especificado.");
    }
    mesasElegidasParaVenta = mesasSeleccionadas; // Asigna las mesas elegidas a la colección global
    return mesasSeleccionadas;                   // Devuelve la colección de mesas elegidas
}

void Sistema::confirmarVentaEnMesa()
{
    if (mesasElegidasParaVenta == nullptr || mesasElegidasParaVenta->isEmpty())
    {
        throw std::runtime_error("No hay mesas elegidas para la venta.");
    }
    Local *venta = new Local(0, 0, 0); // Crear una nueva venta, sin valores iniciales
    venta->setActiva(true);
    venta->setNumero(ventas->getSize() + 1); // Asignar un número de venta basado en el tamaño actual de ventas
    venta->setMesas(mesasElegidasParaVenta); // Asignar las mesas elegidas a la venta

    IIterator *it = mesasElegidasParaVenta->getIterator(); // Asignar a cada mesa la venta actual
    while (it->hasCurrent())
    {
        Mesa *mesa = dynamic_cast<Mesa *>(it->getCurrent());
        if (mesa != nullptr)
        {
            mesa->setLocal(venta);
        }
        it->next();
    }
    venta->setMozo(dynamic_cast<Mozo *>(mozos->find(new Integer(idMozoSeleccionado)))); // Asignar el mozo seleccionado a la venta
}

/*------ ALTA EMPLEADO ------*/
void Sistema::agregarEmpleado(string nombre)
{
    // this->nomEmp = nombre;
}

set<Transporte> Sistema::listarMedioTransporte()
{
    // return {Bicicleta, Auto, Moto};
}

void Sistema::elegirMedio(Transporte medio)
{
    //  this->medioSeleccionado = medio;
}

string transporteToString(Transporte t)
{
    // switch (t)
    // {
    // case Transporte::Bicicleta:
    //     return "Bicicleta";
    // case Transporte::Auto:
    //     return "Auto";
    // case Transporte::Moto:
    //     return "Moto";
    // case Transporte::Ninguno:
    //     return "";
    // default:
    //     return "Desconocido";
    // }
}
// Creo que no iría ningún parámetro
void Sistema::darAltaEmpleado()
{
    //  int idEmpleado = ++ultimoIdEmpleado; // Empieza desde 1

    // IKey *key = new Integer(idEmpleado);

    // Empleado *nuevoEmpleado;

    // if (medioSeleccionado != Transporte::Ninguno)
    // {
    //     // Es repartidor
    //     string medioStr = transporteToString(this->medioSeleccionado);
    //     nuevoEmpleado = new Repartidor(nomEmp, idEmpleado, medioStr);
    //     repartidores->add(key, nuevoEmpleado);
    // }
    // else
    // {
    //     // Es mozo
    //     nuevoEmpleado = new Mozo(nomEmp, idEmpleado, 0);
    //     mozos->add(key, nuevoEmpleado);
    // }

    // // colección general
    // empleados->add(key, nuevoEmpleado);
}

void Sistema::mostrarEmpleados()
{
    // cout << "\n--- Empleados registrados ---" << endl;

    // IIterator *itEmp = empleados->getIterator();
    // while (itEmp->hasCurrent())
    // {
    //     Empleado *emp = dynamic_cast<Empleado *>(itEmp->getCurrent());
    //     if (emp != nullptr)
    //     {
    //         cout << "ID: " << emp->getIdEmpleado() << ", Nombre: " << emp->getNombre() << endl;
    //     }
    //     itEmp->next();
    // }
    // delete itEmp;

    // cout << "\n--- Mozos registrados ---" << endl;

    // IIterator *itMozo = mozos->getIterator();
    // while (itMozo->hasCurrent())
    // {
    //     Mozo *mozo = dynamic_cast<Mozo *>(itMozo->getCurrent());
    //     if (mozo != nullptr)
    //     {
    //         cout << "ID: " << mozo->getIdEmpleado() << ", Nombre: " << mozo->getNombre() << endl;
    //     }
    //     itMozo->next();
    // }
    // delete itMozo;

    // cout << "\n--- Repartidores registrados ---" << endl;

    // IIterator *itrep = repartidores->getIterator();
    // while (itrep->hasCurrent())
    // {
    //     Repartidor *rep = dynamic_cast<Repartidor *>(itrep->getCurrent());
    //     if (rep != nullptr)
    //     {
    //         cout << "ID: " << rep->getIdEmpleado() << ", Nombre: " << rep->getNombre() << ", Medio: " << rep->getTransporte() << endl;
    //     }
    //     itrep->next();
    // }
    // delete itrep;
}

// ALTA CLIENTE
DtCliente Sistema::altaCliente(char telefono, string nombre, DtDireccion direccion)
{
    // if (clienteTemp != nullptr)
    // {
    //     delete clienteTemp;
    //     clienteTemp = nullptr;
    // }

    // clienteTemp = new Cliente(telefono, nombre, direccion);

    // return DtCliente(telefono, nombre, direccion);
}

void Sistema::confirmarAlta()
{
    //?
    // IKey *keyCliente = new String(clienteTemp->getTelefono());
    // clientes->add(keyCliente, clienteTemp);

    // clienteTemp = nullptr;
}

void Sistema::cancelarAlta()
{
    // if (clienteTemp != nullptr)
    // {
    //     delete clienteTemp;
    //     clienteTemp = nullptr;
    // }
}

bool Sistema::existeCliente(char telefono)
{
    // IIterator *it = clientes->getIterator();
    // while (it->hasCurrent())
    // {
    //     Cliente *c = dynamic_cast<Cliente *>(it->getCurrent());
    //     if (c != nullptr && c->getTelefono() == telefono)
    //     {
    //         delete it;
    //         return true;
    //     }
    //     it->next();
    // }
    // delete it;
    return false;
}
