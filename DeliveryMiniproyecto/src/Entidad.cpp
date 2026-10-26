#include <iostream>
#include "Entidad.h"
using namespace std;

Entidad::Entidad() {
    nombre = "";
}

Entidad::Entidad(string n, Ubicacion u) {
    nombre = n;
    ubicacion = u;
}

// Aunque es virtual puro, tiene cuerpo: las hijas lo reutilizan con Entidad::mostrar()
void Entidad::mostrar() const {
    cout << nombre << " | GPS: (" << ubicacion.getLatitud() << ", "
         << ubicacion.getLongitud() << ")" << endl;
}
