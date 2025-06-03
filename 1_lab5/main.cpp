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
            // Lógica
            break;
        case 3:
            // Lógica
            break;
        case 4:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 4);
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