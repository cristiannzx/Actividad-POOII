#include <array>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
    array<string, 12> paises = {"Argentina", "Bolivia", "Brasil", "Chile",
                                "Colombia", "Ecuador", "Guyana", "Paraguay",
                                "Peru", "Surinam"};

    //"a. Insertar los restantes con at() y con []:" << endl;
    paises.at(10) = "Uruguay";
    paises[11] = "Venezuela";

    cout << "b. Paises que inician con C o P:" << endl;
    for (auto p : paises) {
        if (p[0] == 'C' || p[0] == 'P') cout << p << endl;
    }

    cout << endl << "c. Primer elemento: " << paises.front() << endl;
    cout << "   Ultimo elemento: " << paises.back() << endl;

    sort(paises.begin(), paises.end());
    cout << endl << "d. Paises ordenados:" << endl;
    for (auto p : paises) cout << p << ", ";
    return 0;
}
