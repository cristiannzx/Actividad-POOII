#include <iostream>
#include <string>
using namespace std;

// CLASE PADRE
class Animal {
protected:                       // las hijas SÍ pueden usar esto
    string nombre;

public:
    Animal(string n) {
        nombre = n;
    }

    void presentarse() {         // se HEREDA tal cual
        cout << "Soy " << nombre << endl;
    }

    virtual void hacerSonido() { // virtual: cada hija podrá cambiarlo
        cout << nombre << " hace un sonido" << endl;
    }

    virtual ~Animal() {}
};

// CLASE HIJA 1: HERENCIA (: public Animal)
class Pato : public Animal {
public:
    Pato(string n) : Animal(n) {}

    void hacerSonido() override {
        cout << nombre << " dice: Cuac cuac" << endl;
    }
};

// CLASE HIJA 2: HERENCIA (: public Animal)
class Lobo : public Animal {
public:
    Lobo(string n) : Animal(n) {}

    void hacerSonido() override {
        cout << nombre << " dice: Auuuu" << endl;
    }
};

int main() {
    Pato miPato("Donald");
    Lobo miLobo("Akela");

    cout << "--- Herencia ---" << endl;
    miPato.presentarse();        // método heredado de Animal
    miLobo.presentarse();        // método heredado de Animal

    cout << "\n--- Polimorfismo ---" << endl;
    Animal* animales[2] = { &miPato, &miLobo };

    for (int i = 0; i < 2; i++) {
        animales[i]->hacerSonido();   // misma orden, distinta respuesta
    }

    return 0;
}