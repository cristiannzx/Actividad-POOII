#pragma once
#include <string>
#include <iosfwd>
#include "Config.h"
#include "Entidad.h"
#include "Producto.h"

class Negocio : public Entidad {
private:
    std::string tipo;
    bool controlaStock;
    Producto menu[MAX_PRODUCTOS];
    int cantidadProductos;

public:
    Negocio();
    Negocio(std::string n, std::string t, Ubicacion u);

    std::string getTipo() const { return tipo; }
    int getCantidadProductos() const { return cantidadProductos; }
    Producto getProducto(int i) const { return menu[i]; }
    bool getControlaStock() const { return controlaStock; }
    int getStock(int i) const { return menu[i].getStock(); }

    bool agregarProducto(std::string nombreProd, double precio, int stock = 0);
    bool hayStock(int i, int cantidad) const;
    void descontarStock(int i, int cantidad);
    void reponerStock(int i, int cantidad);

    void mostrarMenu() const;
    void mostrar() const override;
    void guardar(std::ostream& out) const;     // linea "N;..." + una "P;..." por producto
};
