#include "Sistema.h"

Sistema *Sistema::instance = NULL;

Sistema::Sistema()
{
    IDictionary *productos = new OrderedDictionary();
    IDictionary *ventas = new OrderedDictionary();
    IDictionary *mozos = new OrderedDictionary();
    IDictionary *mesas = new OrderedDictionary();
    IDictionary *repartidores = new OrderedDictionary();
    IDictionary *empleados = new OrderedDictionary();
    ICollection *medios = new List();
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

// Variables para recordar la selección
Comun *productoComunSeleccionado = nullptr;
IDictionary *productosSeleccionados = new OrderedDictionary(); // clave: código, valor: cantidad (Integer)
int cantidadProductoComunSeleccionada = 0;
Menu *menuRecordado = nullptr;
IDictionary *productosComunSeleccionados = new OrderedDictionary();

// Declaraciones vacías para que el linker no dé error

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
    if (menuRecordado != nullptr)
        delete menuRecordado; // Limpia si ya había uno recordado
    menuRecordado = new Menu(codigoMenu, descripcion, /*precio*/ 0, /*nombre*/ "", /*descuento*/ 0);
    // productosComunSeleccionados->removeAll(); // Opcional: limpiar selección anterior

    // Guardar en productos
    char codStr[2] = {codigoMenu, '\0'};
    IKey *key = new String(codStr);
    // productos->add(key, nuevoMenu);

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
    productosComunSeleccionados->add(key, new Integer(cantProducto));
}

void Sistema::agregarProductoComun(char codigoComun, string descripcion, float precio)
{
    // Verificar si ya existe un producto con ese código usando tu función
    if (existeProducto(codigoComun))
    {
        throw invalid_argument("Ya existe un producto con ese código.");
    }

    // Crear el producto Comun
    Comun *nuevoComun = new Comun(codigoComun, descripcion, precio);

    // Guardar en la colección de productos
    char codStr[2] = {codigoComun, '\0'};
    IKey *key = new String(codStr);

    productoComunSeleccionado = nuevoComun;
    // productos->add(key, nuevoComun);
}

void Sistema::darAltaProducto()
{
    if (menuRecordado != nullptr)
    {
        // 1. Recorrer productosComunSeleccionados y delegar a Menu
        IIterator *keyIt = productosComunSeleccionados->getIterator();
        while (keyIt->hasCurrent())
        {
            IKey *keySel = dynamic_cast<IKey *>(keyIt->getCurrent());
            Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(keySel));
            Comun *comun = nullptr;

            // Extraer el código del producto desde la clave String
            String *strKey = dynamic_cast<String *>(keySel);
            char codigo = strKey->getValue()[0]; // Suponiendo que getValue() devuelve un const char*

            // Buscar el producto en 'productos' comparando el código
            IIterator *prodIt = productos->getIterator();
            while (prodIt->hasCurrent())
            {
                Producto *prod = dynamic_cast<Producto *>(prodIt->getCurrent());
                if (prod && prod->getCodigo() == codigo)
                {
                    comun = dynamic_cast<Comun *>(prod);
                    break;
                }
                prodIt->next();
            }
            delete prodIt;

            if (comun != nullptr && cantidad != nullptr)
            {
                menuRecordado->darAltaMenu(comun, cantidad->getValue());
            }
            keyIt->next();
        }
        delete keyIt;

        // 2. Agregar el menú a la colección de productos
        char codStr[2] = {menuRecordado->getCodigo(), '\0'};
        IKey *keyMenu = new String(codStr);
        productos->add(keyMenu, menuRecordado);

        // 3. Limpiar variables recordadas
        menuRecordado = nullptr;
        // Limpiar productosComunSeleccionados
        IIterator *clearIt = productosComunSeleccionados->getIterator();
        while (clearIt->hasCurrent())
        {
            IKey *key = dynamic_cast<IKey *>(clearIt->getCurrent());
            if (key != nullptr)
            {
                productosComunSeleccionados->remove(key);
            }
            clearIt->next();
        }
        delete clearIt;
    }
    else if (productoComunSeleccionado != nullptr)
    {
        // Producto común: solo agregarlo
        char codStr[2] = {productoComunSeleccionado->getCodigo(), '\0'};
        IKey *key = new String(codStr);
        productos->add(key, productoComunSeleccionado);
        productoComunSeleccionado = nullptr;
    }
}

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

    if (it != nullptr)
    {
        delete it;
        throw std::runtime_error("No existe un mozo con el ID especificado.");
    }
    return DtAsignacion();
}

ICollection *Sistema::elegirMesas(int numero)
{
    if (mesas == nullptr || mesas->isEmpty())
    {
        throw std::runtime_error("No hay mesas disponibles.");
    }
    ICollection *mesasElegidas = new List(); // Colección para almacenar las mesas elegidas
    IIterator *it = mesas->getIterator();
    while (it->hasCurrent())
    {
        Mesa *mesa = dynamic_cast<Mesa *>(it->getCurrent());
        if (mesa != nullptr && mesa->getLocal() == nullptr && mesa->getNumeroMesa() == numero)
        {
            mesasElegidas->add(mesa); // Agrega la mesa a la colección de mesas elegidas
        }
        it->next();
    }
    delete it;
    if (mesasElegidas->isEmpty())
    {
        delete mesasElegidas; // Si no se encontraron mesas, se elimina la colección vacía
        throw std::runtime_error("No se encontraron mesas con el número especificado.");
    }
    return mesasElegidas; // Devuelve la colección de mesas elegidas
}

// void Sistema::confirmarVentaEnMesa()
// {
// }

/*------ ALTA EMPLEADO ------*/
void Sistema::agregarEmpleado(string nombre)
{
    this->nomEmp = nombre;
}

set<Transporte> Sistema::listarMedioTransporte()
{
    return {Bicicleta, Auto, Moto};
}

void Sistema::elegirMedio(Transporte medio)
{
    this->medioSeleccionado = medio;
}

string transporteToString(Transporte t)
{
    switch (t)
    {
    case Transporte::Bicicleta:
        return "Bicicleta";
    case Transporte::Auto:
        return "Auto";
    case Transporte::Moto:
        return "Moto";
    case Transporte::Ninguno:
        return "";
    default:
        return "Desconocido";
    }
}
// Creo que no iría ningún parámetro
void Sistema::darAltaEmpleado()
{
    int idEmpleado = ++ultimoIdEmpleado; // Empieza desde 1

    IKey *key = new Integer(idEmpleado);

    Empleado *nuevoEmpleado;

    if (medioSeleccionado != Transporte::Ninguno)
    {
        // Es repartidor
        string medioStr = transporteToString(this->medioSeleccionado);
        nuevoEmpleado = new Repartidor(nomEmp, idEmpleado, medioStr);
        repartidores->add(key, nuevoEmpleado);
    }
    else
    {
        // Es mozo
        nuevoEmpleado = new Mozo(nomEmp, idEmpleado, 0);
        mozos->add(key, nuevoEmpleado);
    }

    // colección general
    empleados->add(key, nuevoEmpleado);
}

void Sistema::mostrarEmpleados()
{
    cout << "\n--- Empleados registrados ---" << endl;

    IIterator *itEmp = empleados->getIterator();
    while (itEmp->hasCurrent())
    {
        Empleado *emp = dynamic_cast<Empleado *>(itEmp->getCurrent());
        if (emp != nullptr)
        {
            cout << "ID: " << emp->getIdEmpleado() << ", Nombre: " << emp->getNombre() << endl;
        }
        itEmp->next();
    }
    delete itEmp;

    cout << "\n--- Mozos registrados ---" << endl;

    IIterator *itMozo = mozos->getIterator();
    while (itMozo->hasCurrent())
    {
        Mozo *mozo = dynamic_cast<Mozo *>(itMozo->getCurrent());
        if (mozo != nullptr)
        {
            cout << "ID: " << mozo->getIdEmpleado() << ", Nombre: " << mozo->getNombre() << endl;
        }
        itMozo->next();
    }
    delete itMozo;

    cout << "\n--- Repartidores registrados ---" << endl;

    IIterator *itrep = repartidores->getIterator();
    while (itrep->hasCurrent())
    {
        Repartidor *rep = dynamic_cast<Repartidor *>(itrep->getCurrent());
        if (rep != nullptr)
        {
            cout << "ID: " << rep->getIdEmpleado() << ", Nombre: " << rep->getNombre() << ", Medio: " << rep->getTransporte() << endl;
        }
        itrep->next();
    }
    delete itrep;
}

// ALTA CLIENTE
DtCliente Sistema::altaCliente(char telefono, string nombre, DtDireccion direccion)
{
    if (clienteTemp != nullptr)
    {
        delete clienteTemp;
        clienteTemp = nullptr;
    }

    clienteTemp = new Cliente(telefono, nombre, direccion);

    return DtCliente(telefono, nombre, direccion);
}

void Sistema::confirmarAlta()
{
    //?
    IKey *keyCliente = new String(clienteTemp->getTelefono());
    clientes->add(keyCliente, clienteTemp);

    clienteTemp = nullptr;
}

void Sistema::cancelarAlta()
{
    if (clienteTemp != nullptr)
    {
        delete clienteTemp;
        clienteTemp = nullptr;
    }
}

bool Sistema::existeCliente(char telefono)
{
    IIterator *it = clientes->getIterator();
    while (it->hasCurrent())
    {
        Cliente *c = dynamic_cast<Cliente *>(it->getCurrent());
        if (c != nullptr && c->getTelefono() == telefono)
        {
            delete it;
            return true;
        }
        it->next();
    }
    delete it;
    return false;
}
