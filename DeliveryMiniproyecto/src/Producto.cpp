#include "Producto.h"
using namespace std;

Producto::Producto() {
    nombre = "";
    precio = 0;
    stock = 0;
}

Producto::Producto(string n, double p, int s) {
    nombre = n;
    precio = p;
    stock = s;
}
