//-----SIN ENCAPSULAMIENTO-----
struct CuentaInsegura {
    double saldo;   // público: cualquiera puede modificarlo
};

int main() {
    CuentaInsegura c;
    c.saldo = -5000;   // valor inválido aceptado sin ninguna validación
}
//-----CON ENCAPSULAMIENTO-----
#include <iostream>
#include <string>
using namespace std;

class CuentaBancaria {
private:
    string titular;
    double saldo;

public:
    CuentaBancaria(const string& nombre, double saldoInicial)
        : titular(nombre), saldo(0) {
        if (saldoInicial > 0) {
            saldo = saldoInicial;
        }
    }

    bool depositar(double monto) {
        if (monto <= 0) {
            cout << "Error: el monto a depositar debe ser positivo." << endl;
            return false;
        }
        saldo += monto;
        return true;
    }

    bool retirar(double monto) {
        if (monto <= 0) {
            cout << "Error: el monto a retirar debe ser positivo." << endl;
            return false;
        }
        if (monto > saldo) {
            cout << "Error: saldo insuficiente." << endl;
            return false;
        }
        saldo -= monto;
        return true;
    }

    double getSaldo() const { return saldo; }
    string getTitular() const { return titular; }
};

int main() {
    CuentaBancaria cuenta("Cris Cruz", 1000);

    cuenta.depositar(500);
    cuenta.retirar(2000);     // rechazado: saldo insuficiente
    cuenta.depositar(-100);   // rechazado: monto inválido

    // cuenta.saldo = -5000;  // ERROR de compilación: 'saldo' es privado

    cout << "Titular: " << cuenta.getTitular() << endl;
    cout << "Saldo actual: " << cuenta.getSaldo() << endl;
    return 0;
}