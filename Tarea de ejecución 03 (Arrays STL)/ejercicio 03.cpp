#include <array>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct Estudiante {
    string nombre;
    int nacimiento;
    double gpa;
};

int main() {
    array<Estudiante, 10> est = {{{"Juan", 2000, 3.4}, {"Maria", 2005, 2.8}}};
    size_t pos = 2;

    // a. 3 y 4 elemento desde el teclado
    for (int i = 0; i < 2; i++) {
        cout << "Estudiante " << pos + 1 << " (nombre nacimiento gpa): ";
        cin >> est[pos].nombre >> est[pos].nacimiento >> est[pos].gpa;
        pos++;
    }

    // b. 5 y 6 elemento desde arrays básicos
    string nombres[] = {"Gaby", "Patty", "Diana"};
    int nacimientos[] = {2002, 2004, 2006};
    double gps[] = {3.8, 3.0, 2.9};
    for (int i = 0; i < 2; i++) {
        est.at(pos) = {nombres[i], nacimientos[i], gps[i]};
        pos++;
    }

    // c. Restantes desde datos.txt
    ifstream archivo("datos.txt");
    if (!archivo) {
        cout << "No se pudo abrir datos.txt" << endl;
        return 1;
    }
    while (pos < est.size() &&
        archivo >> est[pos].nombre >> est[pos].nacimiento >> est[pos].gpa) {
        pos++;
    }

    // d. Imprimir todos con edad actual y beca
    time_t t = time(nullptr);
    int anio = localtime(&t)->tm_year + 1900;
    cout << fixed << setprecision(1) << endl;
    for (auto e : est) {
        cout << e.nombre << " | Edad: " << anio - e.nacimiento
            << " | GPA: " << e.gpa
            << " | Beca: " << (e.gpa >= 3.5 ? "Si" : "No") << endl;
    }
    return 0;
}
