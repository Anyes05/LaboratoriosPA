#include "Sistema.h"
using namespace std;

Sistema *Sistema::instance = NULL;

Sistema::Sistema()
{
    productos = new OrderedDictionary();
    ventas = new OrderedDictionary();
    mozos = new OrderedDictionary();
    mesas = new OrderedDictionary();
    repartidores = new OrderedDictionary();
    empleados = new OrderedDictionary();
    clientes = new List();

    // Inicializar los punteros temporales
    productoComunTemp = nullptr;
    menuTemp = nullptr;
    productosComunSeleccionados = new OrderedDictionary();
    mesasElegidasParaVenta = nullptr;
    idMozoSeleccionado = 0;
    nomEmp = "";
    medioSeleccionado = {};
    ultimoIdEmpleado = 0;
    medios[0] = {Bicicleta};
    medios[1] = {Auto};
    medios[2] = {Moto};
    cantidadMedios = 3;
    idE = 0;
    clienteTemp = nullptr;
    mesaSeleccionada = nullptr;
    productoAQuitar = nullptr;
    cantidadAQuitar = 0;
    ventaTemp = nullptr;
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

/*char normalizarCodigo(char codigo) {
    return std::toupper(static_cast<unsigned char>(codigo));
}
*/
/*----- ALTA PRODUCTO -----*/

bool Sistema::existeProducto(char codigo)
{
    // Verificar que la instancia del sistema existe
    if (instance == nullptr)
    {
        return false;
    }
    try
    {
        IIterator *it = productos->getIterator();
        if (it == nullptr)
        {
            return false;
        }

        while (it->hasCurrent())
        {
            ICollectible *current = it->getCurrent();
            if (current == nullptr)
            {
                it->next();
                continue;
            }

            Producto *p = dynamic_cast<Producto *>(current);
            if (p != nullptr && !p->noExiste(codigo))
            {
                delete it;
                return true;
            }
            it->next();
        }
        delete it;
        return false;
    }
    catch (const exception &e)
    {
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

    // Verificar si hay productos comunes en el sistema
    bool hayProductosComunes = false;
    IIterator *it = productos->getIterator();
    while (it->hasCurrent())
    {
        Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
        Comun *comun = dynamic_cast<Comun *>(prod);
        if (comun != nullptr)
        {
            hayProductosComunes = true;
            break;
        }
        it->next();
    }
    delete it;

    if (!hayProductosComunes)
    {
        throw invalid_argument("No se puede crear un menú porque no hay productos comunes en el sistema.");
    }

    // Limpiar instancia anterior si existe
    if (menuTemp != nullptr)
    {
        delete menuTemp;
        menuTemp = nullptr;
    }

    // Guardar los datos en el datatypes
    string nombreMenu = "Menu ";
    nombreMenu += codigoMenu;
    menuTemp = new DtMenu(codigoMenu, descripcion, 0, nombreMenu, 0.0);

    // Listar todos los productos comunes y devolverlos como DtComun

    it = productos->getIterator();
    OrderedDictionary *listaDtComunes = new OrderedDictionary();

    while (it->hasCurrent())
    {
        Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
        Comun *comun = dynamic_cast<Comun *>(prod);
        if (comun != nullptr)
        {
            DtComun *dt = dynamic_cast<DtComun *>(comun->getDT());
            char codComunStr[2] = {comun->getCodigo(), '\0'};
            IKey *keyComun = new String(codComunStr);
            listaDtComunes->add(keyComun, dt);
        }
        it->next();
    }
    delete it;

    return listaDtComunes;
}

void Sistema::seleccionarProductoComun(char codigoComun, int cantProducto)
{

    // Verificar que tenemos un menú temporal
    if (menuTemp == nullptr)
    {
        throw invalid_argument("No hay un menú en proceso de creación.");
    }

    if (productosComunSeleccionados == nullptr)
    {
        productosComunSeleccionados = new OrderedDictionary();
    }

    char codStr[2] = {codigoComun, '\0'};
    String *key = new String(codStr);

    if (!productos->member(key))
    {
        delete key;
        throw invalid_argument("No existe un producto común con ese código.");
    }

    // Obtener el producto
    Producto *prod = dynamic_cast<Producto *>(productos->find(key));
    Comun *comun = dynamic_cast<Comun *>(prod);

    if (comun == nullptr)
    {
        delete key;
        throw invalid_argument("El producto con ese código no es de tipo común.");
    }

    // Manejar la cantidad

    if (productosComunSeleccionados->member(key))
    {

        // Si ya existe, obtener la cantidad actual
        Integer *cantActual = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));
        if (cantActual != nullptr)
        {
            // Eliminar la entrada existente
            productosComunSeleccionados->remove(key);
            // Crear nueva entrada con la suma de cantidades
            int nuevaCantidad = cantActual->getValue() + cantProducto;
            productosComunSeleccionados->add(key, new Integer(nuevaCantidad));
            delete cantActual; // Liberar la memoria del Integer anterior
        }
    }
    else
    {
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
    try
    {
        if (productoComunTemp != nullptr && productoComunTemp->getCodigo() != '\0')
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
        else if (menuTemp != nullptr && productosComunSeleccionados != nullptr)
        {
            float precioTotal = 0.0;

            // Obtener los productos comunes que ya existen
            IIterator *it = productos->getIterator();
            if (it == nullptr)
            {
                return;
            }

            while (it->hasCurrent())
            {
                Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
                if (prod == nullptr)
                {
                    it->next();
                    continue;
                }

                Comun *comun = dynamic_cast<Comun *>(prod);
                if (comun == nullptr)
                {
                    it->next();
                    continue;
                }

                char codigo = comun->getCodigo();

                // Crear una clave para buscar en productosComunSeleccionados
                char codStr[2] = {codigo, '\0'};
                String *key = new String(codStr);

                if (productosComunSeleccionados->member(key))
                {
                    Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));
                    if (cantidad != nullptr)
                    {
                        precioTotal += comun->getPrecio() * cantidad->getValue();
                    }
                }
                delete key;
                it->next();
            }
            delete it;

            // 2. Crear el menú
            Menu *nuevoMenu = new Menu(
                menuTemp->getCodigo(),
                menuTemp->getdescripcion(),
                precioTotal,
                menuTemp->getNombre(),
                0.10 // 10% de descuento
            );

            // 3. Agregar productos comunes al menú

            it = productos->getIterator();
            while (it->hasCurrent())
            {
                Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
                if (prod == nullptr)
                {
                    it->next();
                    continue;
                }

                Comun *comun = dynamic_cast<Comun *>(prod);
                if (comun == nullptr)
                {
                    it->next();
                    continue;
                }

                char codigo = comun->getCodigo();

                // Crear una clave para buscar en productosComunSeleccionados
                char codStr[2] = {codigo, '\0'};
                String *key = new String(codStr);

                if (productosComunSeleccionados->member(key))
                {
                    Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));
                    if (cantidad != nullptr)
                    {
                        nuevoMenu->darAltaMenu(comun, cantidad->getValue());
                    }
                }
                delete key;
                it->next();
            }
            delete it;

            // 4. Agregar el menú a la colección de productos
            char codStr[2] = {menuTemp->getCodigo(), '\0'};
            String *keyMenu = new String(codStr);
            if (productos->member(keyMenu))
            {
                delete keyMenu;
                throw runtime_error("El menú ya existe en la colección de productos");
            }
            productos->add(keyMenu, nuevoMenu);

            // 5. Limpiar datos temporales

            delete menuTemp;
            menuTemp = nullptr;
            delete productosComunSeleccionados;
            productosComunSeleccionados = nullptr;
        }
        else
        {
            throw runtime_error("No hay datos temporales válidos para dar de alta");
        }
    }
    catch (const exception &e)
    {

        // Limpiar en caso de error
        if (menuTemp != nullptr)
        {
            delete menuTemp;
            menuTemp = nullptr;
        }
        if (productosComunSeleccionados != nullptr)
        {
            delete productosComunSeleccionados;
            productosComunSeleccionados = nullptr;
        }
        throw;
    }
}

/*----- ALTA CLIENTE -----*/ 

DtCliente Sistema::altaCliente(string telefono, string nombre, DtDireccion direccion)
{
    if (clienteTemp != nullptr)
    {
        delete clienteTemp;
        clienteTemp = nullptr;
    }

    clienteTemp = new DtCliente(telefono, nombre, direccion);
    return *clienteTemp;  // Devolvemos una copia del DtCliente
}

void Sistema::confirmarAlta()
{
    if (clienteTemp != nullptr)
    {
        Cliente* cliente = new Cliente(clienteTemp->getTelefono(), clienteTemp->getNombre(), clienteTemp->getDireccion());
        clientes->add(cliente);
        delete clienteTemp;
        clienteTemp = nullptr;
    }
}

void Sistema::cancelarAlta()
{
    if (clienteTemp != nullptr)
    {
        delete clienteTemp;
        clienteTemp = nullptr;
    }
}

bool Sistema::existeCliente(string telefono)
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

void Sistema::listarClientes()
{
    if (clientes == nullptr || clientes->isEmpty())
    {
        cout << "No hay clientes registrados" << endl;
        return;
    }

    IIterator *it = clientes->getIterator();
    cout << "\n Lista de Clientes:\n";

    while (it->hasCurrent())
    {
        Cliente *c = dynamic_cast<Cliente *>(it->getCurrent());

        if (c != nullptr)
        {
            cout << "- Nombre: " << c->getNombre() << endl;
            cout << "  Teléfono: " << c->getTelefono() << endl;

            DtDireccion dir = c->getDireccion();
            cout << "  Dirección: " << dir.getnombreCalle() << " y " << dir.getcalleEsquina() << ", " << dir.getnumero() << endl;
            cout << "-------------------------" << endl;
        }
        it->next();
    }

    delete it;
}

/*------ ALTA EMPLEADO ------*/

string Sistema::transporteToString(Transporte t)
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

void Sistema::agregarEmpleado(string nombre, int idIngresado)
{
    nomEmp = nombre;
    idE = idIngresado;
}

bool Sistema::existeEmpleado(int idIngresado)
{
    IIterator *it = empleados->getIterator();
    while (it->hasCurrent())
    {
        ICollectible *current = it->getCurrent();
        Empleado *emp = dynamic_cast<Empleado *>(current);
        if (emp != nullptr)
        {
            if (emp->getIdIngresado() == idIngresado)
            {
                delete it;
                return true; // Ya existe ese idIngresado
            }
        }
        it->next();
    }
    delete it;
    return false;
}

void Sistema::listarMedioTransporte()
{
    for (int i = 0; i < cantidadMedios; i++)
    {
        cout << (i + 1) << ". " << transporteToString(medios[i]) << endl;
    }
}

void Sistema::elegirMedio(int opcion)
{
    if (opcion < 1 || opcion > cantidadMedios)
    {
        medioSeleccionado = Transporte::Ninguno;
        throw std::invalid_argument("Opción inválida. Seleccione un número válido.");    
    }
    else
    {
        medioSeleccionado = medios[opcion - 1];
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
        string medioStr = transporteToString(medioSeleccionado);
        nuevoEmpleado = new Repartidor(nomEmp, idEmpleado, medioStr, idE);
        repartidores->add(key, nuevoEmpleado);
    }
    else
    {
        // Es mozo
        nuevoEmpleado = new Mozo(nomEmp, idEmpleado, 0, idE);
        mozos->add(key, nuevoEmpleado);
    }

    // colección general
    empleados->add(key, nuevoEmpleado);
    medioSeleccionado = Transporte::Ninguno;
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
            cout << "ID: " << emp->getIdEmpleado() << ", IDIng: " << emp->getIdIngresado() << ", Nombre: " << emp->getNombre() << endl;
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
            cout << "ID: " << mozo->getIdEmpleado() << ", IDIng: " << mozo->getIdIngresado() << ", Nombre: " << mozo->getNombre() << endl;
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
            cout << "ID: " << rep->getIdEmpleado() << ", IDIng: " << rep->getIdIngresado() << ", Nombre: " << rep->getNombre() << ", Medio: " << rep->getTransporte() << endl;
        }
        itrep->next();
    }
    delete itrep;
}


/*----- ASIGNAR MESAS A MOZOS -----*/ 
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

    if (mozos == nullptr || mozos->isEmpty())
    { // chequeo si hay mozos en la coleccion. o podria utilizar el metodo isEmpty() de IDictionary
        throw std::runtime_error("La colección de mozos no está inicializada.");
    }
    if (mozos->getSize() < cantMozos)
    { // chequeo si hay suficientes mozos. No podria pasar por parametro una cantMozos mayor a los que estan dados de alta en la coleccion mozos
        throw std::runtime_error("No hay suficientes mozos para asignar las mesas.");
    }

    ICollection *asignaciones = new List();
    int mesaActual = 1;

    // tengo que crear la coleccion mesa e ir añadiando las mesas a cada mozo segun la cantidad de mesas que se me pasan en cantMesas
    // de esto en realidad se encarga el mozo, con la funcion agregarMesa
    IIterator *it = mozos->getIterator();
    int i = 0;

    while (it->hasCurrent() && i < cantMozos)
    {
        ICollectible *current = it->getCurrent();
        Mozo *mozo = dynamic_cast<Mozo *>(current);
        if (mozo == nullptr)
        {
            cout << "Error: Un elemento en la colección de mozos no es Mozo." << endl;
            it->next();
            continue;
        }
        int cantidad = mesasPorMozo + (i < mesasExtra ? 1 : 0);
        int *mesasAsignadas = new int[cantidad];

        for (int j = 0; j < cantidad; j++)
        {
            mesasAsignadas[j] = mesaActual;
            Mesa *nuevaMesa = new Mesa(mesaActual);
            //mozo->agregarMesa(nuevaMesa);

            // tambien tengo que agregar la mesa a la coleccion global del sistema
            IKey *keyMesa = new Integer(mesaActual);
            if (mesas->member(keyMesa))
            {
                cout << "Advertencia: Ya existe una mesa con número " << mesaActual << ". No se agregará de nuevo." << endl;
                delete keyMesa;
                delete nuevaMesa;
            }
            else
            {
                mesas->add(keyMesa, nuevaMesa);
                mozo->agregarMesa(nuevaMesa);
            }
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

/*----- INICIAR VENTA EN MESA -----*/ 

DtAsignacion* Sistema::ingresarIdMozo(int idMozo)
{
    IIterator *it = mozos->getIterator();
    while (it->hasCurrent())
    {
        Mozo *mozo = dynamic_cast<Mozo *>(it->getCurrent());
        if (mozo != nullptr && mozo->getIdEmpleado() == idMozo)
        {
            int *mesasAsignadas = mozo->getMesasId();
            idMozoSeleccionado = idMozo;
            DtAsignacion* result = new DtAsignacion(mozo->getIdEmpleado(), mesasAsignadas, mozo->getCantMesas(), false);
            delete it;
            return result;
        }
        it->next();
    }
    delete it;
    throw std::runtime_error("No existe un mozo con el ID especificado.");
}

void Sistema::elegirMesas(int numero)
{
    if (mesas == nullptr || mesas->isEmpty())
    {
        throw std::runtime_error("No hay mesas disponibles.");
    }
    Mesa *mesaSeleccionada = dynamic_cast<Mesa *>(mesas->find(new Integer(numero)));
    if (mesaSeleccionada == nullptr)
    {
        throw std::runtime_error("No existe una mesa con el número especificado.");
    }
    if (mesaSeleccionada->getLocal() != nullptr)
    {
        throw std::runtime_error("La mesa ya está ocupada por una venta activa.");
    }
    if (mesasElegidasParaVenta == nullptr)
    {
        mesasElegidasParaVenta = new List(); // Inicializar la colección si es nula
    }
    if (mesasElegidasParaVenta->member(mesaSeleccionada))
    {
        throw std::runtime_error("La mesa ya ha sido elegida para la venta.");
    }
    mesasElegidasParaVenta->add(mesaSeleccionada); // Agregar la mesa a la colección de mesas elegidas
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
    ventas->add(new Integer(venta->getNumero()), venta);                                // Agregar la venta a la colección de ventas
    mesasElegidasParaVenta = nullptr;                                                   // Limpiar la colección de mesas elegidas
    idMozoSeleccionado = 0;                                                            // Reiniciar el ID del mozo seleccionado
}

/*----- VENTA A DOMICILIO -----*/

bool Sistema::ventaDomicilio(char telefono) {
    throw runtime_error("Funcionalidad no implementada");
}

IDictionary* Sistema::listarProductos() {
    throw runtime_error("Funcionalidad no implementada");
}

void Sistema::agregarProductoPedido(char codigo, int cantidad) {
    throw runtime_error("Funcionalidad no implementada");
}

ICollection* Sistema::listarRepartidores() {
    throw runtime_error("Funcionalidad no implementada");
}

void Sistema::asignarRepartidorDomicilio(int idRepartidor) {
    throw runtime_error("Funcionalidad no implementada");
}

DtFacturaDomicilio Sistema::confirmarPedido() {
    throw runtime_error("Funcionalidad no implementada");
}

/*----- AGREGAR PRODUCTO A UNA VENTA -----*/
ICollection *Sistema::listarParaAgregar(int idMesa)
{
    if (mesas == nullptr || mesas->isEmpty())
        throw runtime_error("No hay mesas disponibles.");

    Mesa *mesaSeleccionada = dynamic_cast<Mesa *>(mesas->find(new Integer(idMesa)));
    if (mesaSeleccionada == nullptr)
        throw runtime_error("No existe una mesa con el número especificado.");


    if (mesaSeleccionada->getLocal() == nullptr || mesaSeleccionada->getLocal()->getActiva() == false)
        throw runtime_error("La mesa no tiene una venta activa.");

    ventaTemp = dynamic_cast<Venta *>(mesaSeleccionada->getLocal());

    // Lo correcto: listar TODOS los productos del sistema
    ICollection *productosDisponibles = new List();
    IIterator *it = productos->getIterator();
    while (it->hasCurrent())
    {
        Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
        if (prod != nullptr)
        {
            DtProducto *dtProducto = prod->getDT(); // getDT debe devolver un puntero NUEVO
            productosDisponibles->add(dtProducto);
        }
        it->next();
    }
    delete it;

    if (productosDisponibles->isEmpty())
    {
        delete productosDisponibles;
        throw runtime_error("No hay productos disponibles para agregar a la venta.");
    }
    return productosDisponibles;
}

void Sistema::seleccionarProductoAgregar(char codigo, int cantidad)
{
    if (productos == nullptr || productos->isEmpty())
        throw runtime_error("No hay productos disponibles para agregar.");

    char codStr[2] = {codigo, '\0'};
    IKey *key = new String(codStr);
    if (!productos->member(key))
    {
        delete key;
        throw runtime_error("No existe un producto con el código especificado.");
    }

    Producto *producto = dynamic_cast<Producto *>(productos->find(key));
    if (producto == nullptr)
    {
        delete key;
        throw runtime_error("El producto encontrado no es válido.");
    }
    if (cantidad <= 0)
    {
        delete key;
        throw runtime_error("La cantidad debe ser mayor a cero.");
    }
    if (ventaTemp == nullptr)
    {
        delete key;
        throw runtime_error("No hay una venta activa para agregar el producto.");
    }
    if (ventaTemp->getProductos() == nullptr)
    {
        ventaTemp->setProductos(new OrderedDictionary());
    }
    if (ventaTemp->getProductos()->find(key) == nullptr)
        estaEnPedido = false;
    else
        estaEnPedido = true;
    pedidoTemp = new Pedido(cantidad);
    pedidoTemp->setProducto(producto);
    delete key; // Solo aquí, porque no la agregaste al diccionario
}

void Sistema::confirmarAgregarProducto()
{
    if (pedidoTemp == nullptr || ventaTemp == nullptr)
        throw runtime_error("No hay un pedido o venta activa para confirmar.");

    char codStr[2] = {pedidoTemp->getProducto()->getCodigo(), '\0'};
    IKey *key = new String(codStr);
    if (estaEnPedido)
    {
        Pedido *pedidoExistente = dynamic_cast<Pedido *>(ventaTemp->getProductos()->find(key));
        if (pedidoExistente != nullptr)
        {
            pedidoExistente->setCantProductos(pedidoExistente->getCantProductos() + pedidoTemp->getCantProductos());
        }
        else
        {
            delete key; // Solo aquí, porque no la agregaste
            throw runtime_error("El producto no se encontró en el pedido existente.");
        }
        delete key; // Solo aquí, porque no la agregaste
    }
    else
    {
        ventaTemp->getProductos()->add(key, pedidoTemp); // NO borrar key aquí
        // El diccionario se encarga de liberar la clave cuando remueve el elemento
    }
    ventaTemp->setSubTotal(ventaTemp->getSubTotal() + (pedidoTemp->getCantProductos() * pedidoTemp->getProducto()->getPrecio()));
    pedidoTemp = nullptr;
}

/* ------ QUITAR PRODUCTO DE UNA VENTA ----------*/

void Sistema::ingresarMesa(int idMesa)
{
    if (mesas->isEmpty())
    {
        throw runtime_error("No hay mesas en la colección.");
    }
    mesaSeleccionada = dynamic_cast<Mesa *>(mesas->find(new Integer(idMesa))); // el find me trae un objeto

    if (mesaSeleccionada == nullptr)
    {
        throw runtime_error("No existe una mesa con el número especificado.");
    }
}

 ICollection *Sistema::productosVenta() // me devuelve un set de DtProducto
 {
    if (mesaSeleccionada->getLocal() == nullptr || mesaSeleccionada->getLocal()->getActiva() == false)
    {
        throw runtime_error("La mesa seleccionada no tiene una venta activa.");
    }

    ventaTemp = dynamic_cast<Local *>(mesaSeleccionada->getLocal());
    if (ventaTemp == nullptr)
    {
        throw runtime_error("La venta activa no es válida.");
    }

    ICollection *productos = new List();
    IIterator *it = ventaTemp->getProductos()->getIterator();
    while (it->hasCurrent())
    {
        Pedido *pedido = dynamic_cast<Pedido *>(it->getCurrent());
        if (pedido != nullptr)
        {
            Producto *producto = pedido->getProducto();
            // Si es un pedido, obtenemos el DtProducto del producto asociado
            DtProducto *dtProducto = new DtProducto(producto->getCodigo(), producto->getDescripcion(), producto->getPrecio());
            productos->add(dtProducto); // Agregar el DtProducto a la colección
        }
        
        it->next();
    }
    delete it;

    if (productos->isEmpty())
    {
        delete productos;
        throw runtime_error("No hay productos en la venta.");
    }
    
    return productos; // Retorna una colección de DtProducto de la venta
    
 }

ICollection* Sistema::pedidosVentaActual(){  // Funcion auxiliar(? En si no es necesaria, solo la agregue porque me permite visualizar mejor en el menu 
    if (!ventaTemp)
        throw runtime_error("No hay venta activa.");

    IDictionary* dict = ventaTemp->getProductos();
    ICollection* pedidos = new List();
    IIterator* it = dict->getIterator();
    while (it->hasCurrent()) {
        Pedido* pedido = dynamic_cast<Pedido*>(it->getCurrent());
        if (pedido)
            pedidos->add(pedido);
        it->next();
    }
    delete it;
    return pedidos;
}

void Sistema::seleccionarProductoQuitar(char codigo, int cant) // se le pasa el codigo del producto que quiero eliminar y la cantidad del mismo
{
    char codStr[2] = {codigo, '\0'};
    IKey *key = new String(codStr);
    
    productoAQuitar = dynamic_cast<Producto *> (productos->find(key)); // Buscar el producto en la colección de productos
    if (productoAQuitar == nullptr)
    {
        delete key;
        throw runtime_error("No existe un producto con el código especificado.");
    }
    if (cant <= 0)
    {
        delete key;
        throw runtime_error("La cantidad a quitar debe ser mayor a cero.");
    }
    cantidadAQuitar = cant; // Asignar la cantidad a quitar
}

 void Sistema::quitarProductoVenta()
 {
    if (productoAQuitar == nullptr || mesaSeleccionada == nullptr)
    {
        throw runtime_error("No hay un producto o mesa seleccionada para quitar.");
    }

    IIterator *it = ventaTemp->getProductos()->getIterator();
    bool encontrado = false;

    while (it->hasCurrent())
    {
        Pedido *pedido = dynamic_cast<Pedido *>(it->getCurrent());
        if (pedido != nullptr && pedido->getProducto()->getCodigo() == productoAQuitar->getCodigo())
        {
            encontrado = true;
            int res = pedido->restarProductos(cantidadAQuitar); // Restar la cantidad del pedido
            if (res <= 0) {
                // Si la cantidad restante es 0 o negativa, eliminar el pedido de la venta
                char codStr[2] = {productoAQuitar->getCodigo(), '\0'};
                IKey *key = new String(codStr);
                ventaTemp->getProductos()->remove(key);
                delete pedido; // Liberar memoria del pedido eliminado
                delete key;
            } 
            break; // Salir del bucle una vez encontrado y procesado
        }
        it->next();
    }
    delete it;
    if (!encontrado)
    {
        throw runtime_error("El producto seleccionado no se encuentra en la venta.");
    }

 }

 /*------ VENTAS DE UN MOZO ------*/


void Sistema::listarMozos(){

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
}


void Sistema::mostrarVentasMozo(int idMozo, DtFecha fecha1, DtFecha fecha2){
    IIterator* it = ventas->getIterator();

    while (it->hasCurrent()) {
        Venta *venta = dynamic_cast<Venta *>(it->getCurrent());

        Local *vLocal = dynamic_cast<Local *>(venta); //ventas locales
        if (vLocal != nullptr) {
            Mozo *mozo = vLocal->getMozo();
            if (mozo != nullptr && mozo->getIdEmpleado() == idMozo) {
                Factura *factura = venta->getFactura();
                
                if (factura != nullptr) {
                    DtFecha f = factura->getFecha();
                if ((f.getAnio() > fecha1.getAnio() || (f.getAnio() == fecha1.getAnio() &&
                    (f.getMes() > fecha1.getMes() || (f.getMes() == fecha1.getMes() && f.getDia() >= fecha1.getDia()))))
                    &&
                    (f.getAnio() < fecha2.getAnio() || (f.getAnio() == fecha2.getAnio() &&
                    (f.getMes() < fecha2.getMes() || (f.getMes() == fecha2.getMes() && f.getDia() <= fecha2.getDia()))))
                ) {
                    int numeroVenta = venta->getNumero();
                        float descuento = venta->getDescuento();
                        bool facturada = venta->getActiva();
                        float total = venta->getTotal();

                        DtVenta dtVenta(numeroVenta, descuento, facturada, total);
                         DtFactura dtF = generarFactura(dtVenta);

                         cout << "Factura N°: " << dtF.getCodigoVenta() << "\n";
                        cout << "Fecha: " << dtF.getFecha().getDia() << "/"
                             << dtF.getFecha().getMes() << "/"
                             << dtF.getFecha().getAnio() << "\n";

                        cout << "Productos:\n";
                        IIterator* itProd = dtF.getProductos()->getIterator();
                        while (itProd->hasCurrent()) {
                            DtProducto* p = dynamic_cast<DtProducto*>(itProd->getCurrent());
                            if (p != nullptr) {
                                cout << "- " << p->getdescripcion() <<
                                     " ($" << p->getprecio() << " c/u)\n";
                            }
                            itProd->next();
                        }
                        delete itProd;

                        cout << "Subtotal: $" << dtF.getSubtotal() << "\n";
                        cout << "Descuento: " << dtF.getDescuento() << "%\n";
                        cout << "Monto con descuento: $" << dtF.getMontoConDescuento() << "\n";
                        cout << "Total con IVA: $" << dtF.getTotalConIVA() << "\n";
                        cout << "-----------------------------\n";
                    }
                 }
            }
        }
        it->next();
    }
}



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

