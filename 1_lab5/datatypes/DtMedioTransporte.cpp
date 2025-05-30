#include "DtMedioTransporte.h"

DtMedioTransporte::DtMedioTransporte() {}

DtMedioTransporte::DtMedioTransporte(string medioTransporte) {
    this->medioTransporte = medioTransporte;
}

string DtMedioTransporte::getMedioTransporte() {
    return medioTransporte;
}
