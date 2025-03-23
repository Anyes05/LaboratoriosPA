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

/*
ostream& operator<<(ostream& os, DtEmpresa* emp) {
  if (DtNacional* nacional = dynamic_cast<DtNacional*>(emp)) { // Es una empresa nacional
    os << nacional->print();
  } else if (DtExtranjera* extranjera = dynamic_cast<DtExtranjera*>(emp)) { // Es una empresa extranjera
    os << extranjera->print();
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, DtEmpresa *empresa)
{
    empresa->imprimir(os);
    return os;
}
*/

/*----- FUNCIONES PRINCIPALES -----*/

/* A) Crea un nuevo socio en el sistema. En caso de ya existir, levanta la excepción
std::invalid_argument.*/
void agregarSocio(string ci, string nombre)
{
}

/*B) Crea una nueva clase en el sistema. En caso de ya existir, levanta una excepción
std::invalid_argument.*/
void agregarClase(DtClase clase)
{
}

/*C) Crea una inscripción de un socio a una clase. La inscripción tiene lugar siempre y
cuando el socio y la clase existan, de lo contrario se levanta una excepción
std::invalid_argument. Si ya existe una inscripción de ese usuario para esa clase, o si
el cupo de esa clase ya fue alcanzado, también se levanta una excepción
std::invalid_argument. */
void agregarInscripcion(String ciSocio, int idClase, Fecha fecha)
{
}

/* D) Borra la inscripción de un socio a una clase. Si no existe una inscripción de ese
usuario para esa clase, se levanta una excepción std::invalid_argument.*/
void borrarInscripcion(string ciSocio, int idClase)
{
}

/*E) Retorna un arreglo con los socios que están inscriptos a determinada clase. El largo
del arreglo de socios deberá ser cargado en el parámetro cantSocios.*/
DtSocio **obtenerInfoSociosPorClase(id idClase, int &cantSocios) {}

/*F) Retorna la información de la clase identificada por idClase. */
DtClase obtenerClase(int idClase) {}

int main()
{

    return 0;
}
