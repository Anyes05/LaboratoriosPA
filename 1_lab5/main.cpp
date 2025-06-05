#include <iostream>
#include "Factory.h"

using namespace std;

void menuAdministrador(ISistema *sistema)
{
    int opcion;
    do
    { // CODIGO TEMPORAL DE PRUEBA
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

                // Se obtiene la colección de productos comunes disponibles para agregar al menú
                IDictionary *comunesDisponibles = sistema->agregarMenu(codigoMenu, descripcionMenu);

                // Mostrar productos comunes disponibles
                cout << "Productos comunes disponibles para agregar al menú:" << endl;
                IIterator *it = comunesDisponibles->getIterator();
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
            else
            {
                cout << "Opción inválida." << endl;
                cin.get();
            }
            break;
        }
        case 2:
        {

            char telefono;
            string nombre, calle, calleEsquina;
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
            /*
            hay que preguntar tambien si la dir es apartamento pa poner los datos
            pero ahora me da paja
            */
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
                    cout << "Ya existe un cliente con ese telefono. Alta cancelada." << endl;
                    sistema->cancelarAlta();
                }
                else
                {
                    sistema->confirmarAlta();
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
    cout << "Nombre del empleado: ";
    cin.ignore();
    getline(cin, nombre);

    sistema->agregarEmpleado(nombre);

    cout << "¿El empleado es repartidor? (s/n): ";
    char esRepartidor;
    cin >> esRepartidor;

    if (esRepartidor == 's' || esRepartidor == 'S') {
        sistema->listarMedioTransporte(); // Muestra medios con índices

        cout << "Opción: ";
        int opcion;
        cin >> opcion;

        sistema->elegirMedio(opcion); // Pasás la opción directamente
    } else {
        sistema->elegirMedio(0); // Opción inválida, para que asigne Ninguno
    }

    try {
        sistema->darAltaEmpleado();
        cout << "Empleado dado de alta con éxito." << endl;
        sistema->mostrarEmpleados(); // Solo para testeo
    } catch (exception &e) {
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

            ICollection* asignaciones = sistema->calcularAsignacion(cantMesas, cantMozos);
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
    cout << "Menú Mozo (a implementar)" << endl;
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
    cout << "Cargar datos de prueba (a implementar)" << endl;
}

int main()
{
    ISistema *sistema = Factory::getSistema(); // Singleton a través de Factory

    int opcion;
    do
    {
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1. Administrador" << endl;
        cout << "2. Mozo" << endl;
        cout << "3. Repartidor" << endl;
        cout << "4. Cliente" << endl;
        cout << "5. Cargar datos de prueba" << endl;
        cout << "6. Salir" << endl;
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
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 6);

    return 0;
}