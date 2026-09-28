#include <iostream>
#include <string>
using namespace std;
class PersonaAbierta {
public:
    string nombre;
    int edad;
    double estatura;

    void mostrar() const;
};
void PersonaAbierta::mostrar() const {
    cout << "Nombre: " << nombre << " | Edad: " << edad << " | Estatura: " << estatura << " m\n";
}
int main() {
    PersonaAbierta p;
    p.nombre = "Pedro Apaza";
    p.edad = 25;
    p.estatura = 1.72;
    cout << "Lectura directa de datos: " << p.nombre << ", " << p.edad << ", " << p.estatura << "\n";
    p.edad = -40;
    p.estatura = 9.5;
    p.nombre = "";
    cout << "Modificacion directa sin ninguna validacion:\n";
    p.mostrar();
    return 0;
}
