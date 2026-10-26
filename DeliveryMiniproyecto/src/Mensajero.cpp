#include <iostream>
#include "Mensajero.h"
using namespace std;

Mensajero::Mensajero() : Entidad() {
    vehiculo = "";
    placa = "";
    disponible = true;
}

Mensajero::Mensajero(string n, string v, string p, Ubicacion u) : Entidad(n, u) {
    vehiculo = v;
    placa = p;
    disponible = true;
}

void Mensajero::mostrar() const {
    cout << "[MENSAJERO] " << vehiculo << " (" << placa << ") | "
         << (disponible ? "DISPONIBLE" : "OCUPADO") << " | ";
    Entidad::mostrar();
}

void Mensajero::guardar(ostream& out) const {
    out << "M;" << nombre << ";" << vehiculo << ";" << placa << ";"
        << ubicacion.getLatitud() << ";" << ubicacion.getLongitud() << ";"
        << (disponible ? 1 : 0) << endl;
}
