#include <iostream>
using namespace std;

class CuentaBancaria {
private:
    // DETALLE OCULTO
    double saldo;

public:
    // Parte que mostramos al exterior
    CuentaBancaria(double saldoInicial) {
        saldo = saldoInicial;
    }

    void depositar(double cantidad) {
        saldo = saldo + cantidad;
    }

    void retirar(double cantidad) {
        if (cantidad <= saldo) {
            saldo = saldo - cantidad;
        } else {
            cout << "No hay suficiente dinero." << endl;
        }
    }

    double consultarSaldo() {
        return saldo;
    }
};

int main() {

    CuentaBancaria cuenta(1000);

    cuenta.depositar(500);
    cuenta.retirar(200);

    cout << "Saldo actual: "
         << cuenta.consultarSaldo() << endl;

    return 0;
}