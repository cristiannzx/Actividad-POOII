#include <iostream>
#include <string>
#include "Sistema.h"
#include "Menu.h"
#include "Utilidades.h"
using namespace std;

namespace {
    enum OpPrincipal  { P_PEDIDOS = 1, P_NEGOCIOS, P_PERSONAS, P_CONSULTAS, P_EJEMPLO };
    enum OpPedidos    { PE_CREAR = 1, PE_AVANZAR, PE_ACTIVAS, PE_TODAS };
    enum OpNegocios   { N_REGISTRAR = 1, N_AGREGAR_PRODUCTO, N_VER_MENU, N_REPONER, N_LISTAR };
    enum OpPersonas   { PS_CLIENTE = 1, PS_MENSAJERO, PS_VER_CLIENTES, PS_VER_MENSAJEROS };
    enum OpConsultas  { C_RESUMEN = 1, C_HISTORIAL, C_REINICIAR };
}

string resumenEstado(const Sistema& sistema) {
    return "Negocios: " + to_string(sistema.getCantNegocios()) +
           " | Clientes: " + to_string(sistema.getCantClientes()) +
           " | Mensajeros libres: " + to_string(sistema.contarMensajerosLibres()) +
           "/" + to_string(sistema.getCantMensajeros()) +
           " | Ordenes activas: " + to_string(sistema.contarOrdenesActivas());
}

// ==========================================================================
// SUBMENU: PEDIDOS Y ENTREGAS
// ==========================================================================
void menuPedidos(Sistema& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        int activas = sistema.contarOrdenesActivas();
        string motivoOrden = sistema.motivoBloqueoCrearOrden();

        Menu menu("PEDIDOS Y ENTREGAS", resumenEstado(sistema));
        menu.agregarOpcion(PE_CREAR, "Crear orden", motivoOrden == "", motivoOrden);
        menu.agregarOpcion(PE_AVANZAR, "Avanzar estado de una orden (" + to_string(activas) + " activas)",
                           activas > 0, "no hay ordenes activas");
        menu.agregarOpcion(PE_ACTIVAS, "Ver ordenes activas",
                           activas > 0, "no hay ordenes activas");
        menu.agregarOpcion(PE_TODAS, "Ver todas las ordenes de esta sesion",
                           sistema.getCantOrdenes() > 0, "todavia no se creo ninguna orden");

        opcion = menu.elegir("Volver al menu principal");
        switch (opcion) {
            case PE_CREAR:   sistema.crearOrden();          break;
            case PE_AVANZAR: sistema.avanzarEstadoOrden();  break;
            case PE_ACTIVAS: sistema.verOrdenesActivas();   break;
            case PE_TODAS:   sistema.verOrdenes();          break;
        }
        if (opcion != 0) pausar();
    }
}

// ==========================================================================
// SUBMENU: NEGOCIOS, MENUS Y STOCK
// ==========================================================================
void menuNegocios(Sistema& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        bool hayNegocios = sistema.getCantNegocios() > 0;

        Menu menu("NEGOCIOS, MENUS Y STOCK", resumenEstado(sistema));
        menu.agregarOpcion(N_REGISTRAR, "Registrar negocio",
                           sistema.getCantNegocios() < MAX_NEGOCIOS, "limite de negocios alcanzado");
        menu.agregarOpcion(N_AGREGAR_PRODUCTO, "Agregar producto al menu de un negocio",
                           hayNegocios, "registra un negocio primero");
        menu.agregarOpcion(N_VER_MENU, "Ver menu de un negocio",
                           hayNegocios, "registra un negocio primero");
        menu.agregarOpcion(N_REPONER, "Reponer stock de un producto",
                           sistema.hayNegocioConStock(), "ningun negocio registrado controla stock");
        menu.agregarOpcion(N_LISTAR, "Ver negocios registrados",
                           hayNegocios, "registra un negocio primero");

        opcion = menu.elegir("Volver al menu principal");
        switch (opcion) {
            case N_REGISTRAR:        sistema.registrarNegocio();       break;
            case N_AGREGAR_PRODUCTO: sistema.agregarProductoAlMenu();  break;
            case N_VER_MENU:         sistema.verMenu();                break;
            case N_REPONER:          sistema.reponerStock();           break;
            case N_LISTAR:           sistema.listarNegocios();         break;
        }
        if (opcion != 0) pausar();
    }
}

// ==========================================================================
// SUBMENU: CLIENTES Y MENSAJEROS
// ==========================================================================
void menuPersonas(Sistema& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        Menu menu("CLIENTES Y MENSAJEROS", resumenEstado(sistema));
        menu.agregarOpcion(PS_CLIENTE, "Registrar cliente",
                           sistema.getCantClientes() < MAX_CLIENTES, "limite de clientes alcanzado");
        menu.agregarOpcion(PS_MENSAJERO, "Registrar mensajero",
                           sistema.getCantMensajeros() < MAX_MENSAJEROS, "limite de mensajeros alcanzado");
        menu.agregarOpcion(PS_VER_CLIENTES, "Ver clientes",
                           sistema.getCantClientes() > 0, "no hay clientes registrados");
        menu.agregarOpcion(PS_VER_MENSAJEROS, "Ver mensajeros",
                           sistema.getCantMensajeros() > 0, "no hay mensajeros registrados");

        opcion = menu.elegir("Volver al menu principal");
        switch (opcion) {
            case PS_CLIENTE:         sistema.registrarCliente();     break;
            case PS_MENSAJERO:       sistema.registrarMensajero();   break;
            case PS_VER_CLIENTES:    sistema.listarClientes();       break;
            case PS_VER_MENSAJEROS:  sistema.listarMensajeros();     break;
        }
        if (opcion != 0) pausar();
    }
}

// ==========================================================================
// SUBMENU: CONSULTAS E HISTORIAL
// ==========================================================================
void menuConsultas(Sistema& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        Menu menu("CONSULTAS E HISTORIAL", resumenEstado(sistema));
        menu.agregarOpcion(C_RESUMEN, "Ver todo lo registrado (negocios, clientes, mensajeros)",
                           !sistema.estaVacio(), "todavia no hay nada registrado");
        menu.agregarOpcion(C_HISTORIAL, "Leer bitacora de transacciones (archivo " + ARCHIVO + ")");
        menu.agregarOpcion(C_REINICIAR, "Reiniciar: borrar todos los datos guardados");

        opcion = menu.elegir("Volver al menu principal");
        switch (opcion) {
            case C_RESUMEN:   sistema.listarEntidades();  break;
            case C_HISTORIAL: sistema.leerHistorial();    break;
            case C_REINICIAR: sistema.reiniciarDatos();   break;
        }
        if (opcion != 0) pausar();
    }
}

// ==========================================================================
// MAIN: crea el Sistema y ejecuta el menu principal
// ==========================================================================
int main() {
    Sistema sistema;
    bool salir = false;

    while (!salir) {
        Menu menu("DELIVERY", resumenEstado(sistema));
        menu.agregarOpcion(P_PEDIDOS,   "Pedidos y entregas (" + to_string(sistema.contarOrdenesActivas()) + " activas)");
        menu.agregarOpcion(P_NEGOCIOS,  "Negocios, menus y stock (" + to_string(sistema.getCantNegocios()) + ")");
        menu.agregarOpcion(P_PERSONAS,  "Clientes y mensajeros");
        menu.agregarOpcion(P_CONSULTAS, "Consultas e historial");
        if (sistema.estaVacio())
            menu.agregarOpcion(P_EJEMPLO, "Cargar datos de ejemplo (para probar rapido)");

        switch (menu.elegir("Salir")) {
            case P_PEDIDOS:   menuPedidos(sistema);   break;
            case P_NEGOCIOS:  menuNegocios(sistema);  break;
            case P_PERSONAS:  menuPersonas(sistema);  break;
            case P_CONSULTAS: menuConsultas(sistema); break;
            case P_EJEMPLO:   sistema.cargarEjemplo(); pausar(); break;
            case 0:           cout << "Hasta luego." << endl; salir = true; break;
        }
    }
    return 0;
}
