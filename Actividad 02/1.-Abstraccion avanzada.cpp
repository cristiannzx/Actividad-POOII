#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
using namespace std;

const double PI = 3.14159265358979;

// ---------- Clase abstracta: define el QUÉ ----------
class Figura {
public:
    virtual ~Figura() = default;
    virtual double area() const = 0;
    virtual double perimetro() const = 0;
    virtual string nombre() const = 0;
};

// ---------- Clase concreta: define el CÓMO ----------
class Circulo : public Figura {
private:
    double radio;
public:
    explicit Circulo(double r) : radio(r) {}
    double area() const override { return PI * radio * radio; }
    double perimetro() const override { return 2 * PI * radio; }
    string nombre() const override { return "Circulo"; }
};

class Rectangulo : public Figura {
private:
    double base, altura;
public:
    Rectangulo(double b, double h) : base(b), altura(h) {}
    double area() const override { return base * altura; }
    double perimetro() const override { return 2 * (base + altura); }
    string nombre() const override { return "Rectangulo"; }
};

// ---------- Código cliente: solo conoce el QUÉ ----------
void mostrarInformacion(const Figura& f) {
    cout << fixed << setprecision(2);
    cout << f.nombre() << " -> Area: " << f.area()
         << " | Perimetro: " << f.perimetro() << endl;
}

int main() {
    vector<unique_ptr<Figura>> figuras;
    figuras.push_back(make_unique<Circulo>(3));
    figuras.push_back(make_unique<Rectangulo>(4, 5));

    for (const auto& fig : figuras) {
        mostrarInformacion(*fig);
    }
    return 0;
}