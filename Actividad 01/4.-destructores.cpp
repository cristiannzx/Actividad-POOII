#include <iostream>
#include <string>
using namespace std;

class Celular {
private:
    string dueno;

public:
    // CONSTRUCTOR: se ejecuta al crear el objeto
    Celular(string d) {
        dueno = d;
        cout << "[Constructor] Se prendio el celular de " << dueno << endl;
    }

    // DESTRUCTOR: se ejecuta al destruir el objeto (lleva ~)
    ~Celular() {
        cout << "[Destructor] Se apago el celular de " << dueno << endl;
    }

    void usar() {
        cout << "Usando el celular de " << dueno << endl;
    }
};

int main() {
    cout << "--- Inicio del programa ---" << endl;

    Celular c1("Ana");              // objeto normal

    cout << "\n--- Entrando al bloque ---" << endl;
    {
        Celular c2("Luis");         // nace aqui
        c2.usar();
    }                               // aqui c2 se destruye SOLO
    cout << "--- Saliendo del bloque ---" << endl;

    cout << "\n--- Objeto con new ---" << endl;
    Celular* c3 = new Celular("Pedro");
    c3->usar();
    delete c3;                      // USO EXPLICITO del destructor
    cout << "--- Fin del objeto con new ---" << endl;

    cout << "\n--- Fin del programa ---" << endl;
    return 0;                       // aqui c1 se destruye
}