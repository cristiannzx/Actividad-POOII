#include <iostream>
#include <sstream>
#include <iomanip>
#include "Orden.h"
using namespace std;

string textoEstado(Estado e) {
    if (e == PENDIENTE)  return "Pendiente";
    if (e == PREPARANDO) return "Preparando";
    if (e == EN_CAMINO)  return "En camino";
    return "Entregado";
}

Orden::Orden() {
    id = 0;
    indiceCliente = -1;
    indiceMensajero = -1;
    cantidadItems = 0;
    distanciaKm = 0;
    subtotal = 0;
    tarifaEntrega = 0;
    estado = PENDIENTE;
}

void Orden::iniciar(int idOrden, string cliente, int idxCliente, string negocio) {
    id = idOrden;
    nombreCliente = cliente;
    indiceCliente = idxCliente;
    nombreNegocio = negocio;
    estado = PENDIENTE;
}

bool Orden::agregarItem(string nombre, double precio, int cantidad) {
    if (cantidadItems >= MAX_ITEMS) return false;
    nombresItems[cantidadItems] = nombre;
    preciosItems[cantidadItems] = precio;
    cantidadesItems[cantidadItems] = cantidad;
    subtotal += precio * cantidad;
    cantidadItems++;
    return true;
}

void Orden::definirEntrega(double km) {
    distanciaKm = km;
    tarifaEntrega = TARIFA_BASE + km * TARIFA_POR_KM;
}

void Orden::asignarMensajero(string nombre, int indice) {
    nombreMensajero = nombre;
    indiceMensajero = indice;
}

bool Orden::avanzarEstado() {
    if (estado == ENTREGADO) return false;
    estado = (Estado)(estado + 1);
    return true;
}

void Orden::mostrarTrazado() const {
    string pasos[4] = {"Pendiente", "Preparando", "En camino", "Entregado"};
    for (int i = 0; i < 4; i++) {
        if (i == (int)estado) cout << "[" << pasos[i] << "]";
        else cout << pasos[i];
        if (i < 3) cout << " -> ";
    }
    cout << endl;
}

string Orden::resumenItems() const {
    string r = "";
    for (int i = 0; i < cantidadItems; i++) {
        r += to_string(cantidadesItems[i]) + "x" + nombresItems[i];
        if (i < cantidadItems - 1) r += "|";
    }
    return r;
}

string Orden::aLineaArchivo() const {
    ostringstream total;
    total << fixed << setprecision(2) << getTotal();
    ostringstream dist;
    dist << fixed << setprecision(2) << distanciaKm;
    return to_string(id) + ";" + nombreCliente + ";" + nombreNegocio + ";" +
           nombreMensajero + ";" + resumenItems() + ";" +
           dist.str() + ";" + total.str() + ";" + textoEstado(estado);
}

void Orden::mostrar() const {
    cout << "--------------------------------------" << endl;
    cout << "ORDEN #" << id << " | Estado: " << textoEstado(estado) << endl;
    cout << "Trazado:   "; mostrarTrazado();
    cout << "Cliente:   " << nombreCliente << endl;
    cout << "Negocio:   " << nombreNegocio << endl;
    cout << "Mensajero: " << nombreMensajero << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < cantidadItems; i++) {
        cout << "  - " << cantidadesItems[i] << " x " << nombresItems[i]
             << " (S/ " << preciosItems[i] << ")" << endl;
    }
    cout << "Distancia: " << distanciaKm << " km" << endl;
    cout << "Subtotal:  S/ " << subtotal << endl;
    cout << "Entrega:   S/ " << tarifaEntrega << endl;
    cout << "TOTAL:     S/ " << getTotal() << endl;
}

void Orden::restaurar(int idOrden, string cliente, string negocio, string mensajero,
                      int idxCliente, int idxMensajero, double km, double tarifa, int estadoNumero) {
    id = idOrden;
    nombreCliente = cliente;
    nombreNegocio = negocio;
    nombreMensajero = mensajero;
    indiceCliente = idxCliente;
    indiceMensajero = idxMensajero;
    distanciaKm = km;
    tarifaEntrega = tarifa;
    if (estadoNumero < PENDIENTE) estadoNumero = PENDIENTE;
    if (estadoNumero > ENTREGADO) estadoNumero = ENTREGADO;
    estado = (Estado)estadoNumero;
}

void Orden::guardar(ostream& out) const {
    out << "O;" << id << ";" << nombreCliente << ";" << nombreNegocio << ";"
        << nombreMensajero << ";" << indiceCliente << ";" << indiceMensajero << ";"
        << distanciaKm << ";" << tarifaEntrega << ";" << (int)estado << endl;
    for (int i = 0; i < cantidadItems; i++) {
        out << "I;" << nombresItems[i] << ";" << preciosItems[i] << ";"
            << cantidadesItems[i] << endl;
    }
}
