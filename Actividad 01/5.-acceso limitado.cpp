#include <iostream>
#include <string>
using namespace std;

// CLASE PADRE
class Cuenta {
private:
    double saldo;

    // METODO PRIVADO 1
    void registrarMovimiento(string texto) {
        cout << "[Registro] " << texto << endl;
    }

    // METODO PRIVADO 2
    bool validarClave(int clave) {
        return clave == 1234;
    }

protected:
    // Metodo protected: la hija SI puede usarlo (para comparar)
    void mostrarSaldo() {
        cout << "Saldo: S/ " << saldo << endl;
    }

public:
    Cuenta() {
        saldo = 100;
    }

    // Metodo public: todos pueden usarlo
    void depositar(double monto) {
        saldo += monto;
        registrarMovimiento("Deposito");   // el PADRE si puede usar sus metodos privados
    }
};

// CLASE HIJA
class CuentaAhorro : public Cuenta {
public:
    void probarAcceso() {
        depositar(50);       // OK: es public
        mostrarSaldo();      // OK: es protected

        // PRUEBA 1
        registrarMovimiento("Hola");

        // PRUEBA 2
        validarClave(1234);
    }
};

int main() {
    CuentaAhorro miCuenta;
    miCuenta.probarAcceso();
    return 0;
}
