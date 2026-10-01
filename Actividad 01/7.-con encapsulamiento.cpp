#include <iostream>
#include <string>
using namespace std;

class Libro {
private:
    // Datos privados: no se pueden modificar directamente desde main()
    string titulo;
    string autor;
    int paginas;

public:
    // Métodos para modificar los datos (setters)

    void setTitulo(string t) {
        titulo = t;
    }

    void setAutor(string a) {
        autor = a;
    }

    void setPaginas(int p) {
        if (p >= 0) {
            paginas = p;
        } else {
            cout << "Error: las paginas no pueden ser negativas." << endl;
        }
    }

    // Métodos para leer los datos (getters)

    string getTitulo() {
        return titulo;
    }

    string getAutor() {
        return autor;
    }

    int getPaginas() {
        return paginas;
    }
};

int main() {

    // Crear un objeto
    Libro libro1;

    // Modificar los datos mediante métodos
    libro1.setTitulo("El Principito");
    libro1.setAutor("Antoine de Saint-Exupery");
    libro1.setPaginas(96);

    // Leer los datos mediante métodos
    cout << "Titulo: " << libro1.getTitulo() << endl;
    cout << "Autor: " << libro1.getAutor() << endl;
    cout << "Paginas: " << libro1.getPaginas() << endl;

    // Modificar nuevamente los datos
    libro1.setTitulo("Cien anios de soledad");
    libro1.setAutor("Gabriel Garcia Marquez");
    libro1.setPaginas(471);

    cout << "\nDespues de modificar el libro:\n";

    // Leer nuevamente los datos
    cout << "Titulo: " << libro1.getTitulo() << endl;
    cout << "Autor: " << libro1.getAutor() << endl;
    cout << "Paginas: " << libro1.getPaginas() << endl;

    return 0;
}