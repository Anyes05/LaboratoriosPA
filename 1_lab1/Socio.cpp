#include "Socio.h"
#include <iostream>

Socio::Socio(string c, string n){
    this->ci = c;
    this->nombre = n;
    
}

string Socio::getNombre(){
    return this->nombre;
}

string Socio::getCi(){
    return this->ci;
}

void Socio::setNombre(string n){
    this->nombre = n;
}

void Socio::setCi(string c){
    this->ci = c;
}

void Socio::mostrarSocio(){
    cout<< "El Socio Agregado es: " << endl;
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"CI: "<<ci<<endl;
}

Socio::~Socio(){}