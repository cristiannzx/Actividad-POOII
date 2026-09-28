#include <iostream>
#include <string>
using namespace std;
class Estudiante {
private:
    string nombre;
    int edad;
    string codigo;
public:
    Estudiante();
    Estudiante(const string& nombre);
    Estudiante(const string& nombre, int edad, const string& codigo);
    void mostrar() const;
};
Estudiante::Estudiante() : nombre("Sin nombre"), edad(0), codigo("000000") {
    cout << "[Constructor por defecto]\n";
}
Estudiante::Estudiante(const string& nombre) : nombre(nombre), edad(0), codigo("000000") {
    cout << "[Constructor con nombre]\n";
}
Estudiante::Estudiante(const string& nombre, int edad, const string& codigo)
    : nombre(nombre), edad(edad), codigo(codigo) {
    cout << "[Constructor completo]\n";
}
void Estudiante::mostrar() const {
    cout << "Nombre: " << nombre << " | Edad: " << edad << " | Codigo: " << codigo << "\n\n";
}
int main() {
    Estudiante e1;
    Estudiante e2("Rosa Condori");
    Estudiante e3("Jose Huanca", 19, "231234");
    e1.mostrar();
    e2.mostrar();
    e3.mostrar();
    return 0;
}
