#include<iostream>
using namespace std;

class Lampara {
private:                     // ENCAPSULAMIENTO: esto está escondido
    bool encendida;
    int brillo;              // de 0 a 100

public:                      // ABSTRACCIÓN: esto es lo único que el usuario ve
    Lampara() {
        encendida = false;
        brillo = 0;
    }

    void encender() {
        encendida = true;
        brillo = 50;
        cout << "La lampara se encendio." << endl;
    }

    void apagar() {
        encendida = false;
        brillo = 0;
        cout << "La lampara se apago." << endl;
    }

    void subirBrillo() {
        if (encendida && brillo < 100) {
            brillo = brillo + 10;
            cout << "Brillo: " << brillo << endl;
        } else {
            cout << "No se puede subir el brillo." << endl;
        }
    }
};

int main() {
    Lampara miLampara;

    miLampara.encender();
    miLampara.subirBrillo();
    miLampara.apagar();
    miLampara.subirBrillo();   // no funciona porque está apagada

    // miLampara.brillo = 500;  // ERROR: brillo es private
    return 0;
}