#pragma once
#include <string>

class Producto {
private:
    std::string nombre;
    double precio;
    int stock;

public:
    Producto();
    Producto(std::string n, double p, int s = 0);

    std::string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }

    bool hayStock(int cantidad) const { return stock >= cantidad; }
    void descontar(int cantidad) { stock -= cantidad; }
    void reponer(int cantidad) { stock += cantidad; }
};
