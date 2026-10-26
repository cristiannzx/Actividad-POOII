#pragma once
#include <string>
#include <iosfwd>
#include "Config.h"

enum Estado { PENDIENTE = 0, PREPARANDO = 1, EN_CAMINO = 2, ENTREGADO = 3 };

std::string textoEstado(Estado e);

class Orden {
private:
    int id;
    std::string nombreCliente;
    std::string nombreNegocio;
    std::string nombreMensajero;
    int indiceCliente;
    int indiceMensajero;

    std::string nombresItems[MAX_ITEMS];
    double preciosItems[MAX_ITEMS];
    int cantidadesItems[MAX_ITEMS];
    int cantidadItems;

    double distanciaKm;
    double subtotal;
    double tarifaEntrega;
    Estado estado;

public:
    Orden();

    int getId() const { return id; }
    Estado getEstado() const { return estado; }
    bool estaActiva() const { return estado != ENTREGADO; }
    int getIndiceCliente() const { return indiceCliente; }
    int getIndiceMensajero() const { return indiceMensajero; }
    int getCantidadItems() const { return cantidadItems; }
    double getTotal() const { return subtotal + tarifaEntrega; }

    void iniciar(int idOrden, std::string cliente, int idxCliente, std::string negocio);
    // Reconstruye una orden leida de datos.txt (los items se agregan despues con agregarItem)
    void restaurar(int idOrden, std::string cliente, std::string negocio, std::string mensajero,
                   int idxCliente, int idxMensajero, double km, double tarifa, int estadoNumero);
    bool agregarItem(std::string nombre, double precio, int cantidad);
    void definirEntrega(double km);
    void asignarMensajero(std::string nombre, int indice);
    bool avanzarEstado();

    void mostrarTrazado() const;
    std::string resumenItems() const;
    std::string aLineaArchivo() const;
    void mostrar() const;
    void guardar(std::ostream& out) const;     // linea "O;..." + una "I;..." por item
};
