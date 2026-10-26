#include <iostream>
#include "Cliente.h"
using namespace std;

Cliente::Cliente() : Entidad() {
    telefono = "";
}

Cliente::Cliente(string n, string tel, Ubicacion u) : Entidad(n, u) {
    telefono = tel;
}

void Cliente::mostrar() const {
    cout << "[CLIENTE] tel: " << telefono << " | ";
    Entidad::mostrar();
}

void Cliente::guardar(ostream& out) const {
    out << "C;" << nombre << ";" << telefono << ";"
        << ubicacion.getLatitud() << ";" << ubicacion.getLongitud() << endl;
}
