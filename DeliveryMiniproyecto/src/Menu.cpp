#include <iostream>
#include "Menu.h"
#include "Utilidades.h"
using namespace std;

Menu::Menu(string t, string e) {
    titulo = t;
    estado = e;
    cantidad = 0;
}

void Menu::agregarOpcion(int codigo, string texto, bool habilitada, string motivo) {
    if (cantidad >= MAX_OPCIONES_MENU) return;
    codigos[cantidad] = codigo;
    textos[cantidad] = texto;
    habilitadas[cantidad] = habilitada;
    motivos[cantidad] = motivo;
    cantidad++;
}

void Menu::mostrar(const string& textoSalir) const {
    cout << endl << "========== " << titulo << " ==========" << endl;
    if (estado != "") cout << estado << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << textos[i];
        if (!habilitadas[i]) cout << "   [bloqueada: " << motivos[i] << "]";
        cout << endl;
    }
    cout << "0. " << textoSalir << endl;
}

int Menu::elegir(string textoSalir) {
    while (true) {
        mostrar(textoSalir);
        int op = leerEntero("Elige una opcion: ");
        if (op == 0) return 0;
        if (op < 1 || op > cantidad) {
            cout << "Opcion invalida." << endl;
            continue;
        }
        if (!habilitadas[op - 1]) {
            cout << "No disponible todavia: " << motivos[op - 1] << "." << endl;
            continue;
        }
        return codigos[op - 1];
    }
}
