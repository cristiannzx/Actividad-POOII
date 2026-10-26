#pragma once
#include <string>
#include "Ubicacion.h"

class Entidad {
protected:
    std::string nombre;
    Ubicacion ubicacion;

public:
    Entidad();
    Entidad(std::string n, Ubicacion u);
    virtual ~Entidad() {}

    std::string getNombre() const { return nombre; }
    Ubicacion getUbicacion() const { return ubicacion; }
    void setUbicacion(Ubicacion u) { ubicacion = u; }

    // Metodo virtual PURO: Entidad es una clase abstracta (no se puede crear una
    // "Entidad" suelta). Cada hija esta OBLIGADA a definir su propio mostrar().
    virtual void mostrar() const = 0;
};
