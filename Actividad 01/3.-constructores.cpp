#include <iostream>
#include <string>
using namespace std;

class Libro {
private:
    string titulo;
    string autor;
    int paginas;

public:
    // CONSTRUCTOR 1: por defecto (sin parametros)
    Libro() {
        titulo = "Sin titulo";
        autor = "Desconocido";
        paginas = 0;
    }

    // CONSTRUCTOR 2: recibe solo el titulo
    Libro(string t) {
        titulo = t;
        autor = "Desconocido";
        paginas = 0;
    }

    // CONSTRUCTOR 3: recibe todos los datos
    Libro(string t, string a, int p) {
        titulo = t;
        autor = a;
        paginas = p;
    }

    void mostrarDatos() {
        cout << "Titulo: " << titulo
            << " | Autor: " << autor
            << " | Paginas: " << paginas << endl;
    }
};

int main() {
    Libro libro1;                                    // constructor 1 (por defecto)
    Libro libro2("El Principito");                   // constructor 2
    Libro libro3("Cien anios de soledad", "Garcia Marquez", 471);  // constructor 3

    cout << "Libro 1: ";
    libro1.mostrarDatos();
    cout << "Libro 2: ";
    libro2.mostrarDatos();
    cout << "Libro 3: ";
    libro3.mostrarDatos();

    return 0;
}