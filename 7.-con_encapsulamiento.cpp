#include <iostream>
#include <string>
using namespace std;
class PersonaEncapsulada {
private:
    string nombre;
    int edad;
    double estatura;
public:
    PersonaEncapsulada(const string& nombre, int edad, double estatura);
    string getNombre() const;
    int getEdad() const;
    double getEstatura() const;
    bool setNombre(const string& nuevoNombre);
    bool setEdad(int nuevaEdad);
    bool setEstatura(double nuevaEstatura);
    void mostrar() const;
};
PersonaEncapsulada::PersonaEncapsulada(const string& nombre, int edad, double estatura)
    : nombre("Sin nombre"), edad(0), estatura(1.0) {
    setNombre(nombre);
    setEdad(edad);
    setEstatura(estatura);
}
string PersonaEncapsulada::getNombre() const { return nombre; }
int PersonaEncapsulada::getEdad() const { return edad; }
double PersonaEncapsulada::getEstatura() const { return estatura; }

bool PersonaEncapsulada::setNombre(const string& nuevoNombre) {
    if (nuevoNombre.empty()) return false;
    nombre = nuevoNombre;
    return true;
}
bool PersonaEncapsulada::setEdad(int nuevaEdad) {
    if (nuevaEdad < 0 || nuevaEdad > 120) return false;
    edad = nuevaEdad;
    return true;
}
bool PersonaEncapsulada::setEstatura(double nuevaEstatura) {
    if (nuevaEstatura < 0.5 || nuevaEstatura > 2.5) return false;
    estatura = nuevaEstatura;
    return true;
}
void PersonaEncapsulada::mostrar() const {
    cout << "Nombre: " << nombre << " | Edad: " << edad << " | Estatura: " << estatura << " m\n";
}
int main() {
    PersonaEncapsulada p("Pedro Apaza", 25, 1.72);

#ifdef PRUEBA_ERROR_ACCESO
    p.edad = -40;
    int leida = p.edad;
    cout << leida << "\n";
#endif

    cout << "Lectura mediante getters: " << p.getNombre() << ", " << p.getEdad() << ", " << p.getEstatura() << "\n\n";

    cout << "setEdad(-40): " << (p.setEdad(-40) ? "aceptado" : "rechazado") << "\n";
    cout << "setEstatura(9.5): " << (p.setEstatura(9.5) ? "aceptado" : "rechazado") << "\n";
    cout << "setNombre(\"\"): " << (p.setNombre("") ? "aceptado" : "rechazado") << "\n";
    cout << "setEdad(26): " << (p.setEdad(26) ? "aceptado" : "rechazado") << "\n\n";

    cout << "Estado final (los datos invalidos no entraron):\n";
    p.mostrar();
    return 0;
}
