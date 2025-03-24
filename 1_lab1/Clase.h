#ifndef CLASE_H
#define CLASE_H

#include <iostream>
using namespace std;

// Estructura para manejar los turnos
enum _retorno
{
    Manana,
    Tarde,
    Noche
};
typedef enum _retorno Turno;

class Clase
{
private:
    int id;
    string nombre;
    Turno turno;
public:
    Clase(int, string, Turno);
    int getId();
    void setId(int);
    string getNombre();
    void setNombre(string);
    Turno getTurno ();
    void setTurno(Turno);
    virtual int cupo() const = 0;
    ~Clase();
};


#endif