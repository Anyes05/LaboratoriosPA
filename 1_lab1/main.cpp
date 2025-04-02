#include <iostream>
#include <limits>
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

/*----- FUNCIONES AUXILIARES -----*/

bool existeClaseConID(int idClase)
{
  for (int i = 0; i < clasesActuales; i++)
  {
    if (arrClases[i]->getID() == idClase)
    {
      return true;
    }
  }
  return false;
}

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
void agregarClase(DtClase clase)
{
  cout << "Que tipo de clase desea agregar?" << endl;
  cout << "1. Spinning" << endl;
  cout << "2. Entrenamiento" << endl;
  int tipoClase;
  cin >> tipoClase;
  cin.ignore(); // Limpiar el buffer de entrada

  if (tipoClase < 1 || tipoClase > 2)
  {
    cout << "Opcion no valida" << endl;
    return;
  }

  // Verificar si ya existe una clase con el mismo ID
  if (existeClaseConID(clase.getId()))
  {
    throw invalid_argument("Ya existe una clase con este ID");
  }

  if (tipoClase == 1)
  {
    int cantBicicletas;
    cout << "Ingrese la cantidad de bicicletas: ";
    cin >> cantBicicletas;
    cin.ignore();
    if (cantBicicletas < 1 || cantBicicletas > 50)
    {
      cout << "La cantidad de bicicletas debe ser entre 1 y 50" << endl;
      return;
    }
    arrClases[clasesActuales] = new Spinning(clase.getId(), clase.getNombre(), clase.getTurno(), cantBicicletas);
  }
  else
  {
    bool enRambla;
    int opcionRambla;
    cout << "La clase es en rambla? (1: Si, 0: No): ";
    cin >> opcionRambla;
    cin.ignore();
    if (opcionRambla != 0 && opcionRambla != 1)
    {
      cout << "Las unicas opciones validas son 0 y 1. " << endl;
      return;
    }
    enRambla = static_cast<bool>(opcionRambla); // Convertir la entrada a booleano
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
void agregarInscripcion(string ciSocio, int idClase, Fecha fecha)
{
  Socio *socio = nullptr;
  Clase *clase = nullptr;

  // Buscar socio
  for (int i = 0; i < sociosActuales; i++)
  {
    if (arrSocios[i]->getCi() == ciSocio)
    {
      socio = arrSocios[i];
      break;
    }
  }

  // Buscar clase
  for (int j = 0; j < clasesActuales; j++)
  {
    if (arrClases[j]->getID() == idClase)
    {
      clase = arrClases[j];
      break;
    }
  }

  // Validar que se encontraron tanto el socio como la clase
  if (socio == nullptr || clase == nullptr)
  {
    throw invalid_argument("No se encontró el socio o la clase");
  }

  // Validar cupos disponibles
  if (clase->cupo() <= 0)
  {
    throw invalid_argument("No hay cupos libres");
  }

  if (!fecha.validar())
  {
    throw invalid_argument("Fecha Invalida");
  }

  // Verificar si ya está inscrito
  Inscripcion **inscriptos = clase->getInscriptos(); // Obtener lista de inscriptos
  int cantInscriptos = clase->getCantInscriptos();   // Cantidad de Inscriptos en la clase

  for (int k = 0; k < cantInscriptos; k++)
  {
    if (inscriptos[k]->getSocio()->getCi() == ciSocio)
    {
      throw invalid_argument("Ya existe una inscripción de este usuario para esta clase");
    }
  }

  // Crear inscripción y agregarla
  Inscripcion *nuevaInscripcion = new Inscripcion(&fecha, socio, clase);
  clase->agregarInscripto(nuevaInscripcion);

  cout << "Inscripción realizada con éxito" << endl;
}

/* D) Borra la inscripción de un socio a una clase. Si no existe una inscripción de ese
usuario para esa clase, se levanta una excepción std::invalid_argument.*/
 void borrarInscripcion(string ciSocio, int idClase)
  {

   // Buacar la clase:
   Clase *clase = nullptr;
   for (int i = 0; i < clasesActuales; i++)
   {
     if (arrClases[i]->getID() == idClase)
     {
       clase = arrClases[i];
       break;
     }
   }
   // Si no se encontró:
   if (clase == nullptr)
   {     throw invalid_argument("No existe una clase con ese ID ");   }
   
   // Buscar al socio y si se encuentra, eliminar la inscripción:
    bool encontrado = false;
    for (int i = 0; i < clase->getCantInscriptos(); i++)
    {
     if (clase->getInscriptos()[i] != nullptr && clase->getInscriptos()[i]->getSocio()->getCi() == ciSocio)
    {
      delete clase->getInscriptos()[i];    // Liberar memoria
      clase->getInscriptos()[i] = nullptr; // Eliminar la inscripción

      // Reorganizar las inscripciones desplazando los elementos
      for (int aux = i; aux < clase->getCantInscriptos(); aux++)
      {
        clase->getInscriptos()[aux] = clase->getInscriptos()[aux + 1]; // Mover al anterior/       
      }
        clase->setCantInscriptos(clase->getCantInscriptos() - 1);
        clase->getInscriptos()[clase->getCantInscriptos()] = nullptr;
        encontrado = true;
        cout << "Inscripción eliminada con éxito." << endl;      break;
   }
  }

  if (!encontrado)
   {
     throw invalid_argument("No existe una inscripción del socio en la clase");
   }
 }

/*E) Retorna un arreglo con los socios que están inscriptos a determinada clase. El largo
del arreglo de socios deberá ser cargado en el parámetro cantSocios.*/
DtSocio **obtenerInfoSociosPorClase(int idClase, int &cantSocios)
{
  Clase *claseEncontrada = nullptr;
  for (int i = 0; i < clasesActuales; i++)
  {
    if (arrClases[i]->getID() == idClase)
    {
      claseEncontrada = arrClases[i];
      break;
    }
  }

  // Si no se encuentra la clase:
  if (claseEncontrada == nullptr)
  {
    throw invalid_argument("No se encontro una clase con el ID proporcionado");
  }
  
  Inscripcion **inscripciones = claseEncontrada->getInscriptos(); // Se obtiene el arreglo de inscripciones

  // Creamos un arreglo dinamico para almacenar los data types de los socios
  DtSocio **dtSocios = new DtSocio *[cantSocios];
  
  if (inscripciones == nullptr || cantSocios == 0)
        {
          cout << "No hay socios inscriptos en esta clase." << endl;
        }

  // Se recorren las inscripciones y se crean los DtSocio correspondientes
  for (int i = 0; i < cantSocios; i++)
  {
    if (inscripciones[i] != nullptr)
    {
      cout << inscripciones[i]->getSocio()->getCi() << " | " << inscripciones[i]->getSocio()->getNombre() << endl; // irmprimior el arreglo antes de retornarlo.
      
      Socio *socio = inscripciones[i]->getSocio(); // copiar el arreglo de inscripciones para retornarlo.
      dtSocios[i] = new DtSocio(socio->getCi(), socio->getNombre());
    }
  }
  return dtSocios;
}

/*F) Retorna la información de la clase identificada por idClase. */
DtClase obtenerClase(int idClase)
{
  for (int i = 0; i < MAX_CLASES; i++)
  {
    if (arrClases[i]->getID() == idClase)
    {
      DtClase dtClase = arrClases[i]->getInfo(); // Obtener el objeto DtClase de la clase correspondiente
      return dtClase;
    }
  }
  throw invalid_argument("No se encontró una clase con ese id");
}

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

    bool socio = false, clase = false, inscripcion = false;
    string ci, nombre;
    Turno turno;
    int turnoInt;
    int idClase = 0;
    int dia, mes, anio;
    char separador;
    string ciSocio;
    Fecha fecha;

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

        if (nombre.empty() || ci.empty()){
          cout << "No pueden tener la CI o NOMBRE vacio" << endl;
          cin.ignore();
        }
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
      while (!clase)
      {
        system("clear");
        cout << "----- AGREGAR CLASE -----" << endl;

        cout << "ID: ";
        cin >> idClase;
        cin.ignore();

        cout << "NOMBRE: ";
        getline(cin, nombre);

        cout << "TURNO (1: Manana, 2: Tarde, 3: Noche): ";
        cin >> turnoInt;
        turno = static_cast<Turno>(turnoInt - 1); // Convertir a enum
        cin.ignore();

        if (nombre.empty() || idClase == 0){
          cout << "No pueden tener la CI o ID vacio" << endl;
          cin.ignore();
        }
        else if (turnoInt < 1 || turnoInt > 3){
          cout << "Opcion de TURNO no valida" << endl;
          cin.ignore();
        }
          
        else
          clase = true;
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

      break;
    case 3:
      while (!inscripcion)
      {
        system("clear");
        cout << "----- AGREGAR INSCRIPCION -----" << endl;

        // Leer CI
        cout << "CI del socio: ";
        getline(cin, ci);

        // Leer ID de la clase
        cout << "ID de la clase: ";
        cin >> idClase;
        cin.ignore();

        // Leer la fecha correctamente
        cout << "Dia de Inscripcion: ";
        cin >> dia;
        cout << "Mes de Inscripcion: ";
        cin >> mes;
        cout << "Año de Inscripcion: ";
        cin >> anio;
        cin.ignore();

        // Crear la fecha con los valores correctos
        fecha = Fecha(dia, mes, anio);

        // Validaciones
        if (ci.empty() || idClase == 0){
          cout << "No puede tener CI o ID vacío" << endl;
          cin.ignore();
        } 
        else
          inscripcion = true; // Salir del bucle si todo es correcto
      }
      try
      {
        agregarInscripcion(ci, idClase, fecha);
      }
      catch (invalid_argument &ex)
      {
        cout << "Error: " << ex.what() << endl; // devuelve un mensaje explicativo de la excepción
      }

      break;

    case 4:
    {

       system("clear");
       cout << "----- BORRAR INSCRIPCIÓN -----" << endl;

       cout << "Ingrese CI del socio: ";
       getline(cin, ciSocio);
       cout << "Ingrese ID de la clase: ";
       cin >> idClase;
       cin.ignore();

       try
       {
        borrarInscripcion(ciSocio, idClase);
        cout << "La inscripción fue eliminada correctamente." << endl;
        cin.ignore();
       }
       catch (invalid_argument &ex)
       {
         cout << "Error: " << ex.what() << endl;
       }

      break;
    }
    case 5:
    {
      system("clear");
      cout << "----- LISTAR INFO DE SOCIOS POR CLASE -----" << endl;
      cout << "Ingrese el ID de la clase: ";

      cin >> idClase;
      cin.ignore();
      
      int cantSocios = 0;
      
      for (int i = 0; i < clasesActuales; i++)
      {
        if (arrClases[i]->getID() == idClase)
        {
          if (dynamic_cast<Spinning *>(arrClases[i]) != nullptr)
          {
            Spinning *spinning = dynamic_cast<Spinning *>(arrClases[i]);
            cantSocios = spinning->getCantInscriptos();
          }
          else if (dynamic_cast<Entrenamiento *>(arrClases[i]) != nullptr)
          {
            Entrenamiento *entrenamiento = dynamic_cast<Entrenamiento *>(arrClases[i]);
            cantSocios = entrenamiento->getCantInscriptos();
          }
        }
      }

      try
      {
        DtSocio **socios = obtenerInfoSociosPorClase(idClase, cantSocios);
      }
      catch (invalid_argument &ex)
      {
        cout << "Error: " << ex.what() << endl;
      }
      break;
    }

    case 6:
      system("clear");
      cout << "----- LISTAR INFO CLASE -----" << endl;
      cout << "Ingrese id de la clase: ";
      cin >> idClase;
      cin.ignore();
      system("clear");

      try
      {
        DtClase dtClase = obtenerClase(idClase); // Crear un puntero a la clase base
        DtClase *dtClasePtr = new DtClase(dtClase); // Crear un puntero a la clase base
        string tipo;
        int bicis;
        bool rambla;

        for (int i = 0; i < clasesActuales; i++) {
          if (dynamic_cast<Spinning *>(arrClases[i]) != nullptr) {
            Spinning *spinning = dynamic_cast<Spinning *>(arrClases[i]);
            dtClasePtr = new DtSpinning(spinning->getID(), spinning->getNombre(), spinning->getTurno(), spinning->getCantidadBicicletas());
            tipo = "Spinning";
            bicis = spinning->getCantidadBicicletas();
          } else if (dynamic_cast<Entrenamiento *>(arrClases[i]) != nullptr) {
            Entrenamiento *entrenamiento = dynamic_cast<Entrenamiento *>(arrClases[i]);
            dtClasePtr = new DtEntrenamiento(entrenamiento->getID(), entrenamiento->getNombre(), entrenamiento->getTurno(), entrenamiento->getEnRambla());
            tipo = "Entrenamiento";
            rambla = entrenamiento->getEnRambla();
          }
        }
         // Crear un puntero a la clase base
        cout << "Clase ID: " << dtClase.getId() << endl;
        cout << "Nombre: " << dtClase.getNombre() << endl;
        cout << "Turno: " << (dtClase.getTurno() == Turno::Manana ? "Mañana" : (dtClase.getTurno() == Turno::Tarde ? "Tarde" : "Noche")) << endl;
        cout << "Tipo: " << tipo << endl;
        if (tipo == "Spinning")
        {
          cout << "Cantidad de bicicletas: " << bicis << endl;
        }
        else if (tipo == "Entrenamiento")
        {
          cout << "En Rambla: " << (rambla ? "Sí" : "No") << endl;
        }
      }
      catch (invalid_argument &ex)
      {
        cout << "Error: " << ex.what() << endl;
      }
      break;

    case 7:
      salir = true;
      break;
    default:
      cout << "Opcion no valida. Intente de nuevo." << endl;
      cin.ignore();
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

  /*
   // datos para probar la sobrecragra dek operador
  DtClase clase(1, "Clase de Prueba", Turno::Manana);
  agregarClase(clase);
  obtenerClase(1);

  agregarSocio("12345678", "Juan Perez");
  agregarSocio("87654321", "Maria Lopez");

  agregarInscripcion("12345678", 1, Fecha(1, 1, 2023));
  cout << "Inscripcion de Juan Perez a la clase 1" << endl;
  agregarInscripcion("87654321", 1, Fecha(1, 1, 2023));
  cout << "Inscripcion de Maria Lopez a la clase 1" << endl;

  DtSpinning spinning(1, "Spinning Avanzado", Turno::Manana, 30);
  DtEntrenamiento entrenamiento(2, "Entrenamiento Funcional", Turno::Tarde, true);

  cout << spinning << endl;
  cout << entrenamiento << endl;
  */
  return 0;
}
