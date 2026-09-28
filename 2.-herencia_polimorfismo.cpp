#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
class Empleado {
protected:
    string nombre;
    double salarioBase;
public:
    Empleado(const string& nombre, double salarioBase);
    virtual ~Empleado() = default;
    virtual double calcularSalario() const;
    virtual string cargo() const;
    void mostrarInformacion() const;
};
class Gerente : public Empleado {
private:
    double bono;
public:
    Gerente(const string& nombre, double salarioBase, double bono);
    double calcularSalario() const override;
    string cargo() const override;
};
class Desarrollador : public Empleado {
private:
    int horasExtra;
    double pagoPorHoraExtra;
public:
    Desarrollador(const string& nombre, double salarioBase, int horasExtra, double pagoPorHoraExtra);
    double calcularSalario() const override;
    string cargo() const override;
};
Empleado::Empleado(const string& nombre, double salarioBase)
    : nombre(nombre), salarioBase(salarioBase) {}
double Empleado::calcularSalario() const {
    return salarioBase;
}
string Empleado::cargo() const {
    return "Empleado";
}
void Empleado::mostrarInformacion() const {
    cout << cargo() << " | " << nombre << " | Salario: " << calcularSalario() << "\n";
}
Gerente::Gerente(const string& nombre, double salarioBase, double bono)
    : Empleado(nombre, salarioBase), bono(bono) {}
double Gerente::calcularSalario() const {
    return salarioBase + bono;
}
string Gerente::cargo() const {
    return "Gerente";
}
Desarrollador::Desarrollador(const string& nombre, double salarioBase, int horasExtra, double pagoPorHoraExtra)
    : Empleado(nombre, salarioBase), horasExtra(horasExtra), pagoPorHoraExtra(pagoPorHoraExtra) {}
double Desarrollador::calcularSalario() const {
    return salarioBase + horasExtra * pagoPorHoraExtra;
}
string Desarrollador::cargo() const {
    return "Desarrollador";
}
int main() {
    vector<unique_ptr<Empleado>> planilla;
    planilla.push_back(make_unique<Empleado>("Luis Quispe", 1500.0));
    planilla.push_back(make_unique<Gerente>("Marta Rojas", 4000.0, 1500.0));
    planilla.push_back(make_unique<Desarrollador>("Carlos Mamani", 3000.0, 10, 40.0));
    cout << "=== POLIMORFISMO: misma llamada, distinto comportamiento ===\n";
    double total = 0;
    for (const auto& e : planilla) {
        e->mostrarInformacion();
        total += e->calcularSalario();
    }
    cout << "Total planilla: " << total << "\n";
    return 0;
}
