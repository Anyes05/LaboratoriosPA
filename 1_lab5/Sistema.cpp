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
    cout << "Debug Sistema::Destructor: Iniciando destrucción" << endl;
    
    // Limpiar menuTemp si existe
    if (menuTemp != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando menuTemp" << endl;
        delete menuTemp;
        menuTemp = nullptr;
    }
    
    // Limpiar productoComunTemp si existe
    if (productoComunTemp != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando productoComunTemp" << endl;
        delete productoComunTemp;
        productoComunTemp = nullptr;
    }
    
    // Limpiar productosComunSeleccionados si existe
    if (productosComunSeleccionados != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando productosComunSeleccionados" << endl;
        delete productosComunSeleccionados;
        productosComunSeleccionados = nullptr;
    }
    
    // Limpiar otras colecciones
    if (productos != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando productos" << endl;
        delete productos;
        productos = nullptr;
    }
    
    if (ventas != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando ventas" << endl;
        delete ventas;
        ventas = nullptr;
    }
    
    if (mozos != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando mozos" << endl;
        delete mozos;
        mozos = nullptr;
    }
    
    if (mesas != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando mesas" << endl;
        delete mesas;
        mesas = nullptr;
    }
    
    if (repartidores != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando repartidores" << endl;
        delete repartidores;
        repartidores = nullptr;
    }
    
    if (empleados != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando empleados" << endl;
        delete empleados;
        empleados = nullptr;
    }
    
    if (medios != nullptr) {
        cout << "Debug Sistema::Destructor: Liberando medios" << endl;
        delete medios;
        medios = nullptr;
    }
    
    cout << "Debug Sistema::Destructor: Destrucción completada" << endl;
}

Sistema *Sistema::getInstance()
{
    if (instance == NULL)
        instance = new Sistema();
    return instance;
}

// Declaraciones vacías para que el linker no dé error

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
    cout << "Debug Sistema::agregarMenu: Iniciando" << endl;
    cout << "Debug Sistema::agregarMenu: Código: " << codigoMenu << endl;
    cout << "Debug Sistema::agregarMenu: Descripción: " << descripcion << endl;

    if (existeProducto(codigoMenu))
    {
        cout << "Debug Sistema::agregarMenu: Producto ya existe" << endl;
        throw invalid_argument("Ya existe un producto con ese código.");
    }

    // Limpiar instancia anterior si existe
    if (menuTemp != nullptr) {
        cout << "Debug Sistema::agregarMenu: Limpiando menuTemp anterior" << endl;
        delete menuTemp;
        menuTemp = nullptr;
    }

    // Guardar los datos en el datatype
    cout << "Debug Sistema::agregarMenu: Creando nuevo menuTemp" << endl;
    string nombreMenu = "Menu ";
    nombreMenu += codigoMenu;
    menuTemp = new DtMenu(codigoMenu, descripcion, 0, nombreMenu, 0.0);
    cout << "Debug Sistema::agregarMenu: menuTemp creado exitosamente" << endl;

    // Listar todos los productos comunes y devolverlos como DtComun
    cout << "Debug Sistema::agregarMenu: Obteniendo lista de productos comunes" << endl;
    IIterator *it = productos->getIterator();
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

    cout << "Debug Sistema::agregarMenu: Lista de productos comunes creada" << endl;
    return listaDtComunes;
}

void Sistema::seleccionarProductoComun(char codigoComun, int cantProducto)
{
    cout << "Debug Sistema::seleccionarProductoComun: Iniciando" << endl;
    cout << "Debug Sistema::seleccionarProductoComun: Código: " << codigoComun << ", Cantidad: " << cantProducto << endl;

    // Verificar que tenemos un menú temporal
    if (menuTemp == nullptr)
    {
        cout << "Debug Sistema::seleccionarProductoComun: No hay menú temporal" << endl;
        throw invalid_argument("No hay un menú en proceso de creación.");
    }

    // Verificar que el diccionario de selección existe
    if (productosComunSeleccionados == nullptr)
    {
        cout << "Debug Sistema::seleccionarProductoComun: Creando nuevo diccionario de selección" << endl;
        productosComunSeleccionados = new OrderedDictionary();
    }

    // Verificar que el producto existe
    cout << "Debug Sistema::seleccionarProductoComun: Verificando existencia del producto" << endl;
    char codStr[2] = {codigoComun, '\0'};
    cout << "Debug Sistema::seleccionarProductoComun: Creando clave con código: " << codStr << endl;
    String *key = new String(codStr);

    if (!productos->member(key))
    {
        cout << "Debug Sistema::seleccionarProductoComun: Producto no encontrado" << endl;
        delete key;
        throw invalid_argument("No existe un producto común con ese código.");
    }

    // Obtener el producto
    cout << "Debug Sistema::seleccionarProductoComun: Obteniendo producto" << endl;
    Producto *prod = dynamic_cast<Producto *>(productos->find(key));
    Comun *comun = dynamic_cast<Comun *>(prod);

    if (comun == nullptr)
    {
        cout << "Debug Sistema::seleccionarProductoComun: Producto no es de tipo común" << endl;
        delete key;
        throw invalid_argument("El producto con ese código no es de tipo común.");
    }

    // Manejar la cantidad
    cout << "Debug Sistema::seleccionarProductoComun: Verificando si el producto ya está seleccionado" << endl;
    if (productosComunSeleccionados->member(key))
    {
        cout << "Debug Sistema::seleccionarProductoComun: Producto ya seleccionado, actualizando cantidad" << endl;
        // Si ya existe, obtener la cantidad actual
        Integer *cantActual = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));
        if (cantActual != nullptr)
        {
            // Eliminar la entrada existente
            productosComunSeleccionados->remove(key);
            // Crear nueva entrada con la suma de cantidades
            int nuevaCantidad = cantActual->getValue() + cantProducto;
            cout << "Debug Sistema::seleccionarProductoComun: Nueva cantidad total: " << nuevaCantidad << endl;
            productosComunSeleccionados->add(key, new Integer(nuevaCantidad));
            delete cantActual; // Liberar la memoria del Integer anterior
        }
    }
    else
    {
        // Si no existe, agregar nueva entrada
        cout << "Debug Sistema::seleccionarProductoComun: Agregando nuevo producto seleccionado" << endl;
        productosComunSeleccionados->add(key, new Integer(cantProducto));
    }
    cout << "Debug Sistema::seleccionarProductoComun: Producto agregado exitosamente" << endl;
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
    cout << "Debug Sistema::darAltaProducto: Iniciando" << endl;
    try
    {
        if (productoComunTemp != nullptr && productoComunTemp->getCodigo() != '\0')
        {
            cout << "Debug Sistema::darAltaProducto: Procesando producto común" << endl;
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
            cout << "Debug Sistema::darAltaProducto: Iniciando alta de menú" << endl;
            cout << "Debug Sistema::darAltaProducto: Verificando menuTemp" << endl;
            cout << "Debug Sistema::darAltaProducto: Código del menú: " << menuTemp->getCodigo() << endl;
            cout << "Debug Sistema::darAltaProducto: Descripción del menú: " << menuTemp->getdescripcion() << endl;
            cout << "Debug Sistema::darAltaProducto: Nombre del menú: " << menuTemp->getNombre() << endl;

            // 1. Calcular precio total del menú
            float precioTotal = 0.0;
            cout << "Debug Sistema::darAltaProducto: Tamaño de productosComunSeleccionados: " << productosComunSeleccionados->getSize() << endl;
            
            // Obtener los productos comunes que ya existen
            IIterator *it = productos->getIterator();
            if (it == nullptr)
            {
                cout << "Debug Sistema::darAltaProducto: Iterator es null" << endl;
                return;
            }

            cout << "Debug Sistema::darAltaProducto: Calculando precio total" << endl;
            while (it->hasCurrent())
            {
                Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
                if (prod == nullptr)
                {
                    cout << "Debug Sistema::darAltaProducto: Producto es null" << endl;
                    it->next();
                    continue;
                }

                Comun *comun = dynamic_cast<Comun *>(prod);
                if (comun == nullptr)
                {
                    cout << "Debug Sistema::darAltaProducto: No es un producto común" << endl;
                    it->next();
                    continue;
                }

                char codigo = comun->getCodigo();
                cout << "Debug Sistema::darAltaProducto: Verificando producto con código: " << codigo << endl;

                // Crear una clave para buscar en productosComunSeleccionados
                char codStr[2] = {codigo, '\0'};
                String *key = new String(codStr);

                if (productosComunSeleccionados->member(key))
                {
                    cout << "Debug Sistema::darAltaProducto: Producto encontrado en selección" << endl;
                    Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));
                    if (cantidad != nullptr)
                    {
                        cout << "Debug Sistema::darAltaProducto: Cantidad seleccionada: " << cantidad->getValue() << endl;
                        cout << "Debug Sistema::darAltaProducto: Precio del producto común: " << comun->getPrecio() << endl;
                        precioTotal += comun->getPrecio() * cantidad->getValue();
                        cout << "Debug Sistema::darAltaProducto: Precio total acumulado: " << precioTotal << endl;
                    }
                }
                delete key;
                it->next();
            }
            delete it;

            cout << "Debug Sistema::darAltaProducto: Precio total final calculado: " << precioTotal << endl;

            // 2. Crear el menú
            cout << "Debug Sistema::darAltaProducto: Intentando crear nuevo menú" << endl;
            cout << "Debug Sistema::darAltaProducto: Parámetros para crear menú:" << endl;
            cout << "  - Código: " << menuTemp->getCodigo() << endl;
            cout << "  - Descripción: " << menuTemp->getdescripcion() << endl;
            cout << "  - Precio: " << precioTotal << endl;
            cout << "  - Nombre: " << menuTemp->getNombre() << endl;
            cout << "  - Descuento: 0.10" << endl;

            Menu *nuevoMenu = new Menu(
                menuTemp->getCodigo(),
                menuTemp->getdescripcion(),
                precioTotal,
                menuTemp->getNombre(),
                0.10 // 10% de descuento
            );

            cout << "Debug Sistema::darAltaProducto: Menú creado exitosamente" << endl;

            // 3. Agregar productos comunes al menú
            cout << "Debug Sistema::darAltaProducto: Iniciando agregado de productos comunes al menú" << endl;
            it = productos->getIterator();
            while (it->hasCurrent())
            {
                Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
                if (prod == nullptr)
                {
                    cout << "Debug Sistema::darAltaProducto: Producto es null" << endl;
                    it->next();
                    continue;
                }

                Comun *comun = dynamic_cast<Comun *>(prod);
                if (comun == nullptr)
                {
                    cout << "Debug Sistema::darAltaProducto: No es un producto común" << endl;
                    it->next();
                    continue;
                }

                char codigo = comun->getCodigo();
                cout << "Debug Sistema::darAltaProducto: Verificando producto con código: " << codigo << endl;

                // Crear una clave para buscar en productosComunSeleccionados
                char codStr[2] = {codigo, '\0'};
                String *key = new String(codStr);

                if (productosComunSeleccionados->member(key))
                {
                    cout << "Debug Sistema::darAltaProducto: Producto encontrado en selección" << endl;
                    Integer *cantidad = dynamic_cast<Integer *>(productosComunSeleccionados->find(key));
                    if (cantidad != nullptr)
                    {
                        cout << "Debug Sistema::darAltaProducto: Cantidad a agregar: " << cantidad->getValue() << endl;
                        cout << "Debug Sistema::darAltaProducto: Llamando a darAltaMenu" << endl;
                        nuevoMenu->darAltaMenu(comun, cantidad->getValue());
                        cout << "Debug Sistema::darAltaProducto: darAltaMenu completado" << endl;
                    }
                }
                delete key;
                it->next();
            }
            delete it;

            cout << "Debug Sistema::darAltaProducto: Productos agregados al menú exitosamente" << endl;

            // 4. Agregar el menú a la colección de productos
            cout << "Debug Sistema::darAltaProducto: Intentando agregar menú a la colección de productos" << endl;
            char codStr[2] = {menuTemp->getCodigo(), '\0'};
            String *keyMenu = new String(codStr);
            cout << "Debug Sistema::darAltaProducto: Verificando si el menú ya existe en productos" << endl;
            if (productos->member(keyMenu)) {
                cout << "Debug Sistema::darAltaProducto: ERROR - El menú ya existe en productos" << endl;
                delete keyMenu;
                throw runtime_error("El menú ya existe en la colección de productos");
            }
            cout << "Debug Sistema::darAltaProducto: Agregando menú a productos" << endl;
            productos->add(keyMenu, nuevoMenu);

            cout << "Debug Sistema::darAltaProducto: Menú agregado a productos exitosamente" << endl;

            // 5. Limpiar datos temporales
            cout << "Debug Sistema::darAltaProducto: Iniciando limpieza de datos temporales" << endl;
            delete menuTemp;
            menuTemp = nullptr;
            delete productosComunSeleccionados;
            productosComunSeleccionados = nullptr;

            cout << "Debug Sistema::darAltaProducto: Datos temporales limpiados exitosamente" << endl;
        }
        else
        {
            cout << "Debug Sistema::darAltaProducto: ERROR - No hay datos temporales válidos" << endl;
            cout << "Debug Sistema::darAltaProducto: menuTemp es " << (menuTemp == nullptr ? "null" : "no null") << endl;
            cout << "Debug Sistema::darAltaProducto: productosComunSeleccionados es " << (productosComunSeleccionados == nullptr ? "null" : "no null") << endl;
            throw runtime_error("No hay datos temporales válidos para dar de alta");
        }
    }
    catch (const exception &e)
    {
        cout << "Debug Sistema::darAltaProducto: Error capturado: " << e.what() << endl;
        // Limpiar en caso de error
        if (menuTemp != nullptr)
        {
            cout << "Debug Sistema::darAltaProducto: Limpiando menuTemp en caso de error" << endl;
            delete menuTemp;
            menuTemp = nullptr;
        }
        if (productosComunSeleccionados != nullptr)
        {
            cout << "Debug Sistema::darAltaProducto: Limpiando productosComunSeleccionados en caso de error" << endl;
            delete productosComunSeleccionados;
            productosComunSeleccionados = nullptr;
        }
        throw;
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
    return mesasSeleccionadas;                   // Devuelve la colección de mesas elegidas
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
