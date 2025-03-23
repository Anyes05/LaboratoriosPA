#include "Socio.h"
#include <iostream>

Socio::Socio(string n, string c){
    this->nombre = n;
    this->ci = c;
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
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"CI: "<<ci<<endl;
}

Socio::~Socio(){}