#ifndef DTCLASE_H
#define DTCLASE_H

#include <ostream>
#include <string>
#include "Turno.h"

using namespace std;

class DtClase
{
private:
    int ID;
    string nombre;
    Turno turno;

public:
    DtClase(int, string, Turno);
    virtual ~DtClase();
    int getId();
    string getNombre();
    Turno getTurno();

    /*Ejercicio 3: Definir la sobrecarga del operador << en la clase base DtClase y en las clases derivadas DtSpinning y DtEntrenamiento.*/
  
    virtual void print(ostream &out) const {
        out << "ID: " << ID << "\nNombre: " << nombre << "\nTurno: ";
        switch (turno) {
            case Turno::Manana:
                out << "Mañana";
                break;
            case Turno::Tarde:
                out << "Tarde";
                break;
            case Turno::Noche:
                out << "Noche";
                break;
        }
        out << endl;  // Asegura que la salida termina con un salto de línea
    }

    friend ostream& operator<<(ostream &out, const DtClase &clase) {
        clase.print(out);
        return out;
    }
};

#endif