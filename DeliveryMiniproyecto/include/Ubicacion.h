#pragma once

class Ubicacion {
private:
    double latitud;
    double longitud;

public:
    Ubicacion();
    Ubicacion(double la, double lo);

    double getLatitud() const { return latitud; }
    double getLongitud() const { return longitud; }

    double distanciaKm(const Ubicacion& otra) const;
};
