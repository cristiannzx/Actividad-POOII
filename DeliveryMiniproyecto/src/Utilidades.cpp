#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Utilidades.h"
using namespace std;

static const int CANT_TIPOS_STOCK = 8;
static const string TIPOS_CON_STOCK[CANT_TIPOS_STOCK] = {
    "farmacia", "botica", "tienda", "bodega",
    "minimarket", "supermercado", "libreria", "ferreteria"
};

string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++) texto[i] = tolower((unsigned char)texto[i]);
    return texto;
}

bool tipoUsaStock(string tipo) {
    string t = aMinusculas(tipo);
    for (int i = 0; i < CANT_TIPOS_STOCK; i++) {
        if (t.find(TIPOS_CON_STOCK[i]) != string::npos) return true;
    }
    return false;
}

// Lee una linea. El caracter ';' separa los campos de los archivos, asi que se
// cambia por ',' para que nunca rompa el formato.
string leerTexto(string mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);
    for (size_t i = 0; i < texto.size(); i++)
        if (texto[i] == ';' || texto[i] == '\r') texto[i] = ',';
    return texto;
}

int leerEntero(string mensaje) {
    int numero;
    cout << mensaje;
    while (!(cin >> numero)) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Dato invalido. " << mensaje;
    }
    cin.ignore(10000, '\n');
    return numero;
}

double leerDecimal(string mensaje) {
    double numero;
    cout << mensaje;
    while (!(cin >> numero)) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Dato invalido. " << mensaje;
    }
    cin.ignore(10000, '\n');
    return numero;
}

void pausar() {
    cout << endl << "Presiona Enter para continuar...";
    string basura;
    getline(cin, basura);
}

int dividir(const string& linea, string campos[], int maximo) {
    int cantidad = 0;
    string actual = "";
    for (size_t i = 0; i <= linea.size(); i++) {
        if (i == linea.size() || linea[i] == ';') {
            if (cantidad < maximo) { campos[cantidad] = actual; cantidad++; }
            actual = "";
        } else {
            actual += linea[i];
        }
    }
    return cantidad;
}

double leerCoordenada(string mensaje, double minimo, double maximo) {
    double valor = leerDecimal(mensaje);
    while (valor < minimo || valor > maximo) {
        cout << "Fuera de rango (" << minimo << " a " << maximo << "). Revisa el signo y el orden." << endl;
        valor = leerDecimal(mensaje);
    }
    return valor;
}
