#pragma once
#include <string>
#include "Config.h"
#include "Negocio.h"
#include "Cliente.h"
#include "Mensajero.h"
#include "Orden.h"

class Sistema {
private:
    Negocio negocios[MAX_NEGOCIOS];
    Cliente clientes[MAX_CLIENTES];
    Mensajero mensajeros[MAX_MENSAJEROS];
    Orden ordenes[MAX_ORDENES];

    int cantNegocios;
    int cantClientes;
    int cantMensajeros;
    int cantOrdenes;
    int siguienteId;

    // persistencia
    void guardarTransaccion(const Orden& o);   // bitacora: agrega una linea a ordenes.txt
    void cargarUltimoId();                     // continua la numeracion segun la bitacora
    void guardarDatos() const;                 // foto completa del sistema en datos.txt
    void cargarDatos();                        // lee datos.txt al iniciar

    // logica interna
    int buscarMensajeroCercano(Ubicacion puntoNegocio) const;
    int elegirNegocio(bool soloConStock = false, bool soloConProductos = false);
    int elegirCliente();
    bool llenarCarrito(Orden& orden, int n, int enCarrito[]);

public:
    Sistema();

    // ----- consultas de estado (las usa el menu dinamico) -----
    int getCantNegocios() const { return cantNegocios; }
    int getCantClientes() const { return cantClientes; }
    int getCantMensajeros() const { return cantMensajeros; }
    int getCantOrdenes() const { return cantOrdenes; }
    int contarMensajerosLibres() const;
    int contarOrdenesActivas() const;
    bool hayNegocioConStock() const;
    bool hayNegocioConProductos() const;
    bool estaVacio() const;
    std::string motivoBloqueoCrearOrden() const;   // "" si se puede crear

    // ----- registro -----
    void registrarNegocio();
    void registrarCliente();
    void registrarMensajero();

    // ----- menu y stock -----
    void agregarProductoAlMenu();
    void verMenu();
    void reponerStock();

    // ----- ordenes -----
    void crearOrden();
    void avanzarEstadoOrden();
    void verOrdenes() const;
    void verOrdenesActivas() const;
    void leerHistorial() const;

    // ----- listados -----
    void listarNegocios() const;
    void listarClientes() const;
    void listarMensajeros() const;
    void listarEntidades() const;

    void cargarEjemplo();
    void reiniciarDatos();     // borra datos.txt y ordenes.txt (pide confirmacion)
};
