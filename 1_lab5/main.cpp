#include <iostream>
#include "Factory.h"

using namespace std;

void menuAdministrador(ISistema *sistema)
{
    int opcion;
    do
    {
        cout << "\n--- Administrador ---" << endl;
        cout << "1. Alta Producto" << endl;
        cout << "2. Alta Cliente" << endl;
        cout << "3. Alta Empleado" << endl;
        cout << "4. Asignar mesas a mozos" << endl;
        cout << "5. Iniciar Venta a Domicilio" << endl;
        cout << "6. Informacion de un Producto" << endl;
        cout << "7. Resumen facturación de un día" << endl;
        cout << "8. Baja de producto" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            (void)system("clear");
            cout << "ALTA DE PRODUCTO" << endl;
            cout << "1 - Producto Común" << endl;
            cout << "2 - Menú" << endl;
            cout << "Seleccione una opción: ";
            char tipoProducto;
            cin >> tipoProducto;
            cin.ignore();

            if (tipoProducto == '1')
            {
                // Alta de producto común
                char codigoComun;
                string descripcion;
                float precio;

                cout << "Ingrese el código del producto común: ";
                cin >> codigoComun;
                cin.ignore();

                if (sistema->existeProducto(codigoComun))
                {
                    cout << "Ya existe un producto con ese código." << endl;
                    cin.get();
                    break;
                }

                cout << "Ingrese la descripción: ";
                getline(cin, descripcion);

                cout << "Ingrese el precio: ";
                cin >> precio;
                cin.ignore();

                sistema->agregarProductoComun(codigoComun, descripcion, precio);

                cout << "¿Desea confirmar el alta del producto? (S/N): ";
                char confirmar;
                cin >> confirmar;
                cin.ignore();

                if (confirmar == 'S' || confirmar == 's')
                {
                    sistema->darAltaProducto();
                    cout << "Producto común dado de alta correctamente." << endl;
                }
                else
                {
                    cout << "Alta de producto cancelada." << endl;
                }
                cin.get();
            }
            else if (tipoProducto == '2')
            {
                // Alta de menú
                char codigoMenu;
                string descripcionMenu;

                cout << "Ingrese el código del menú: ";
                cin >> codigoMenu;
                cin.ignore();

                if (sistema->existeProducto(codigoMenu))
                {
                    cout << "Ya existe un producto con ese código." << endl;
                    cin.get();
                    break;
                }

                cout << "Ingrese la descripción del menú: ";
                getline(cin, descripcionMenu);

                try
                {
                    IDictionary *productosComunes = sistema->agregarMenu(codigoMenu, descripcionMenu);
                    // Mostrar productos comunes disponibles
                    cout << "Productos comunes disponibles para agregar al menú:" << endl;
                    IIterator *it = productosComunes->getIterator();
                    while (it->hasCurrent())
                    {
                        DtComun *dt = dynamic_cast<DtComun *>(it->getCurrent());
                        if (dt)
                        {
                            cout << "Código: " << dt->getCodigo() << " | Descripción: " << dt->getdescripcion() << " | Precio: " << dt->getprecio() << endl;
                        }
                        it->next();
                    }
                    delete it;

                    // Selección de productos comunes para el menú
                    char agregarOtro;
                    do
                    {
                        bool productoValido = false;
                        while (!productoValido)
                        {
                            char codigoComun;
                            int cantidad;
                            cout << "Ingrese el código del producto común a agregar al menú: ";
                            cin >> codigoComun;
                            cin.ignore();
                            cout << "Ingrese la cantidad de este producto en el menú: ";
                            cin >> cantidad;
                            cin.ignore();

                            try
                            {
                                sistema->seleccionarProductoComun(codigoComun, cantidad);
                                productoValido = true; // Solo salgo si fue exitoso
                            }
                            catch (const std::exception &e)
                            {
                                cout << "Error: " << e.what() << endl;
                                cout << "¿Desea intentar con otro código? (S/N): ";
                                char reintentar;
                                cin >> reintentar;
                                cin.ignore();
                                if (reintentar != 'S' && reintentar != 's')
                                {
                                    // El usuario no quiere intentar de nuevo, salgo del sub-ciclo
                                    break;
                                }
                            }
                        }

                        cout << "¿Desea agregar otro producto común al menú? (S/N): ";
                        cin >> agregarOtro;
                        cin.ignore();
                    } while (agregarOtro == 'S' || agregarOtro == 's');

                    cout << "¿Desea confirmar el alta del menú? (S/N): ";
                    char confirmar;
                    cin >> confirmar;
                    cin.ignore();

                    if (confirmar == 'S' || confirmar == 's')
                    {
                        sistema->darAltaProducto();
                        cout << "Menú dado de alta correctamente." << endl;
                    }
                    else
                    {
                        cout << "Alta de menú cancelada." << endl;
                    }
                    cin.get();
                }
                catch (const invalid_argument &e)
                {
                    cout << "Error: " << e.what() << endl;
                    cout << "Presione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    return;
                }
            }
            else
            {
                cout << "Opción inválida." << endl;
                cin.get();
            }
            break;
        }
        case 2:
        {
            string nombre, calle, calleEsquina, telefono;
            int nroPuerta;

            (void)system("clear");

            cout << "ALTA CLIENTE" << endl;
            cout << "Ingrese telefono: ";
            cin >> telefono;
            cout << "\nIngrese nombre: ";
            cin >> nombre;
            cout << "\nIngrese calle: ";
            cin >> calle;
            cout << "\nIngrese calleEsquina: ";
            cin >> calleEsquina;
            cout << "\nIngrese nro de puerta: ";
            cin >> nroPuerta;

            DtDireccion direccion(calle, nroPuerta, calleEsquina);

            DtCliente dt = sistema->altaCliente(telefono, nombre, direccion);

            cout << "Cliente:" << endl;
            cout << "Nombre: " << dt.getNombre() << endl;
            cout << "Telefono: " << dt.getTelefono() << endl;
            cout << "Dirección: " << direccion.getnombreCalle() << " y " << direccion.getcalleEsquina() << ", " << direccion.getnumero() << endl;
            cout << endl;

            char opt;
            cout << "\n¿Desea confirmar? (s/n): ";
            cin >> opt;

            if (opt == 's' || opt == 'S')
            {
                if (sistema->existeCliente(telefono))
                {
                    cout << "Ya existe un cliente con ese telefono" << endl;
                    sistema->cancelarAlta();
                }
                else
                {
                    sistema->confirmarAlta();
                    sistema->listarClientes();
                }
            }
            else
            {
                sistema->cancelarAlta();
            }
        }
        break;

        case 3:
        {
            cout << "--- Alta Empleado ---" << endl;

            string nombre;
            int idIngresado;
            cout << "Nombre del empleado: ";
            cin.ignore();
            getline(cin, nombre);

            cout << "Identificador del empleado (entero): ";
            cin >> idIngresado;

            if (sistema->existeEmpleado(idIngresado))
            {
                cout << "Ya existe un empleado con ese identificador. Operación cancelada." << endl;
                break;
            }

            sistema->agregarEmpleado(nombre, idIngresado);

            char esRepartidor;
            bool entradaValida = false;

            do
            {
                cout << "¿El empleado es repartidor? (s/n): ";
                cin >> esRepartidor;

                // Limpiar caracteres sobrantes del buffer (por si el usuario ingresa "sss" o "sn\n")
                cin.ignore(1000, '\n');

                if (esRepartidor == 's' || esRepartidor == 'S' || esRepartidor == 'n' || esRepartidor == 'N')
                {
                    entradaValida = true;
                }
                else
                {
                    cout << "Entrada inválida. Ingrese 's' para sí o 'n' para no." << endl;
                }

            } while (!entradaValida);

            if (esRepartidor == 's' || esRepartidor == 'S'){
                cout << "Seleccione un medio de transporte:" << endl;
                ICollection* dtMedios = sistema->listarMedioTransporte();
                IIterator* itMedios = dtMedios->getIterator();

                // 2) La imprimimos
                while (itMedios->hasCurrent()) {
                        DtTransporte* dt = dynamic_cast<DtTransporte*>(itMedios->getCurrent());
                        cout << dt->getId() << ". " << dt->getDescripcion() << endl;
                        itMedios->next();
                }
                delete itMedios;

                int opcion;
                entradaValida = false;
                do
                {
                    cout << "Opción: ";
                    cin >> opcion;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Entrada inválida. Debe ser un número." << endl;
                        continue;
                    }

                    try
                    {
                        sistema->elegirMedio(opcion);
                        entradaValida = true;
                    }
                    catch (const invalid_argument &e)
                    {
                        cout << "Error: " << e.what() << endl;
                    }

                } while (!entradaValida);
            }
            else
            {
                try
                {
                    sistema->elegirMedio(0); 
                }
                catch (...) {} 
            }

            try
            {
                sistema->darAltaEmpleado();
                cout << "Empleado dado de alta con éxito." << endl;
                sistema->mostrarEmpleados(); // Solo para testeo
            }
            catch (exception &e)
            {
                cout << "Error al dar de alta al empleado: " << e.what() << endl;
            }

            break;
        }
        case 4:
        {
            (void)system("clear");
            cout << "ASIGNAR MESAS A MOZOS" << endl;
            cout << "Ingrese la cantidad de mesas a asignar: " << endl;
            int cantMesas;
            cin >> cantMesas;
            cin.ignore();
            cout << "Ingrese la cantidad de mozos: " << endl;
            int cantMozos;
            cin >> cantMozos;
            cin.ignore();
            cout << endl;

            try
            {
                ICollection *asignaciones = sistema->calcularAsignacion(cantMesas, cantMozos);
                IIterator *it = asignaciones->getIterator();
                while (it->hasCurrent())
                {
                    DtAsignacion *dtAsignacion = dynamic_cast<DtAsignacion *>(it->getCurrent());
                    if (dtAsignacion)
                    {
                        cout << "Mozo ID: " << dtAsignacion->getidMozo() << endl;
                        cout << "Mesas asignadas: ";
                        int *mesas = dtAsignacion->getidMesas();
                        for (int j = 0; j < dtAsignacion->getcantMesas(); j++)
                        {
                            cout << mesas[j] << " - ";
                        }
                        cout << endl;
                        cout << "----------------------" << endl;
                    }
                    delete dtAsignacion;
                    it->next();
                }
                delete it;
                delete asignaciones;
            }
            catch (const std::exception &e)
            {
                cout << "Error al calcular asignación: " << e.what() << endl;
            }
            break;
        }
        case 5:
        {
            (void)system("clear");
            cout << "--- INICIAR VENTA A DOMICILIO ---" << endl;
            string telefonoCliente;
            cout << "Ingrese el teléfono del cliente: ";
            cin >> telefonoCliente;
            cin.ignore();

            try
            {
                if (!sistema->ventaDomicilio(telefonoCliente))
                {
                    cout << "El cliente con teléfono " << telefonoCliente << " no está registrado." << endl;
                    cout << "¿Desea dar de alta un nuevo cliente? (S/N): ";
                    char altaClienteOpt;
                    cin >> altaClienteOpt;
                    cin.ignore();

                    if (altaClienteOpt == 'S' || altaClienteOpt == 's')
                    {
                        string nombre, calle, calleEsquina;
                        int nroPuerta;
                        cout << "\n--- ALTA NUEVO CLIENTE ---" << endl;
                        cout << "Ingrese nombre: ";
                        getline(cin, nombre);
                        cout << "Ingrese calle: ";
                        getline(cin, calle);
                        cout << "Ingrese calleEsquina: ";
                        getline(cin, calleEsquina);
                        cout << "Ingrese nro de puerta: ";
                        cin >> nroPuerta;
                        cin.ignore();

                        DtDireccion direccion(calle, nroPuerta, calleEsquina);
                        sistema->altaCliente(telefonoCliente, nombre, direccion);
                        sistema->confirmarAlta();
                        cout << "Cliente dado de alta correctamente." << endl;
                    }
                    else
                    {
                        cout << "Operación de venta a domicilio cancelada." << endl;
                        break;
                    }
                }

                // Listar productos y agregar al pedido
                char agregarMasProductos = 's';
                while (agregarMasProductos == 'S' || agregarMasProductos == 's')
                {
                    cout << "\n--- Productos Disponibles ---" << endl;
                    ICollection *productosDisp = sistema->listarProductos();
                    if (productosDisp->isEmpty())
                    {
                        cout << "No hay productos disponibles. Por favor, cargue datos de prueba (Opción 3 en el menú principal)." << endl;
                        delete productosDisp;
                        // Salir del bucle de agregar productos si no hay ninguno
                        break;
                    }

                    IIterator *itProd = productosDisp->getIterator();
                    while (itProd->hasCurrent())
                    {
                        DtProducto *dtProd = dynamic_cast<DtProducto *>(itProd->getCurrent());
                        if (dtProd != nullptr)
                        {
                            cout << "Código: " << dtProd->getCodigo() << " | Descripción: " << dtProd->getdescripcion() << " | Precio: " << dtProd->getprecio() << endl;
                        }
                        itProd->next();
                    }
                    delete itProd;
                    delete productosDisp; // Liberar memoria de la colección

                    char codigoProducto;
                    int cantidadProducto;
                    cout << "Ingrese el código del producto a agregar: ";
                    cin >> codigoProducto;
                    cout << "Ingrese la cantidad: ";
                    cin >> cantidadProducto;
                    cin.ignore();

                    sistema->agregarProductoPedido(codigoProducto, cantidadProducto);
                    cout << "Producto agregado al pedido." << endl;

                    cout << "¿Desea agregar otro producto al pedido? (S/N): ";
                    cin >> agregarMasProductos;
                    cin.ignore();
                }

                // Listar repartidores y asignar uno
                cout << "\n--- Repartidores Disponibles ---" << endl;
                ICollection *repartidoresDisp = sistema->listarRepartidores();
                if (repartidoresDisp->isEmpty())
                {
                    cout << "No hay repartidores disponibles." << endl;
                    delete repartidoresDisp;
                    cout << "Operación de venta a domicilio cancelada." << endl;
                    break;
                }

                IIterator *itRep = repartidoresDisp->getIterator();
                while (itRep->hasCurrent())
                {
                    DtRepartidor *dtRep = dynamic_cast<DtRepartidor *>(itRep->getCurrent());
                    if (dtRep != nullptr)
                    {
                        cout << "ID: " << dtRep->getIdRepartidor() << " | Nombre: " << dtRep->getNombre() << " | Transporte: " << dtRep->getTransporte() << endl;
                    }
                    itRep->next();
                }
                delete itRep;
                delete repartidoresDisp; // Liberar memoria de la colección

                int idRepartidor;
                cout << "Ingrese el ID del repartidor a asignar: ";
                cin >> idRepartidor;
                cin.ignore();
                sistema->asignarRepartidorDomicilio(idRepartidor);
                cout << "Repartidor asignado correctamente." << endl;

                // Confirmar pedido
                char confirmarPedidoOpt;
                cout << "¿Desea confirmar el pedido? (S/N): ";
                cin >> confirmarPedidoOpt;
                cin.ignore();

                if (confirmarPedidoOpt == 'S' || confirmarPedidoOpt == 's')
                {
                    // Obtener fecha para la factura
                    int dia, mes, anio;
                    cout << "Ingrese la fecha de la factura (DD MM AAAA): ";
                    cin >> dia >> mes >> anio;
                    cin.ignore();
                    DtFecha fechaFactura(dia, mes, anio);
                    
                    DtFacturaDomicilio factura = sistema->confirmarPedido(fechaFactura);
                    cout << "\n--- FACTURA DE VENTA A DOMICILIO ---" << endl;
                    cout << "Número de Venta: " << factura.getVenta().getidVenta() << endl;
                    cout << "Subtotal: " << factura.getVenta().getTotal() + factura.getVenta().getDescuento() << endl; // Total + Descuento para obtener subtotal
                    cout << "Descuento Aplicado: " << factura.getVenta().getDescuento() << endl;
                    cout << "Total: " << factura.getVenta().getTotal() << endl;
                    cout << "Repartidor: " << factura.getRepartidor().getNombre() << " (ID: " << factura.getRepartidor().getIdRepartidor() << ", Medio: " << factura.getRepartidor().getTransporte() << ")" << endl;
                    cout << "Venta a domicilio confirmada y facturada." << endl;
                }
                else
                {
                    cout << "Pedido cancelado." << endl;
                }
            }
            catch (const std::exception &e)
            {
                cout << "Error en Venta a Domicilio: " << e.what() << endl;
            }
            cin.get();
        }
        break;
        case 6:
        {
            (void)system("clear");
            cout << "INFORMACIÓN DE UN PRODUCTO" << endl;
            ICollection *productos = sistema->obtenerProductos();
            IIterator *it = productos->getIterator();
            while (it->hasCurrent())
            {
                DtProducto *dtProducto = dynamic_cast<DtProducto *>(it->getCurrent());
                if (dtProducto)
                {
                    cout << "Código: " << dtProducto->getCodigo() << " | Descripción: " << dtProducto->getdescripcion() << " | Precio: " << dtProducto->getprecio() << endl;
                }
                it->next();
            }
            delete it;

            char codigoProducto;
            while (true) {
                cout << "Ingrese el código del producto para ver más detalles: ";
                cin >> codigoProducto;
                cin.ignore();
                if (!sistema->existeProducto(codigoProducto)) {
                    cout << "No existe un producto con ese código." << endl;
                    cout << "¿Desea intentar con otro código? (S/N): ";
                    char reintentar;
                    cin >> reintentar;
                    cin.ignore();
                    if (reintentar != 'S' && reintentar != 's') {
                        delete productos;
                        break;
                    }
                } else {
                    try
                    {
                        bool esMenu = sistema->ingresarCodigoProducto(codigoProducto);
                        if (esMenu)
                        {
                            ICollection* menuYProductos = sistema->infoProductosIncluidosMenu();
                            IIterator* itMenu = menuYProductos->getIterator();
                            bool primero = true;
                            while (itMenu->hasCurrent()) {
                                DtProducto* dt = dynamic_cast<DtProducto*>(itMenu->getCurrent());
                                if (dt) {
                                    if (primero) {
                                        DtMenu* dtMenu = dynamic_cast<DtMenu*>(dt);
                                        if (!dtMenu) {
                                            throw std::runtime_error("No es menú válido.");
                                        }
                                        cout << "Información del menú:" << endl;
                                        cout << "Nombre: " << dtMenu->getNombre() << endl;
                                        cout << "Código: " << dtMenu->getCodigo() << endl;
                                        cout << "Descripción: " << dtMenu->getdescripcion() << endl;
                                        cout << "Precio: " << dtMenu->getprecio() << endl;
                                        cout << "Cantidad Vendida: " << dtMenu->getCantidadVendida() << endl;
                                        cout << "Productos incluidos:" << endl;
                                        primero = false;
                                    } else {
                                        DtComun* dtComun = dynamic_cast<DtComun*>(dt);
                                        cout << "Código: " << dtComun->getCodigo()
                                            << " | Descripción: " << dtComun->getdescripcion()
                                            << " | Precio: " << dtComun->getprecio()
                                            << " | Cantidad en menú: " << dtComun->getCantidadVendida() << endl;
                                    }
                                }
                                itMenu->next();
                            }
                            delete itMenu;
                            delete menuYProductos;
                        }   
                        else
                        {
                            DtProducto *dtProducto = sistema->infoProducto();
                            if (dtProducto)
                            {
                                cout << "Código: " << dtProducto->getCodigo() << endl;
                                cout << "Descripción: " << dtProducto->getdescripcion() << endl;
                                cout << "Precio: " << dtProducto->getprecio() << endl;
                                cout << "Cantidad Vendida: " << dtProducto->getCantidadVendida() << endl;
                                delete dtProducto; // Liberar memoria del DtProducto
                            }
                            else
                            {
                                cout << "No se encontró información para el producto con código: " << codigoProducto << endl;
                            }
                        }
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    delete productos; // Liberar memoria de la colección
                    break; // Salir del bucle después de mostrar la info
                }
            }
            break;
        }
        case 7: {
            int result = system("clear");
            (void)result;
            cout << "--- RESUMEN FACTURACION DE UN DIA ---" << endl;

            int dia, mes, anio;
            cout << "Ingrese la fecha (DD MM AAAA): ";
            cin >> dia >> mes >> anio;
            cin.ignore();

            DtFecha fecha(dia, mes, anio);

            try
            {
                DtFacturacionDia* informePtr = sistema->mostrarInforme(fecha);
                DtFacturacionDia informe = *informePtr;

                cout << "\n=== INFORME DE FACTURACION ===" << endl;
                cout << "Fecha: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << endl;
                cout << "Monto Total Facturado: $" << informe.getMontoTotalFacturado() << endl;

                // Mostrar facturas locales
                ICollection* facturasLocales = informe.getFacturasLocales();
                if (!facturasLocales->isEmpty())
                {
                    cout << "\n--- VENTAS LOCALES ---" << endl;
                    IIterator* itLocal = facturasLocales->getIterator();
                    while (itLocal->hasCurrent())
                    {
                        DtFactura* factura = dynamic_cast<DtFactura*>(itLocal->getCurrent());
                        if (factura != nullptr)
                        {
                            cout << "Venta N°: " << factura->getCodigoVenta() << endl;
                            cout << "Subtotal: $" << factura->getSubtotal() << endl;
                            cout << "Descuento: " << factura->getDescuento() << "%" << endl;
                            cout << "Total con IVA: $" << factura->getTotalConIVA() << endl;
                            cout << "-------------------------" << endl;
                        }
                        itLocal->next();
                    }
                    delete itLocal;
                }

                // Mostrar facturas domicilio
                ICollection* facturasDomicilio = informe.getFacturasDomicilio();
                if (!facturasDomicilio->isEmpty())
                {
                    cout << "\n--- VENTAS A DOMICILIO ---" << endl;
                    IIterator* itDom = facturasDomicilio->getIterator();
                    while (itDom->hasCurrent())
                    {
                        DtFacturaDomicilio* factura = dynamic_cast<DtFacturaDomicilio*>(itDom->getCurrent());
                        if (factura != nullptr)
                        {
                            cout << "Venta N°: " << factura->getVenta().getidVenta() << endl;
                            cout << "Fecha: " << factura->getFecha().getDia() << "/" << factura->getFecha().getMes() << "/" << factura->getFecha().getAnio() << endl;
                            cout << "Cliente: " << factura->getCliente().getNombre() << endl;
                            cout << "Repartidor: " << factura->getRepartidor().getNombre() << endl;
                            cout << "Total: $" << factura->getVenta().getTotal() << endl;
                            cout << "-------------------------" << endl;
                        }
                        itDom->next();
                    }
                    delete itDom;
                }

                if (facturasLocales->isEmpty() && facturasDomicilio->isEmpty())
                {
                    cout << "No hay ventas facturadas para la fecha especificada." << endl;
                }
            }
            catch (const std::exception &e)
            {
                cout << "Error al generar informe: " << e.what() << endl;
            }
            cin.get();
            break;
        }
        case 8:
        {
            system("clear");
            cout << "BAJA DE PRODUCTO" << endl;
            try{
                ICollection *productos = sistema->mostrarProductos();
                IIterator *it = productos->getIterator();
                cout << "Productos disponibles: " << endl;
                while (it->hasCurrent())
                {
                    DtProducto *dtProducto = dynamic_cast<DtProducto *>(it->getCurrent());
                    if (dtProducto)
                    {
                        cout << "Código: " << dtProducto->getCodigo() << " | Descripción: " << dtProducto->getdescripcion() << " | Precio: " << dtProducto->getprecio() << endl;
                    }
                    it->next();
                }
                delete it;
                delete productos;

                // Seleccionar producto a eliminar
                cout << "Ingrese el código del producto a dar de baja: ";
                char codigoProducto;
                cin >> codigoProducto;
                cin.ignore();

                try {
                    sistema->seleccionarProductoBaja(codigoProducto);
                } catch (const std::exception &e) {
                    cout << "Error: " << e.what() << endl;
                    break;
                }

                // Confirmar o cancelar la baja
                cout << "¿Desea confirmar la baja del producto? (S/N): ";
                char confirmarBaja;
                cin >> confirmarBaja;
                cin.ignore();

                if (confirmarBaja == 'S' || confirmarBaja == 's')
                {
                    try {
                        sistema->darBajaProducto();
                        cout << "Producto dado de baja correctamente." << endl;
                    } catch (const std::exception &e) {
                        cout << "Error al dar de baja el producto: " << e.what() << endl;
                        break;
                    }
                }
                else
                {
                    cout << "Baja de producto cancelada." << endl;
                }
            } catch (const std::exception &e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }
        default:
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);
}

void menuMozo(ISistema *sistema)
{
    int opcion;
    do
    {
        cout << "\n--- Mozo ---" << endl;
        cout << "1. Iniciar venta en mesa" << endl;
        cout << "2. Agregar producto a una venta" << endl;
        cout << "3. Quitar producto a una venta" << endl;
        cout << "4. Facturacion de una venta" << endl;
        cout << "5. Mostrar ventas de un mozo" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            (void)system("clear");
            cout << "INICIAR VENTA EN UNA MESA" << endl;
            cout << "Ingrese el identificador del mozo: " << endl;
            int idMozo;
            cin >> idMozo;
            cin.ignore();
            cout << "Las mesas asignadas al mozo " << idMozo << " son: " << endl;
            try
            {
                DtAsignacion *dtAsignacion = sistema->ingresarIdMozo(idMozo);
                int *mesas = dtAsignacion->getidMesas();
                if (mesas == nullptr || dtAsignacion->getcantMesas() == 0)
                {
                    cout << "No hay mesas asignadas al mozo." << endl;
                    break;
                }
                cout << "Mesas asignadas: ";
                for (int j = 0; j < dtAsignacion->getcantMesas(); j++)
                {
                    cout << mesas[j] << " ";
                }
                cout << endl;
                cout << "Seleccione las mesas para la venta: " << endl;
                cout << "Ingrese el número de mesa: ";
                cout << " (0 para salir)" << endl;
                int numeroMesa;
                cin >> numeroMesa;
                cin.ignore();
                while (numeroMesa != 0)
                {
                    try
                    {
                        sistema->elegirMesas(numeroMesa);
                        cout << "Mesa " << numeroMesa << " seleccionada." << endl;
                    }
                    catch (const std::exception &e)
                    {
                        cout << "Error al seleccionar la mesa: " << e.what() << endl;
                    }
                    cout << "Ingrese el número de mesa (0 para salir): ";
                    cin >> numeroMesa;
                    cin.ignore();
                }
                (void)system("clear");
                cout << "Desea iniciar la venta en las mesas seleccionadas? (S/N): ";
                char confirmar;
                cin >> confirmar;
                cin.ignore();
                if (confirmar == 'S' || confirmar == 's')
                {
                    sistema->confirmarVentaEnMesa();
                    cout << "Venta iniciada correctamente." << endl;
                    break;
                }
                else
                {
                    cout << "Venta cancelada." << endl;
                    break;
                }
            }
            catch (const std::exception &e)
            {
                cout << "Error: " << e.what() << endl;
                break;
            }
            break;
        }
        case 2:
        {
            (void)system("clear");
            cout << "AGREGAR PRODUCTO A UNA VENTA" << endl;
            cout << "Ingrese el número de mesa: ";
            int idMesa;
            cin >> idMesa;
            cin.ignore();

            try
            {
                ICollection *productos = sistema->listarParaAgregar(idMesa);
                IIterator *it = productos->getIterator();
                while (it->hasCurrent())
                {
                    DtProducto *dtProducto = dynamic_cast<DtProducto *>(it->getCurrent());
                    if (dtProducto)
                    {
                        cout << "Código: " << dtProducto->getCodigo() << " | Descripción: " << dtProducto->getdescripcion() << " | Precio: " << dtProducto->getprecio() << endl;
                    }
                    it->next();
                }
                delete it;

                char agregarOtro;
                do
                {
                    char codigoProducto;
                    int cantidad;
                    cout << "Ingrese el código del producto a agregar: ";
                    cin >> codigoProducto;
                    cin.ignore();
                    cout << "Ingrese la cantidad: ";
                    cin >> cantidad;
                    cin.ignore();

                    sistema->seleccionarProductoAgregar(codigoProducto, cantidad);
                    cout << "Desea confirmar la adición del producto? (S/N): ";
                    char confirmar;
                    cin >> confirmar;
                    cin.ignore();
                    if (confirmar == 'S' || confirmar == 's')
                    {
                        sistema->confirmarAgregarProducto();
                        cout << "Producto agregado a la venta correctamente." << endl;
                    }
                    else
                    {
                        cout << "Operación cancelada." << endl;
                    }
                    cout << "¿Desea agregar otro producto? (S/N): ";
                    cin >> agregarOtro;
                    cin.ignore();
                } while (agregarOtro == 'S' || agregarOtro == 's');
                cout << "Productos agregados a la venta correctamente." << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Error al agregar producto: " << e.what() << endl;
                break;
            }
            break;
        }
        case 3:
        {
            (void)system ("clear");
            cout << "QUITAR PRODUCTO DE UNA VENTA" << endl;
            cout << endl; 
            cout << "Ingrese el número de una de las mesas involucradas en la venta: ";
            int idMesa;
            cin >> idMesa;
            cin.ignore();
            if (idMesa <= 0)
            {
                cout << "Número de mesa inválido. Debe ser un número positivo." << endl;
                break;
            }
            try
            {
                sistema->ingresarMesa(idMesa);
                ICollection *productos = sistema->productosVenta();
                IIterator *it = productos->getIterator();
                cout << "Productos en la venta actual: " << endl;
                while (it->hasCurrent())
                {
                    DtPedido *dtPedido = dynamic_cast<DtPedido *>(it->getCurrent());
                    if (dtPedido)
                    {
                        cout << "Código: " << dtPedido->getCodigo()
                            << " | Descripción: " << dtPedido->getdescripcion()
                            << " | Cantidad: " << dtPedido->getCantProductos()
                            << endl;
                    }
                    it->next();
                }
                delete it;

                char quitarOtro;
                do 
                {
                    char codigoProducto;
                    int cantidad;
                    cout << "Ingrese el código del producto a quitar: ";
                    cin >> codigoProducto;
                    cin.ignore();
                    cout << "Ingrese la cantidad a quitar: ";
                    cin >> cantidad;
                    cin.ignore();

                    try
{
                        sistema->seleccionarProductoQuitar(codigoProducto, cantidad);
                        cout << "Desea confirmar la disminución del producto? (S/N): ";
                        char confirmar;
                        cin >> confirmar;
                        cin.ignore();
                        if (confirmar == 'S' || confirmar == 's')
                        {
                            sistema->quitarProductoVenta();
                            cout << "Producto quitado de la venta correctamente." << endl;
                            cout << endl;
                            // Me muestra los productos actuales en la venta, lo dejo, no? Esta mas visual asi <- <- <-
                            try {
                                ICollection *productosActuales = sistema->productosVenta();
                                IIterator *it2 = productosActuales->getIterator();
                                cout << "Productos actuales en la venta:" << endl;
                                while (it2->hasCurrent())
                                {
                                    DtPedido *dtPedido = dynamic_cast<DtPedido *>(it2->getCurrent());
                                    if (dtPedido)
                                    {
                                        cout << "Código: " << dtPedido->getCodigo()
                                        << " | Descripción: " << dtPedido->getdescripcion()
                                        << " | Cantidad: " << dtPedido->getCantProductos()
                                        << endl;
                                    }
                                    it2->next();
                                }
                                delete it2;
                                // delete productosActuales; // Si tu ICollection necesita borrado manual
                            } catch (const std::exception &e) {
                                cout << "Error al mostrar productos actuales: " << e.what() << endl;
                            }
                        }
                        else
                        {
                            cout << "Operación cancelada." << endl;
                        }

                    }
                    catch (const std::exception &e)
                    {
                        cout << "Error al quitar producto: " << e.what() << endl;
                    }

                    cout << "¿Desea quitar otro producto? (S/N): ";
                    cin >> quitarOtro;
                    cin.ignore();
                } while (quitarOtro == 'S' || quitarOtro == 's');
            }
            catch (const std::exception &e)
            {
                cout << "Error al quitar producto: " << e.what() << endl;
            }
            break;
        }
        case 4: {
            try {
                int nroMesa;
                cout << "Ingrese el número de la mesa principal: ";
                cin >> nroMesa;

                // Finalizar la venta
                DtVenta ventaDTO = sistema->finalizarVenta(nroMesa);

                // Preguntar si quiere agregar otra mesa
                char agregarMesa = 's';
                while (agregarMesa == 's' || agregarMesa == 'S') {
                    cout << "¿Desea agregar otra mesa a esta factura? (s/n): ";
                    cin >> agregarMesa;

                    if (agregarMesa == 's' || agregarMesa == 'S') {
                        int nroMesaAgregar;
                        cout << "Ingrese el número de la mesa a agregar: ";
                        cin >> nroMesaAgregar;

                        try {
                           // sistema->agregarMesaAFacturacion(nroMesaAgregar);
                            cout << "Mesa "<< nroMesaAgregar << " agregada a la facturación." << endl;
                        } catch (const exception& e) {
                            cout << "Error al agregar mesa: " << e.what() << endl;
                        }
                    }
                }

                char desc;
                cout << "¿Desea aplicar un descuento? (s/n): ";
                cin >> desc;

                if (desc== 's' || desc == 'S') {
                    int descuento;
                    cout << "Ingrese el porcentaje de descuento (0-100): ";
                    cin >> descuento;

                    sistema->aplicarDescuento(descuento);
                }

                int dia, mes, anio;
                cout << "Ingrese la fecha de la factura (DD MM AAAA): ";
                cin >> dia >> mes >> anio;
                DtFecha fechaFactura(dia, mes, anio);

                // factura con fecha
                DtFactura facturaDTO = sistema->generarFactura(ventaDTO, fechaFactura);


                // Mostrar datos
                cout << "\n------ FACTURA ------\n";
                cout << "Código de venta: " << facturaDTO.getCodigoVenta() << endl;
                //cout << "Fecha: " << facturaDTO.getFecha() << endl;

                cout << "\nProductos:\n";
                IIterator* it = facturaDTO.getProductos()->getIterator();
                while (it->hasCurrent()) {
                    DtProducto* p = dynamic_cast<DtProducto*>(it->getCurrent());
                    cout << "Descripción: " << p->getdescripcion() << "Precio: $" << p->getprecio() << endl;
                    it->next();
                }
                delete it;

                float subtotal = facturaDTO.getSubtotal();
                float descuentoAplicado = facturaDTO.getDescuento();
                float total = subtotal * (1 - descuentoAplicado / 100.0f);
                float totalConIVA = total * 1.22;

                cout << "\nSubtotal: $" << subtotal << endl;
                cout << "Descuento aplicado: " << descuentoAplicado << "%" << endl;
                cout << "Total con descuento: $" << total << endl;
                cout << "Total con IVA (22%): $" << totalConIVA << endl;
                cout << "----------------------\n";

            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }

        case 5:
        {
                (void)system("clear");
            cout << "--- MOSTRAR VENTAS DE UN MOZO ---" << endl;
            ICollection* dtMozos = sistema->listarMozos();
            IIterator* it = dtMozos->getIterator();
            while (it->hasCurrent()) {
                DtMozo* dtMozo = dynamic_cast<DtMozo*>(it->getCurrent());
                if (dtMozo != nullptr) {
                    cout << "ID: " << dtMozo->getIdEmpleado()
                        << ", Nombre: " << dtMozo->getNombre() << endl;
                }
                it->next();
            }
            delete it;
            delete dtMozos;

            int idMozo;
            cout << "Ingrese el ID del mozo: ";
            cin >> idMozo;
            cin.ignore();

            int dia1, mes1, anio1, dia2, mes2, anio2;

            cout << "Ingrese la fecha de inicio (DD MM AAAA): ";
            cin >> dia1 >> mes1 >> anio1;
            cin.ignore();

            cout << "Ingrese la fecha de fin (DD MM AAAA): ";
            cin >> dia2 >> mes2 >> anio2;
            cin.ignore();

            DtFecha fechaInicio(dia1, mes1, anio1);
            DtFecha fechaFin(dia2, mes2, anio2);

            try
            {
                ICollection* facturas = sistema->mostrarVentasMozo(idMozo, fechaInicio, fechaFin);
                IIterator* it = facturas->getIterator();

                while (it->hasCurrent()) {
                DtFactura* factura = dynamic_cast<DtFactura*>(it->getCurrent());

                cout << "Factura N°: " << factura->getCodigoVenta() << endl;
                DtFecha f = factura->getFecha();
                cout << "Fecha: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;

                cout << "Productos:\n";
                ICollection* productos = factura->getProductos();
                IIterator* itProd = productos->getIterator();
                while (itProd->hasCurrent()) {
                    DtPedido* dtp = dynamic_cast<DtPedido*>(itProd->getCurrent());
                    cout << "- " << dtp->getdescripcion()
                        << " x " << dtp->getCantProductos()
                        << " ($" << dtp->getprecio() << " c/u)" << endl;

                    itProd->next();
                }
                delete itProd;

                cout << "Subtotal: $" << factura->getSubtotal() << endl;
                cout << "Descuento: " << factura->getDescuento() << "%" << endl;
                cout << "Monto con descuento: $" << factura->getMontoConDescuento() << endl;
                cout << "Total con IVA: $" << factura->getTotalConIVA() << endl;
                cout << "-----------------------------" << endl;

                it->next();
            }
            delete it;

            // Liberar memoria si corresponde (de lo contrario puede haber leaks)
            // ...

            delete facturas;

        } 
            catch (const std::exception &e)
            {
                cout << "Error al mostrar ventas: " << e.what() << endl;
            }
            break;
        }
        case 0:

            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);
}


void cargarDatosPrueba(ISistema *sistema)
{
    cout << "Cargando datos de prueba..." << endl;

    try
    {
        // Bebidas
        sistema->agregarProductoComun('A', "Agua Mineral", 2.50);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('B', "Coca Cola", 3.00);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('C', "Cerveza", 4.50);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('D', "Vino Tinto", 8.00);
        sistema->darAltaProducto();

        // Entradas
        sistema->agregarProductoComun('E', "Ensalada César", 6.50);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('F', "Sopa del Día", 5.00);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('G', "Pan con Mantequilla", 2.00);
        sistema->darAltaProducto();

        // Platos Principales
        sistema->agregarProductoComun('H', "Bife de Chorizo", 15.00);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('I', "Pasta Carbonara", 12.00);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('J', "Pescado del Día", 14.00);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('K', "Pollo a la Parrilla", 11.00);
        sistema->darAltaProducto();

        // Postres
        sistema->agregarProductoComun('L', "Flan Casero", 4.50);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('M', "Helado", 3.50);
        sistema->darAltaProducto();
        sistema->agregarProductoComun('N', "Tiramisú", 5.00);
        sistema->darAltaProducto();

        cout << "Productos comunes cargados exitosamente. Creando menús..." << endl;

        // Crear Menú Ejecutivo
        sistema->agregarMenu('X', "Menú Ejecutivo");
        sistema->seleccionarProductoComun('A', 1); // Agua Mineral
        sistema->seleccionarProductoComun('E', 1); // Ensalada César
        sistema->seleccionarProductoComun('H', 1); // Bife de Chorizo
        sistema->seleccionarProductoComun('L', 1); // Flan Casero
        sistema->darAltaProducto();

        // Crear Menú Vegetariano
        sistema->agregarMenu('Y', "Menú Vegetariano");
        sistema->seleccionarProductoComun('A', 1); // Agua Mineral
        sistema->seleccionarProductoComun('E', 1); // Ensalada César
        sistema->seleccionarProductoComun('I', 1); // Pasta Carbonara
        sistema->seleccionarProductoComun('M', 1); // Helado
        sistema->darAltaProducto();

        // Crear Menú Familiar
        sistema->agregarMenu('Z', "Menú Familiar");
        sistema->seleccionarProductoComun('B', 4); // 4 Coca Colas
        sistema->seleccionarProductoComun('G', 4); // 4 Panes con Mantequilla
        sistema->seleccionarProductoComun('H', 2); // 2 Bifes de Chorizo
        sistema->seleccionarProductoComun('K', 2); // 2 Pollos a la Parrilla
        sistema->seleccionarProductoComun('N', 4); // 4 Tiramisús
        sistema->darAltaProducto();

        // Cargar empleados de prueba

        // Mozo 1
        sistema->agregarEmpleado("Juan Pérez", 100);
        sistema->darAltaEmpleado();

        // Mozo 2
        sistema->agregarEmpleado("Ana López", 101);
        sistema->darAltaEmpleado();

        // Repartidor 1
        sistema->agregarEmpleado("Carlos Gómez", 200);
        sistema->elegirMedio(1); // Bicicleta
        sistema->darAltaEmpleado();

        // Repartidor 2
        sistema->agregarEmpleado("Lucía Fernández", 201);
        sistema->elegirMedio(3); // Moto
        sistema->darAltaEmpleado();

        // Repartidor 3
        sistema->agregarEmpleado("Pedro Ruiz", 202);
        sistema->elegirMedio(2); // Auto
        sistema->darAltaEmpleado();



        cout << "Datos de prueba cargados exitosamente!" << endl;
    }
    catch (const exception &e)
    {
        cout << "Error al cargar datos de prueba: " << e.what() << endl;
    }
}  

void precargarMesas(ISistema *sistema)
{
    cout << "Precargando mesas..." << endl;
    try
    {
        // Crear 10 mesas y asignarlas a los mozos existentes
        ICollection *asignaciones = sistema->calcularAsignacion(10, 2); // 10 mesas para 3 mozos
        IIterator *it = asignaciones->getIterator();
        while (it->hasCurrent())
        {
            DtAsignacion *dtAsignacion = dynamic_cast<DtAsignacion *>(it->getCurrent());
            if (dtAsignacion)
            {
                cout << "Mozo ID: " << dtAsignacion->getidMozo() << endl;
                cout << "Mesas asignadas: ";
                int *mesas = dtAsignacion->getidMesas();
                for (int j = 0; j < dtAsignacion->getcantMesas(); j++)
                {
                    cout << mesas[j] << " ";
                }
                cout << endl;
            }
            delete dtAsignacion;
            it->next();
        }
        delete it;
        delete asignaciones;
        cout << "Mesas precargadas exitosamente!" << endl;
    }
    catch (const exception &e)
    {
        cout << "Error al precargar mesas: " << e.what() << endl;
    }
}


int main()
{
    try
    {
        ISistema *sistema = Sistema::getInstance();
        if (sistema == nullptr)
        {
            cout << "Error: No se pudo inicializar el sistema" << endl;
            return 1;
        }

        int opcion;
        do
        {
            cout << "===== MENU PRINCIPAL =====" << endl;
            cout << "1. Administrador" << endl;
            cout << "2. Mozo" << endl;
            cout << "3. Cargar datos de prueba" << endl;
            cout << "4. Precargar mesas" << endl;
            cout << "0. Salir" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                menuAdministrador(sistema);
                break;
            case 2:
                menuMozo(sistema);
                break;
            case 3:
                cargarDatosPrueba(sistema);
                break;
            case 4:
                precargarMesas(sistema);
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
            }
        } while (opcion != 0);
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}