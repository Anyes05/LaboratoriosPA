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
        cout << "0. Volver" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            system("clear");
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

            system("clear");

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
                sistema->listarMedioTransporte();

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
            system("clear");
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
            cout << "Volviendo al menú principal..." << endl;
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
        cout << "0. Volver" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            system("clear");
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
                system("clear");
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
            system("clear");
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
            system ("clear");
            cout << "QUITAR PRODUCTO DE UNA VENTA" << endl;
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
                while (it->hasCurrent())
                {
                    DtProducto *dtProducto = dynamic_cast<DtProducto *>(it->getCurrent());
                    if (dtProducto)
                    {
                        cout << "Código: " << dtProducto->getCodigo() << " | Descripción: " << dtProducto->getdescripcion() <<  endl;
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
                            // Me muestra los productos actuales en la venta, lo dejo, no? Esta mas visual asi <- <- <-
                            try {
                                ICollection *productosActuales = sistema->pedidosVentaActual();
                                IIterator *it2 = productosActuales->getIterator();
                                cout << "Productos actuales en la venta:" << endl;
                                while (it2->hasCurrent())
                                {
                                    // Aquí accedemos al Pedido para mostrar la cantidad
                                    Pedido *pedido = dynamic_cast<Pedido *>(it2->getCurrent());
                                    if (pedido)
                                    {
                                        Producto *prod = pedido->getProducto();
                                        cout << "Código: " << prod->getCodigo()
                                            << " | Descripción: " << prod->getDescripcion()
                                            << " | Cantidad: " << pedido->getCantProductos()
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
        case 4:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);
}

void menuRepartidor(ISistema *sistema)
{
    cout << "Menú Repartidor (a implementar)" << endl;
}
void menuCliente(ISistema *sistema)
{
    cout << "Menú Cliente (a implementar)" << endl;
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
        IDictionary *productosComunes = sistema->agregarMenu('X', "Menú Ejecutivo");
        sistema->seleccionarProductoComun('A', 1); // Agua Mineral
        sistema->seleccionarProductoComun('E', 1); // Ensalada César
        sistema->seleccionarProductoComun('H', 1); // Bife de Chorizo
        sistema->seleccionarProductoComun('L', 1); // Flan Casero
        sistema->darAltaProducto();

        // Crear Menú Vegetariano
        productosComunes = sistema->agregarMenu('Y', "Menú Vegetariano");
        sistema->seleccionarProductoComun('A', 1); // Agua Mineral
        sistema->seleccionarProductoComun('E', 1); // Ensalada César
        sistema->seleccionarProductoComun('I', 1); // Pasta Carbonara
        sistema->seleccionarProductoComun('M', 1); // Helado
        sistema->darAltaProducto();

        // Crear Menú Familiar
        productosComunes = sistema->agregarMenu('Z', "Menú Familiar");
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
            cout << "3. Repartidor" << endl;
            cout << "4. Cliente" << endl;
            cout << "5. Cargar datos de prueba" << endl;
            cout << "6. Precargar mesas" << endl;
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
                menuRepartidor(sistema);
                break;
            case 4:
                menuCliente(sistema);
                break;
            case 5:
                cargarDatosPrueba(sistema);
                break;
            case 6:
                precargarMesas(sistema);
                break;
            case 7:
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