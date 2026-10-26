#pragma once
#include <string>
#include <iosfwd>
#include "Entidad.h"

class Mensajero : public Entidad {
private:
    std::string vehiculo;
    std::string placa;
    bool disponible;

public:
    Mensajero();
    Mensajero(std::string n, std::string v, std::string p, Ubicacion u);

    bool estaDisponible() const { return disponible; }
    void setDisponible(bool d) { disponible = d; }

    void mostrar() const override;
    void guardar(std::ostream& out) const;     // linea "M;..." de datos.txt
};
