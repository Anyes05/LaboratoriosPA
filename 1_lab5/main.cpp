#include <iostream>
#include "Factory.h"

using namespace std;

void menuAdministrador(ISistema* sistema) {
    int opcion;
    do { //CODIGO TEMPORAL DE PRUEBA
        cout << "\n--- Administrador ---" << endl;
        cout << "1. Alta Producto" << endl;
        cout << "2. Alta Cliente" << endl;
        cout << "3. Alta Empleado" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: { //CODIGO TEMPORAL DE PRUEBA
                char codigo;
                string descripcion;
                float precio;
                cout << "Código: "; cin >> codigo;
                cout << "Descripción: "; cin.ignore(); getline(cin, descripcion);
                cout << "Precio: "; cin >> precio;
                try {
                    sistema->agregarProductoComun(codigo, descripcion, precio);
                    cout << "Producto común agregado." << endl;
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 2:
                // Lógica 
                break;
            case 3:
                // Lógica
                break;
            case 4: cout << "Volviendo al menú principal..." << endl; break;
            default: cout << "Opción inválida." << endl;
        }
    } while(opcion != 4);
}

void menuMozo(ISistema* sistema) {
    cout << "Menú Mozo (a implementar)" << endl;
}
void menuRepartidor(ISistema* sistema) {
    cout << "Menú Repartidor (a implementar)" << endl;
}
void menuCliente(ISistema* sistema) {
    cout << "Menú Cliente (a implementar)" << endl;
}
void cargarDatosPrueba(ISistema* sistema) {
    cout << "Cargar datos de prueba (a implementar)" << endl;
}

int main() {
    ISistema* sistema = Factory::getSistema(); // Singleton a través de Factory

    int opcion;
    do {
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1. Administrador" << endl;
        cout << "2. Mozo" << endl;
        cout << "3. Repartidor" << endl;
        cout << "4. Cliente" << endl;
        cout << "5. Cargar datos de prueba" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: menuAdministrador(sistema); break;
            case 2: menuMozo(sistema); break;
            case 3: menuRepartidor(sistema); break;
            case 4: menuCliente(sistema); break;
            case 5: cargarDatosPrueba(sistema); break;
            case 6: cout << "Saliendo..." << endl; break;
            default: cout << "Opción inválida." << endl;
        }
    } while(opcion != 6);

    return 0;
}