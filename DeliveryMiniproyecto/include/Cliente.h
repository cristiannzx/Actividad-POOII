#pragma once
#include <string>
#include <iosfwd>
#include "Entidad.h"

class Cliente : public Entidad {
private:
    std::string telefono;

public:
    Cliente();
    Cliente(std::string n, std::string tel, Ubicacion u);

    void mostrar() const override;
    void guardar(std::ostream& out) const;     // linea "C;..." de datos.txt
};
