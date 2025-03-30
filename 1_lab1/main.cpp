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
  cout << "Que tipo de clase desea agregar?" << endl;
  cout << "1. Spinning" << endl;
  cout << "2. Entrenamiento" << endl;
  int tipoClase;
  cin >> tipoClase;
  cin.ignore(); // Limpiar el buffer de entrada
  if (tipoClase < 1 || tipoClase > 2) {
    cout << "Opcion no valida" << endl;
    return;
  }
  if (tipoClase == 1) {
    int cantBicicletas;
    cout << "Ingrese la cantidad de bicicletas: ";
    cin >> cantBicicletas;
    if (cantBicicletas <= 1 || cantBicicletas > 50) {
      cout << "La cantidad de bicicletas debe ser entre 1 y 50" << endl;
      return;
    }
    arrClases[clasesActuales] = new Spinning(clase.getId(), clase.getNombre(), clase.getTurno(), cantBicicletas);
  } else {
    bool enRambla;
    cout << "La clase es en rambla? (1: Si, 0: No): ";
    cin >> enRambla;
    arrClases[clasesActuales] = new Entrenamiento(clase.getId(), clase.getNombre(), clase.getTurno(), enRambla);
  }
  clasesActuales++;
  cout << "Clase agregada con exito!" << endl;

}
/*C) Crea una inscripción de un socio a una clase. La inscripción tiene lugar siempre y
cuando el socio y la clase existan, de lo contrario se levanta una excepción
std::invalid_argument. Si ya existe una inscripción de ese usuario para esa clase, o si
el cupo de esa clase ya fue alcanzado, también se levanta una excepción
std::invalid_argument. */
void agregarInscripcion(string ciSocio, int idClase, Fecha fecha){
  for (int i = 0; i < sociosActuales; i++) {    // Chequeo si existe el socio
    if (arrSocios[i]->getCi() == ciSocio) {
      for (int j = 0; j < clasesActuales; j++) {  // Si el socio existe, chequeo si existe la clase y si tiene cupos libres.
        if (arrClases[j]->getID() == idClase) {
          if (arrClases[j]->cupo() <= 0) {
            throw invalid_argument("No hay cupos libres");
          }
          if (arrClases[j]->getID() == idClase) {   // Si tiene cupo, chequeo si ya existe una inscripcion para ese socio.
            for (int k = 0; k < arrClases[j]->cantInscriptos; k++) {
              if (arrClases[j]->getInscriptos()[k]->getSocio()->getCi() == ciSocio) {
                throw invalid_argument("Ya existe una inscripcion de este usuario para esta clase");
              }
            }
          }
          Socio * socio = arrSocios[i];
          Clase * clase = arrClases[j];
          Inscripcion *inscripcion = new Inscripcion(&fecha, socio, clase);
          arrClases[j]->agregarInscripto(inscripcion);
          arrClases[j]->cantInscriptos++;
          std::cout << "Inscripcion realizada con exito" << endl;
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
DtSocio **obtenerInfoSociosPorClase (int idClase, int &cantSocios) {
  // int &cantSocios es un parametro de salida, se pasa por referencia para que la funcion pueda modificarlo
  cantSocios = 0;
  
  // Se busca la clase que coincide con idClase
  Clase* claseEncontrada = nullptr;
  for (int i = 0; i < clasesActuales; i++) {
    if (arrClases[i]->getID() == idClase) {
      claseEncontrada = arrClases[i];
      break;
    }
  }

  // Si no se encuentra la clase: 
  if (claseEncontrada == nullptr) {
    throw invalid_argument("No se encontro una clase con el ID proporcionado");
  }

  // Se obtiene la lista de inscriptos de la clase
  Inscripcion** inscripciones = claseEncontrada->getInscriptos();
  int maxInscriptos = claseEncontrada->cantInscriptos;

  // Creamos un arreglo dinamico para almacenar los data types de los socios
  DtSocio** dtSocios = new DtSocio*[maxInscriptos];

  // Se recorren las inscripciones y se crean los DtSocio correspondientes
  for (int i = 0; i < maxInscriptos; i++) {
    if (inscripciones[i] != nullptr) {
      Socio* socio = inscripciones[i]->getSocio();
      dtSocios[cantSocios] = new DtSocio(socio->getCi(), socio->getNombre());
      cantSocios++;
    }
  }

  return dtSocios;

}

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
    case 2:
      system("clear");
      cout << "----- AGREGAR CLASE -----" << endl;
      cout << "ID: ";
      int idClase;
      cin >> idClase;
      cin.ignore(); 

      cout << "NOMBRE: ";
      getline(cin, nombre);

      cout << "TURNO (1: Manana, 2: Tarde, 3: Noche): ";
      int turnoInt;
      cin >> turnoInt;
      Turno turno = static_cast<Turno>(turnoInt - 1); // Convertir a enum

      for (int i = 0; i < clasesActuales; i++) {
        if(arrClases[i]->getID() == idClase) {
          throw invalid_argument("Ya existe una clase con este ID");
      }

      try
      {
        DtClase dtClase(idClase, nombre, turno);
        agregarClase(dtClase);
      }
      catch (invalid_argument &ex)
      {
        cout << "Error: " << ex.what() << endl; // devuelve un mensaje explicativo de la excepción (dentro de la funcion agregarClase)
      }
    }
      break;
    case 3:
      system("clear");
      cout << "----- AGREGAR INSCRIPCION -----" << endl;
      cout << "CI del socio: ";
      cin >> ci;
      cin.ignore(); 

      cout << "ID de la clase: ";
      cin >> idClase;
      cin.ignore(); 

      cout << "Fecha (DD/MM/AAAA): ";
      int dia, mes, anio;
      char separador;
      cin >> dia >> separador >> mes >> separador >> anio;
      Fecha fecha(dia, mes, anio); 

      try
      {
        agregarInscripcion(ci, idClase, fecha);
      }
      catch (invalid_argument &ex)
      {
        cout << "Error: " << ex.what() << endl; // devuelve un mensaje explicativo de la excepción (dentro de la funcion agregarInscripcion)
      }
      break;
    case 5: {
      system("clear");
      cout << "----- LISTAR INFO DE SOCIOS POR CLASE -----" << endl;
      cout << "Ingrese el ID de la clase: ";
      int idClase;
      std::cin >> idClase;
  
      try {
          int cantSocios;
          DtSocio **socios = obtenerInfoSociosPorClase(idClase, cantSocios);
  
          cout << "Socios inscritos en la clase " << idClase << ":" << endl;
          for (int i = 0; i < cantSocios; i++) {
              cout << "- CI: " << socios[i]->getCi() << ", Nombre: " << socios[i]->getNombre() << endl;
              delete socios[i]; // Liberar memoria de cada DtSocio
          }
          delete[] socios; // Liberar memoria del arreglo
      } catch (invalid_argument &ex) {
          cout << "Error: " << ex.what() << endl;
      }
  
      break;
  } 

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

  //datos para probar la sobrecragra dek operador
  DtSpinning spinning(1, "Spinning Avanzado", Turno::Manana, 30);
  DtEntrenamiento entrenamiento(2, "Entrenamiento Funcional", Turno::Tarde, true);

  cout << spinning << endl;
  cout << entrenamiento << endl;

  return 0;
}
