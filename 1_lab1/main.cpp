#include <iostream>
using namespace std;
#define MAX_SOCIOS 50
#define MAX_CLASES 50

// include de todas los .h (clases y datatypes)
#include "DataTypes/Turno.h"
#include "DataTypes/Fecha.h"
#include "DataTypes/DtSocio.h"
#include "DataTypes/DtClase.h"
#include "DataTypes/DtSpinning.h"
#include "DataTypes/DtEntrenamiento.h"

#include "Socio.h"
#include "Inscripcion.h"
#include "Clase.h"
#include "Spinning.h"
#include "Entrenamiento.h"

int sociosActuales = 0;
int clasesActuales = 0;
Socio *arrSocios[MAX_SOCIOS];
Clase *arrClases[MAX_CLASES];

/*----- FUNCIONES PRINCIPALES -----*/

/* A) Crea un nuevo socio en el sistema. En caso de ya existir, levanta la excepción
std::invalid_argument.*/
void agregarSocio(string ci, string nombre)
{
  for (int i = 0; i < sociosActuales; i++)
  {
    if (arrSocios[i]->getCi() == ci)
      throw invalid_argument("Ya existe un socio con esta cedula");
  }

  // Si no se encontró un socio con la misma CI, creamos el nuevo socio
  Socio *s = new Socio(ci, nombre);
  arrSocios[sociosActuales] = s;
  sociosActuales++;

  s->mostrarSocio();
}

/*B) Crea una nueva clase en el sistema. En caso de ya existir, levanta una excepción
std::invalid_argument.*/
void agregarClase(DtClase clase) { 
  
  for (int i = 0; i < MAX_CLASES; i++) {
    if (arrClases[i]->getClase()->getId() == clase.getId() ) // comparar ID de clase para ver si ya existe
      throw invalid_argument("Ya existe una clase con este ID");
  }

  //Preguntamos que tipo de clase desea crear
  cout << "Ingrese el tipo de clase que desea crear: " << endl;
  cout << "1. Spinning" << endl;
  cout << "2. Entrenamiento" << endl;
  int tipoClase;
  cin >> tipoClase;

  if (tipoClase == 1) { 
    cout << "Ingrese la cantidad de bicicletas: ";
    int cantBicicletas;
    cin >> cantBicicletas;
    DtSpinning dtSpinning(clase.getId(), clase.getNombre(), clase.getTurno(), cantBicicletas);
    DtSpinning *dtSpinning = dynamic_cast<DtSpinning*>(&clase);
    Spinning *claseSpinning = new Spinning(&dtSpinning);
    arrClases[clasesActuales] = claseSpinning;
    clasesActuales++;
  } else if (tipoClase == 2) {
    cout << "La clase se realiza en la rambla? (1: Si, 0: No): ";
    bool enRambla;
    cin >> enRambla;
    DtEntrenamiento dtEntrenamiento(clase.getId(), clase.getNombre(), clase.getTurno(), enRambla);
    DtEntrenamiento *dtEntrenamiento = dynamic_cast<DtEntrenamiento*>(&clase);
    Entrenamiento *claseEntrenamiento = new Entrenamiento(&dtEntrenamiento);
    arrClases[clasesActuales] = claseEntrenamiento;
    clasesActuales++;
  } else {
    cout << "Opcion no valida. Intente de nuevo." << endl;
  }
  
  cout << "Clase creada con exito" << endl;
}

/*C) Crea una inscripción de un socio a una clase. La inscripción tiene lugar siempre y
cuando el socio y la clase existan, de lo contrario se levanta una excepción
std::invalid_argument. Si ya existe una inscripción de ese usuario para esa clase, o si
el cupo de esa clase ya fue alcanzado, también se levanta una excepción
std::invalid_argument. */
void agregarInscripcion(string ciSocio, int idClase, Fecha fecha){
  for (int i = 0; i < sociosActuales; i++) {
    if (arrSocios[i]->getCi() == ciSocio) {
      for (int j = 0; j < clasesActuales; j++) {
        if (arrClases[j]->getClase()->getId() == idClase) {
          if (arrClases[j]->cupo() <= 0) {
            throw invalid_argument("No hay cupos libres");
          }
          if (arrClases[j]->getClase()->getId() == idClase) {
            for (int k = 0; k < arrClases[j]->getMaxInscriptos(); k++) {
              if (arrClases[j]->getInscriptos()[k]->getSocio()->getCi() == ciSocio) {
                throw invalid_argument("Ya existe una inscripcion de este usuario para esta clase");
              }
            }
          }
          Socio * socio = arrSocios[i];
          Clase * clase = arrClases[j];
          Inscripcion *inscripcion = new Inscripcion(&fecha, socio, clase->getClase());
          arrClases[j]->agregarInscripto(inscripcion);
          cout << "Inscripcion realizada con exito" << endl;
          return;
        }
      }
    }
  }
  throw invalid_argument("No se encontro el socio o la clase");
}


/* D) Borra la inscripción de un socio a una clase. Si no existe una inscripción de ese
usuario para esa clase, se levanta una excepción std::invalid_argument.*/
// void borrarInscripcion(string ciSocio, int idClase){}

/*E) Retorna un arreglo con los socios que están inscriptos a determinada clase. El largo
del arreglo de socios deberá ser cargado en el parámetro cantSocios.*/
// DtSocio **obtenerInfoSociosPorClase(id idClase, int &cantSocios){}

/*F) Retorna la información de la clase identificada por idClase. */
// DtClase obtenerClase(int idClase) {}

/*------MENU-----*/

void menu()
{
  int opcion;
  bool salir = false;

  do
  {
    system("clear");
    cout << "===== MENU =====" << endl;
    cout << "1. Agregar Socio" << endl;
    cout << "2. Agregar Clase" << endl;
    cout << "3. Agregar Inscripcion" << endl;
    cout << "4. Borrar Inscripcion" << endl;
    cout << "5. Listar Info de Socios por Clase" << endl;
    cout << "6. Listar Info Clase" << endl;
    cout << "7. Salir" << endl;
    cout << "Ingrese su opcion: ";
    cin >> opcion;
    cin.ignore();

    bool socio = false;
    string ci, nombre;
    switch (opcion)
    {
    case 1:
      while (!socio)
      {
        system("clear");
        cout << "----- AGREGAR SOCIO -----" << endl;
        cout << "CI: ";
        getline(cin, ci);

        cout << "NOMBRE: ";
        getline(cin, nombre);

        if (nombre.empty() || ci.empty())
          cout << "No pueden tener la CI o NOMBRE vacio" << endl;
        else
          socio = true;
      }

      try
      {
        agregarSocio(ci, nombre);
      }
      catch (invalid_argument &ex)
      {
        cout << "Error: " << ex.what() << endl; // devuelve un mensaje explicativo de la excepción (dentro de la funcion agregarSocio)
      }

      break;

    case 7:
      salir = true;
      break;
    default:
      cout << "Opcion no valida. Intente de nuevo." << endl;
      break;
    }

    // Pausar la ejecución para que el usuario pueda ver el resultado
    cout << "Presione ENTER para continuar...";
    cin.ignore(); // Esperar a que el usuario presione ENTER
  } while (!salir);
}

int main()
{
  menu();

  return 0;
}
