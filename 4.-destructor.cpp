#include <iostream>
#include <string>
using namespace std;
class BufferDatos {
private:
    string nombre;
    int* datos;
    int capacidad;
public:
    BufferDatos(const string& nombre, int capacidad);
    ~BufferDatos();
    BufferDatos(const BufferDatos&) = delete;
    BufferDatos& operator=(const BufferDatos&) = delete;
    void llenar();
    void mostrar() const;
};
BufferDatos::BufferDatos(const string& nombre, int capacidad)
    : nombre(nombre), datos(new int[capacidad]), capacidad(capacidad) {
    cout << "[Constructor] " << nombre << ": reservados " << capacidad << " enteros en el heap\n";
}
BufferDatos::~BufferDatos() {
    delete[] datos;
    datos = nullptr;
    cout << "[Destructor] " << nombre << ": memoria liberada\n";
}
void BufferDatos::llenar() {
    for (int i = 0; i < capacidad; i++) datos[i] = (i + 1) * 10;
}
void BufferDatos::mostrar() const {
    cout << nombre << ": ";
    for (int i = 0; i < capacidad; i++) cout << datos[i] << " ";
    cout << "\n";
}
int main() {
    cout << "--- Objeto dinamico: delete explicito ---\n";
    BufferDatos* dinamico = new BufferDatos("Dinamico", 3);
    dinamico->llenar();
    dinamico->mostrar();
    delete dinamico;
    cout << "\n--- Objeto en ambito interno: destructor al salir del bloque ---\n";
    {
        BufferDatos local("Local", 4);
        local.llenar();
        local.mostrar();
        cout << "Fin del bloque\n";
    }
    cout << "\n--- Objeto en main: destructor al terminar el programa ---\n";
    BufferDatos principal("Principal", 2);
    principal.llenar();
    principal.mostrar();
    cout << "Fin de main\n";
    return 0;
}
