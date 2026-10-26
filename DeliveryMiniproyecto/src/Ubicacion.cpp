#include <cmath>
#include "Ubicacion.h"
using namespace std;

Ubicacion::Ubicacion() {
    latitud = 0;
    longitud = 0;
}

Ubicacion::Ubicacion(double la, double lo) {
    latitud = la;
    longitud = lo;
}

double Ubicacion::distanciaKm(const Ubicacion& otra) const {
    const double R = 6371.0;
    const double PI = 3.14159265358979;
    double lat1 = latitud * PI / 180;
    double lat2 = otra.latitud * PI / 180;
    double dLat = lat2 - lat1;
    double dLon = (otra.longitud - longitud) * PI / 180;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * asin(sqrt(a));
    return R * c;
}
