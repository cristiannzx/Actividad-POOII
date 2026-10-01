#include <iostream>
#include <string>
using namespace std;

class Libro {
public:
    string titulo;
    string autor;
    int paginas;
};

int main() {

    // Crear un objeto
    Libro libro1;

    // Asignar valores directamente
    libro1.titulo = "El Principito";
    libro1.autor = "Antoine de Saint-Exupery";
    libro1.paginas = 96;

    // Leer los valores directamente
    cout << "Titulo: " << libro1.titulo << endl;
    cout << "Autor: " << libro1.autor << endl;
    cout << "Paginas: " << libro1.paginas << endl;

    // Modificar los valores directamente
    libro1.titulo = "Cien anios de soledad";
    libro1.autor = "Gabriel Garcia Marquez";
    libro1.paginas = 471;

    cout << "\nDespues de modificar el libro:\n";

    // Leer nuevamente los valores
    cout << "Titulo: " << libro1.titulo << endl;
    cout << "Autor: " << libro1.autor << endl;
    cout << "Paginas: " << libro1.paginas << endl;

    return 0;
}