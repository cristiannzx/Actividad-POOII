#include <iostream>
#include <iomanip>
#include "Negocio.h"
#include "Utilidades.h"
using namespace std;

Negocio::Negocio() : Entidad() {
    tipo = "";
    cantidadProductos = 0;
    controlaStock = false;
}

Negocio::Negocio(string n, string t, Ubicacion u) : Entidad(n, u) {
    tipo = t;
    cantidadProductos = 0;
    controlaStock = tipoUsaStock(t);
}

bool Negocio::agregarProducto(string nombreProd, double precio, int stock) {
    if (cantidadProductos >= MAX_PRODUCTOS) return false;
    menu[cantidadProductos] = Producto(nombreProd, precio, stock);
    cantidadProductos++;
    return true;
}

bool Negocio::hayStock(int i, int cantidad) const {
    if (!controlaStock) return true;
    return menu[i].hayStock(cantidad);
}

void Negocio::descontarStock(int i, int cantidad) {
    if (controlaStock) menu[i].descontar(cantidad);
}

void Negocio::reponerStock(int i, int cantidad) {
    menu[i].reponer(cantidad);
}

void Negocio::mostrarMenu() const {
    cout << "--- MENU de " << nombre << " ---" << endl;
    if (cantidadProductos == 0) {
        cout << "(sin productos todavia)" << endl;
        return;
    }
    for (int i = 0; i < cantidadProductos; i++) {
        cout << i + 1 << ". " << menu[i].getNombre()
             << "  - S/ " << fixed << setprecision(2) << menu[i].getPrecio();
        if (controlaStock) {
            if (menu[i].getStock() == 0) cout << "  [AGOTADO]";
            else cout << "  [Stock: " << menu[i].getStock() << "]";
        }
        cout << endl;
    }
}

void Negocio::mostrar() const {
    cout << "[NEGOCIO - " << tipo << (controlaStock ? " - con stock" : "") << "] ";
    Entidad::mostrar();
}

void Negocio::guardar(ostream& out) const {
    out << "N;" << nombre << ";" << tipo << ";"
        << ubicacion.getLatitud() << ";" << ubicacion.getLongitud() << endl;
    for (int i = 0; i < cantidadProductos; i++) {
        out << "P;" << menu[i].getNombre() << ";" << menu[i].getPrecio() << ";"
            << menu[i].getStock() << endl;
    }
}
