#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

class Estudiante {
private:
    string nombre;
    int anio;
    double gpa;
    double presupuesto;
public:
    Estudiante() : nombre("NN"), anio(0), gpa(0), presupuesto(0) {}

    Estudiante(string n, int a, double g, double p)
        : nombre(n), anio(a), gpa(g), presupuesto(p) {}

    string getNombre() const { return nombre; }
    int getAnio() const { return anio; }
    double getGpa() const { return gpa; }
    double getPresupuesto() const { return presupuesto; }

    void setNombre(const string &n) { nombre = n; }
    void setAnio(int a) { anio = a; }
    void setGpa(double g) { gpa = g; }
    void setPresupuesto(double p) { presupuesto = p; }

    double indiceU() const {
        return fabs(gpa - 3) * presupuesto;
    }
};
class GestorEstudiantes {
private:
    vector<Estudiante> lista;
public:
    GestorEstudiantes() {}
    GestorEstudiantes(const vector<Estudiante> &inicial) : lista(inicial) {}
    int tamanio() const { return (int)lista.size(); }
    bool vacio() const { return lista.empty(); }
    // ---------- INSERTAR ----------
    void insertarAlFinal(const Estudiante &e) {
        lista.push_back(e);
    }
    bool insertarEnIndice(int i, const Estudiante &e) {
        if (i < 0 || i > (int)lista.size()) return false;
        lista.insert(lista.begin() + i, e);
        return true;
    }
    // ---------- ELIMINAR ----------
    bool eliminarUltimo() {
        if (lista.empty()) return false;
        lista.pop_back();
        return true;
    }
    bool eliminarEnIndice(int i) {
        if (lista.empty()) return false;
        if (i < 0 || i >= (int)lista.size()) return false;
        lista.erase(lista.begin() + i);
        return true;
    }
    // ---------- ACTUALIZAR ----------
    bool actualizar(int i, const Estudiante &nuevo) {
        if (i < 0 || i >= (int)lista.size()) return false;
        lista[i] = nuevo;
        return true;
    }
    // ---------- ORDENAR (ascendente) ----------
    void ordenarPorAnio() {
        sort(lista.begin(), lista.end(), [](const Estudiante &a, const Estudiante &b) {
            return a.getAnio() < b.getAnio();
        });
    }
    void ordenarPorGPA() {
        sort(lista.begin(), lista.end(), [](const Estudiante &a, const Estudiante &b) {
            return a.getGpa() < b.getGpa();
        });
    }
    void ordenarPorPresupuesto() {
        sort(lista.begin(), lista.end(), [](const Estudiante &a, const Estudiante &b) {
            return a.getPresupuesto() < b.getPresupuesto();
        });
    }
    void ordenarPorIndiceU() {
        sort(lista.begin(), lista.end(), [](const Estudiante &a, const Estudiante &b) {
            return a.indiceU() < b.indiceU();
        });
    }
    // ---------- IMPRIMIR ----------
    void imprimir() const {
        if (lista.empty()) {
            cout << "  (vector vacio)\n";
            return;
        }
        cout << "  " << left << setw(5) << "Idx" << setw(16) << "Nombre"
            << setw(8) << "Anio" << setw(8) << "GPA"
            << setw(14) << "Presupuesto" << "Indice U.\n";
        cout << fixed << setprecision(2);
        int i = 0;
        for (const auto &e : lista) {
            cout << "  " << left << setw(5) << i << setw(16) << e.getNombre()
                << setw(8) << e.getAnio() << setw(8) << e.getGpa()
                << setw(14) << e.getPresupuesto() << e.indiceU() << "\n";
            i++;
        }
        cout << "  Total: " << lista.size() << " estudiante(s)\n";
    }
};
// LECTURA DE DATOS
int leerEntero(const string &mensaje) {
    int x;
    while (true) {
        cout << mensaje;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Entrada invalida, intente de nuevo.\n";
    }
}
double leerReal(const string &mensaje) {
    double x;
    while (true) {
        cout << mensaje;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Entrada invalida, intente de nuevo.\n";
    }
}
Estudiante leerEstudiante() {
    string nombre;
    cout << "Nombre: ";
    getline(cin, nombre);
    if (nombre.empty()) nombre = "NN";
    int anio = leerEntero("Anio de nacimiento: ");
    double gpa = leerReal("Promedio (GPA): ");
    double presupuesto = leerReal("Presupuesto: ");
    return Estudiante(nombre, anio, gpa, presupuesto);
}
void menuInsertar(GestorEstudiantes &g) {
    cout << "\n-- INSERTAR --\n";
    cout << "1. Por defecto (NN,0,0,0)\n2. Con datos\n";
    int tipo = leerEntero("Opcion: ");
    cout << "1. Al final\n2. En un indice\n";
    int donde = leerEntero("Opcion: ");

    Estudiante e;                       // por defecto NN,0,0,0
    if (tipo == 2) e = leerEstudiante();

    if (donde == 1) {
        g.insertarAlFinal(e);
        cout << "Estudiante insertado al final.\n";
    } else if (donde == 2) {
        int i = leerEntero("Indice (0 a " + to_string(g.tamanio()) + "): ");
        if (g.insertarEnIndice(i, e)) cout << "Estudiante insertado.\n";
        else cout << "Indice invalido.\n";
    } else {
        cout << "Opcion invalida.\n";
    }
}
void menuEliminar(GestorEstudiantes &g) {
    cout << "\n-- ELIMINAR --\n";
    if (g.vacio()) {
        cout << "El vector esta vacio, no se puede eliminar.\n";
        return;
    }
    cout << "1. El ultimo\n2. Desde un indice\n";
    int op = leerEntero("Opcion: ");
    if (op == 1) {
        g.eliminarUltimo();
        cout << "Ultimo estudiante eliminado.\n";
    } else if (op == 2) {
        int i = leerEntero("Indice (0 a " + to_string(g.tamanio() - 1) + "): ");
        if (g.eliminarEnIndice(i)) cout << "Estudiante eliminado.\n";
        else cout << "Indice invalido.\n";
    } else {
        cout << "Opcion invalida.\n";
    }
}
void menuActualizar(GestorEstudiantes &g) {
    cout << "\n-- ACTUALIZAR --\n";
    if (g.vacio()) {
        cout << "El vector esta vacio, no hay nada que actualizar.\n";
        return;
    }
    int i = leerEntero("Indice (0 a " + to_string(g.tamanio() - 1) + "): ");
    if (i < 0 || i >= g.tamanio()) {
        cout << "Indice invalido.\n";
        return;
    }
    cout << "Nuevos datos:\n";
    g.actualizar(i, leerEstudiante());
    cout << "Estudiante actualizado.\n";
}
void menuOrdenar(GestorEstudiantes &g) {
    cout << "\n-- ORDENAR (ascendente) --\n";
    cout << "1. Por anio de nacimiento\n2. Por GPA\n3. Por presupuesto\n"
        << "4. Por indice universidad\n";
    int op = leerEntero("Opcion: ");
    if (op == 1) g.ordenarPorAnio();
    else if (op == 2) g.ordenarPorGPA();
    else if (op == 3) g.ordenarPorPresupuesto();
    else if (op == 4) g.ordenarPorIndiceU();
    else { cout << "Opcion invalida.\n"; return; }
    cout << "Lista ordenada.\n";
}
// PRUEBAS DE FUNCIONAMIENTO
vector<Estudiante> datosBase(int n = 4) {
    vector<Estudiante> base = {
        {"Tony",  2003, 3.8, 500},
        {"Daemon", 2001, 2.5, 1000},
        {"Eren",  2005, 3.0, 800},
        {"Paul",  2002, 4.0, 200}
    };
    base.resize(n);
    return base;
}

void encabezado(const string &titulo, const string &entrada, const string &esperada) {
    cout << "\n==============================================================\n";
    cout << titulo << "\n";
    cout << "ENTRADA : " << entrada << "\n";
    cout << "ESPERADA: " << esperada << "\n";
    cout << "OBTENIDA:\n";
}
void ejecutarPruebas() {
    cout << "pruebas de funcionamiento\n";
    // ----- INSERTAR (2 pruebas) -----
    {
        GestorEstudiantes g;
        encabezado("PRUEBA 1: Insertar SIN datos",
                "vector vacio; insertar estudiante por defecto al final",
                "[0] NN 0 0.00 0.00");
        g.insertarAlFinal(Estudiante());
        g.imprimir();
    }
    {
        GestorEstudiantes g;
        g.insertarAlFinal(Estudiante());
        encabezado("PRUEBA 2: Insertar CON datos en un indice",
                "vector [NN]; insertar (Maria,2004,3.5,300) en indice 0",
                "[0] Maria 2004 3.50 300.00 | [1] NN 0 0.00 0.00");
        g.insertarEnIndice(0, {"Maria", 2004, 3.5, 300});
        g.imprimir();
    }
    // ----- ELIMINAR (3 pruebas) -----
    {
        GestorEstudiantes g(datosBase(3));      // Tony, Daemon, Eren
        encabezado("PRUEBA 3: Eliminar el ULTIMO",
                "vector [Tony, Daemon, Eren]; eliminar el ultimo",
                "[Tony, Daemon, Eren] -> [Tony, Daemon]");
        g.eliminarUltimo();
        g.imprimir();
    }
    {
        GestorEstudiantes g(datosBase(3));      // Tony, Daemon, Eren
        encabezado("PRUEBA 4: Eliminar desde un INDICE",
                "vector [Tony, Daemon, Eren]; eliminar indice 1",
                "[Tony, Eren]");
        g.eliminarEnIndice(1);
        g.imprimir();
    }
    {
        GestorEstudiantes g;
        encabezado("PRUEBA 5: No se elimina con vector VACIO",
                "vector vacio; intentar eliminar el ultimo",
                "retorna false y el vector sigue vacio");
        bool ok = g.eliminarUltimo();
        cout << "  eliminarUltimo devolvio: " << (ok ? "true" : "false") << "\n";
        g.imprimir();
    }
    // ----- ACTUALIZAR (1 prueba) -----
    {
        GestorEstudiantes g(datosBase(2));      // Tony, Daemon
        encabezado("PRUEBA 6: Actualizar un estudiante",
                "vector [Tony, Daemon]; indice 1 = (Daemon Smith,2000,3.2,750)",
                "[Tony, Daemon Smith 2000 3.20 750.00]");
        g.actualizar(1, {"Daemon Smith", 2000, 3.2, 750});
        g.imprimir();
    }
    // ----- ORDENAR (4 pruebas) -----
    {
        GestorEstudiantes g(datosBase());
        encabezado("PRUEBA 7: Ordenar por ANIO",
                "[Tony 2003, Daemon 2001, Eren 2005, Paul 2002]",
                "Daemon(2001), Paul(2002), Tony(2003), Eren(2005)");
        g.ordenarPorAnio();
        g.imprimir();
    }
    {
        GestorEstudiantes g(datosBase());
        encabezado("PRUEBA 8: Ordenar por GPA",
                "[Tony 3.8, Daemon 2.5, Eren 3.0, Paul 4.0]",
                "Daemon(2.5), Eren(3.0), Tony(3.8), Paul(4.0)");
        g.ordenarPorGPA();
        g.imprimir();
    }
    {
        GestorEstudiantes g(datosBase());
        encabezado("PRUEBA 9: Ordenar por PRESUPUESTO",
                "[Tony 500, Daemon 1000, Eren 800, Paul 200]",
                "Paul(200), Tony(500), Eren(800), Daemon(1000)");
        g.ordenarPorPresupuesto();
        g.imprimir();
    }
    {
        GestorEstudiantes g(datosBase());
        encabezado("PRUEBA 10: Ordenar por INDICE UNIVERSIDAD",
                "Tony=|3.8-3|*500=400, Daemon=|2.5-3|*1000=500, "
                "Eren=0*800=0, Paul=|4-3|*200=200",
                "Eren(0), Paul(200), Tony(400), Daemon(500)");
        g.ordenarPorIndiceU();
        g.imprimir();
    }
    cout << "\n FIN DE LAS PRUEBAS \n";
}
int main() {
    GestorEstudiantes estudiantes;
    int opcion;
    do {
        cout << "\n-------MENU ESTUDIANTES-------\n"
            << "1. Insertar estudiante\n"
            << "2. Eliminar estudiante\n"
            << "3. Actualizar estudiante\n"
            << "4. Ordenar\n"
            << "5. Imprimir\n"
            << "6. Ejecutar pruebas de funcionamiento\n"
            << "0. Salir\n";
        opcion = leerEntero("Opcion: ");
        if (opcion == 1) menuInsertar(estudiantes);
        else if (opcion == 2) menuEliminar(estudiantes);
        else if (opcion == 3) menuActualizar(estudiantes);
        else if (opcion == 4) menuOrdenar(estudiantes);
        else if (opcion == 5) {
            cout << "\n-- ESTUDIANTES --\n";
            estudiantes.imprimir();
        }
        else if (opcion == 6) ejecutarPruebas();
        else if (opcion == 0) cout << "Hasta luego.\n";
        else cout << "Opcion invalida.\n";
    } while (opcion != 0);
    return 0;
}