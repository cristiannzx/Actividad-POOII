#include <iostream>
#include <string>

class CuentaBancaria {
private:
    std::string titular;
    double saldo;
    int pin;
    int intentosFallidos;
    bool bloqueada;

public:
    CuentaBancaria(const std::string& titular, double saldoInicial, int pin)
        : titular(titular),
        saldo(saldoInicial >= 0 ? saldoInicial : 0),
        pin(pin),
        intentosFallidos(0),
        bloqueada(false) {}

    bool depositar(double monto) {
        if (monto <= 0) {
            return false;
        }
        saldo += monto;
        return true;
    }

    bool retirar(double monto, int pinIngresado) {
        if (bloqueada) {
            return false;
        }
        if (pinIngresado != pin) {
            intentosFallidos++;
            if (intentosFallidos >= 3) {
                bloqueada = true;
            }
            return false;
        }
        intentosFallidos = 0;
        if (monto <= 0 || monto > saldo) {
            return false;
        }
        saldo -= monto;
        return true;
    }

    double consultarSaldo() const {
        return saldo;
    }

    bool estaBloqueada() const {
        return bloqueada;
    }
};

std::string estado(bool ok) {
    return ok ? "aceptado" : "rechazado";
}

int main() {
    CuentaBancaria cuenta("Ana", 1000.0, 1234);

    std::cout << "Deposito de -50: " << estado(cuenta.depositar(-50)) << "\n";
    std::cout << "Deposito de 200: " << estado(cuenta.depositar(200)) << "\n";
    std::cout << "Saldo: " << cuenta.consultarSaldo() << "\n";

    std::cout << "Retiro de 5000 con PIN correcto: "
            << estado(cuenta.retirar(5000, 1234)) << "\n";

    for (int i = 1; i <= 3; i++) {
        std::cout << "Retiro con PIN incorrecto (intento " << i << "): "
                << estado(cuenta.retirar(100, 0)) << "\n";
    }

    std::cout << "Cuenta bloqueada: " << (cuenta.estaBloqueada() ? "si" : "no") << "\n";
    std::cout << "Retiro de 100 con PIN correcto tras bloqueo: "
            << estado(cuenta.retirar(100, 1234)) << "\n";
    std::cout << "Saldo final: " << cuenta.consultarSaldo() << "\n";

    return 0;
}