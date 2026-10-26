#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>      // remove
#include <iomanip>     // setprecision
#include "Sistema.h"
#include "Utilidades.h"
using namespace std;

Sistema::Sistema() {
    cantNegocios = 0;
    cantClientes = 0;
    cantMensajeros = 0;
    cantOrdenes = 0;
    siguienteId = 1;
    cargarDatos();         // recupera lo que se guardo en la sesion anterior
    cargarUltimoId();      // y se asegura de no repetir numeros de orden
}

// ==========================================================================
// PERSISTENCIA
// ==========================================================================
void Sistema::guardarTransaccion(const Orden& o) {
    ofstream archivo(ARCHIVO.c_str(), ios::app);
    if (!archivo) {
        cout << "No se pudo abrir el archivo para guardar." << endl;
        return;
    }
    archivo << o.aLineaArchivo() << endl;
    archivo.close();
}

void Sistema::cargarUltimoId() {
    ifstream archivo(ARCHIVO.c_str());
    if (!archivo) return;
    string linea;
    int maximo = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campoId;
        getline(ss, campoId, ';');
        int idLeido = atoi(campoId.c_str());
        if (idLeido > maximo) maximo = idLeido;
    }
    archivo.close();
    if (maximo + 1 > siguienteId) siguienteId = maximo + 1;   // nunca baja el contador
}

void Sistema::leerHistorial() const {
    ifstream archivo(ARCHIVO.c_str());
    if (!archivo) {
        cout << "Todavia no hay historial guardado." << endl;
        return;
    }
    cout << "=== BITACORA DE TRANSACCIONES (archivo " << ARCHIVO << ") ===" << endl;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, cliente, negocio, mensajero, items, dist, total, estado;
        getline(ss, id, ';');
        getline(ss, cliente, ';');
        getline(ss, negocio, ';');
        getline(ss, mensajero, ';');
        getline(ss, items, ';');
        getline(ss, dist, ';');
        getline(ss, total, ';');
        getline(ss, estado, ';');
        cout << "#" << id << " | " << cliente << " <- " << negocio
             << " | Mensajero: " << mensajero << " | Items: " << items
             << " | Total: S/ " << total << " | " << estado << endl;
    }
    archivo.close();
}

// --------------------------------------------------------------------------
// FOTO DEL SISTEMA (datos.txt)
// Formato: una linea por registro, campos separados por ';'
//   N;nombre;tipo;lat;lon            negocio       (le siguen sus lineas P)
//   P;nombre;precio;stock            producto del ultimo negocio
//   C;nombre;telefono;lat;lon        cliente
//   M;nombre;vehiculo;placa;lat;lon;disponible(1/0)   mensajero
//   O;id;cliente;negocio;mensajero;idxCliente;idxMensajero;km;tarifa;estado
//   I;nombre;precio;cantidad         item de la ultima orden
// Cada clase sabe escribirse a si misma (metodo guardar), el Sistema solo
// recorre los arreglos.
// --------------------------------------------------------------------------
void Sistema::guardarDatos() const {
    ofstream archivo(ARCHIVO_DATOS.c_str());       // sin ios::app: reescribe todo
    if (!archivo) {
        cout << "No se pudo guardar " << ARCHIVO_DATOS << "." << endl;
        return;
    }
    archivo << setprecision(10);                   // para no perder decimales del GPS
    for (int i = 0; i < cantNegocios; i++)   negocios[i].guardar(archivo);
    for (int i = 0; i < cantClientes; i++)   clientes[i].guardar(archivo);
    for (int i = 0; i < cantMensajeros; i++) mensajeros[i].guardar(archivo);
    for (int i = 0; i < cantOrdenes; i++)    ordenes[i].guardar(archivo);
    archivo.close();
}

void Sistema::cargarDatos() {
    ifstream archivo(ARCHIVO_DATOS.c_str());
    if (!archivo) return;                          // primera vez: no hay nada que cargar

    string linea;
    string c[12];
    int maxId = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea[linea.size() - 1] == '\r') linea.erase(linea.size() - 1);
        int n = dividir(linea, c, 12);
        if (n < 1) continue;

        if (c[0] == "N" && n >= 5 && cantNegocios < MAX_NEGOCIOS) {
            negocios[cantNegocios] = Negocio(c[1], c[2], Ubicacion(atof(c[3].c_str()), atof(c[4].c_str())));
            cantNegocios++;
        } else if (c[0] == "P" && n >= 4 && cantNegocios > 0) {
            negocios[cantNegocios - 1].agregarProducto(c[1], atof(c[2].c_str()), atoi(c[3].c_str()));
        } else if (c[0] == "C" && n >= 5 && cantClientes < MAX_CLIENTES) {
            clientes[cantClientes] = Cliente(c[1], c[2], Ubicacion(atof(c[3].c_str()), atof(c[4].c_str())));
            cantClientes++;
        } else if (c[0] == "M" && n >= 7 && cantMensajeros < MAX_MENSAJEROS) {
            Mensajero m(c[1], c[2], c[3], Ubicacion(atof(c[4].c_str()), atof(c[5].c_str())));
            m.setDisponible(c[6] == "1");
            mensajeros[cantMensajeros] = m;
            cantMensajeros++;
        } else if (c[0] == "O" && n >= 10 && cantOrdenes < MAX_ORDENES) {
            int id = atoi(c[1].c_str());
            ordenes[cantOrdenes].restaurar(id, c[2], c[3], c[4],
                                           atoi(c[5].c_str()), atoi(c[6].c_str()),
                                           atof(c[7].c_str()), atof(c[8].c_str()),
                                           atoi(c[9].c_str()));
            cantOrdenes++;
            if (id > maxId) maxId = id;
        } else if (c[0] == "I" && n >= 4 && cantOrdenes > 0) {
            ordenes[cantOrdenes - 1].agregarItem(c[1], atof(c[2].c_str()), atoi(c[3].c_str()));
        }
    }
    archivo.close();
    if (maxId + 1 > siguienteId) siguienteId = maxId + 1;

    if (!estaVacio() || cantOrdenes > 0) {
        cout << "Datos de la sesion anterior cargados: " << cantNegocios << " negocios, "
             << cantClientes << " clientes, " << cantMensajeros << " mensajeros, "
             << cantOrdenes << " ordenes." << endl;
    }
}

void Sistema::reiniciarDatos() {
    cout << "Esto borra TODOS los datos guardados (" << ARCHIVO_DATOS << " y " << ARCHIVO << ")." << endl;
    string r = aMinusculas(leerTexto("Escribe SI para confirmar: "));
    if (r != "si") { cout << "Cancelado." << endl; return; }
    cantNegocios = 0;
    cantClientes = 0;
    cantMensajeros = 0;
    cantOrdenes = 0;
    siguienteId = 1;
    remove(ARCHIVO_DATOS.c_str());
    remove(ARCHIVO.c_str());
    cout << "Todo fue borrado. El sistema quedo vacio." << endl;
}

// ==========================================================================
// CONSULTAS DE ESTADO (para que el menu se adapte)
// ==========================================================================
int Sistema::contarMensajerosLibres() const {
    int libres = 0;
    for (int i = 0; i < cantMensajeros; i++)
        if (mensajeros[i].estaDisponible()) libres++;
    return libres;
}

int Sistema::contarOrdenesActivas() const {
    int activas = 0;
    for (int i = 0; i < cantOrdenes; i++)
        if (ordenes[i].estaActiva()) activas++;
    return activas;
}

bool Sistema::hayNegocioConStock() const {
    for (int i = 0; i < cantNegocios; i++)
        if (negocios[i].getControlaStock()) return true;
    return false;
}

bool Sistema::hayNegocioConProductos() const {
    for (int i = 0; i < cantNegocios; i++)
        if (negocios[i].getCantidadProductos() > 0) return true;
    return false;
}

bool Sistema::estaVacio() const {
    return cantNegocios == 0 && cantClientes == 0 && cantMensajeros == 0;
}

string Sistema::motivoBloqueoCrearOrden() const {
    if (!hayNegocioConProductos()) return "registra un negocio y agregale productos";
    if (cantClientes == 0)         return "registra un cliente";
    if (cantMensajeros == 0)       return "registra un mensajero";
    if (contarMensajerosLibres() == 0) return "todos los mensajeros estan ocupados (entrega una orden para liberar uno)";
    if (cantOrdenes >= MAX_ORDENES)    return "limite de ordenes alcanzado";
    return "";
}

// ==========================================================================
// SELECCION DINAMICA (solo muestra lo que sirve para la accion)
// ==========================================================================
int Sistema::buscarMensajeroCercano(Ubicacion puntoNegocio) const {
    int mejor = -1;
    double menorDistancia = 0;
    for (int i = 0; i < cantMensajeros; i++) {
        if (mensajeros[i].estaDisponible()) {
            double d = mensajeros[i].getUbicacion().distanciaKm(puntoNegocio);
            if (mejor == -1 || d < menorDistancia) {
                mejor = i;
                menorDistancia = d;
            }
        }
    }
    return mejor;
}

int Sistema::elegirNegocio(bool soloConStock, bool soloConProductos) {
    int indices[MAX_NEGOCIOS];     // posiciones reales de los negocios que cumplen
    int cant = 0;
    for (int i = 0; i < cantNegocios; i++) {
        if (soloConStock && !negocios[i].getControlaStock()) continue;
        if (soloConProductos && negocios[i].getCantidadProductos() == 0) continue;
        indices[cant] = i;
        cant++;
    }
    if (cant == 0) { cout << "No hay negocios disponibles para esta accion." << endl; return -1; }
    if (cant == 1) {
        cout << "Negocio: " << negocios[indices[0]].getNombre() << " (unico disponible)" << endl;
        return indices[0];
    }
    for (int i = 0; i < cant; i++) {
        cout << i + 1 << ". " << negocios[indices[i]].getNombre()
             << " (" << negocios[indices[i]].getTipo() << ")" << endl;
    }
    int op = leerEntero("Elige negocio (0 para cancelar): ");
    if (op == 0) { cout << "Cancelado." << endl; return -1; }
    if (op < 1 || op > cant) { cout << "Opcion invalida." << endl; return -1; }
    return indices[op - 1];
}

int Sistema::elegirCliente() {
    if (cantClientes == 1) {
        cout << "Cliente: " << clientes[0].getNombre() << " (unico registrado)" << endl;
        return 0;
    }
    for (int i = 0; i < cantClientes; i++) cout << i + 1 << ". " << clientes[i].getNombre() << endl;
    int op = leerEntero("Elige cliente (0 para cancelar): ");
    if (op == 0) { cout << "Cancelado." << endl; return -1; }
    if (op < 1 || op > cantClientes) { cout << "Cliente invalido." << endl; return -1; }
    return op - 1;
}

// ==========================================================================
// REGISTRO
// ==========================================================================
void Sistema::registrarNegocio() {
    if (cantNegocios >= MAX_NEGOCIOS) { cout << "Limite de negocios alcanzado." << endl; return; }
    string nombre = leerTexto("Nombre del negocio: ");
    string tipo = leerTexto("Tipo (restaurante, tienda, farmacia...): ");
    double lat = leerCoordenada("Latitud GPS (ej: -15.84): ", -90, 90);
    double lon = leerCoordenada("Longitud GPS (ej: -70.02): ", -180, 180);
    negocios[cantNegocios] = Negocio(nombre, tipo, Ubicacion(lat, lon));
    cantNegocios++;
    if (negocios[cantNegocios - 1].getControlaStock())
        cout << "Negocio registrado (este tipo de negocio controla stock)." << endl;
    else
        cout << "Negocio registrado." << endl;
    guardarDatos();
}

void Sistema::registrarCliente() {
    if (cantClientes >= MAX_CLIENTES) { cout << "Limite de clientes alcanzado." << endl; return; }
    string nombre = leerTexto("Nombre del cliente: ");
    string tel = leerTexto("Telefono: ");
    double lat = leerCoordenada("Latitud GPS: ", -90, 90);
    double lon = leerCoordenada("Longitud GPS: ", -180, 180);
    clientes[cantClientes] = Cliente(nombre, tel, Ubicacion(lat, lon));
    cantClientes++;
    cout << "Cliente registrado." << endl;
    guardarDatos();
}

void Sistema::registrarMensajero() {
    if (cantMensajeros >= MAX_MENSAJEROS) { cout << "Limite de mensajeros alcanzado." << endl; return; }
    string nombre = leerTexto("Nombre del mensajero: ");
    string vehiculo = leerTexto("Vehiculo (moto, bicicleta, auto...): ");
    string placa = leerTexto("Placa: ");
    double lat = leerCoordenada("Latitud GPS actual: ", -90, 90);
    double lon = leerCoordenada("Longitud GPS actual: ", -180, 180);
    mensajeros[cantMensajeros] = Mensajero(nombre, vehiculo, placa, Ubicacion(lat, lon));
    cantMensajeros++;
    cout << "Mensajero registrado." << endl;
    guardarDatos();
}

// ==========================================================================
// MENU Y STOCK
// ==========================================================================
void Sistema::agregarProductoAlMenu() {
    int n = elegirNegocio();
    if (n == -1) return;
    string nombre = leerTexto("Nombre del producto: ");
    double precio = leerDecimal("Precio (S/): ");
    int stock = 0;
    if (negocios[n].getControlaStock()) {
        stock = leerEntero("Stock inicial (unidades): ");
        if (stock < 0) stock = 0;
    }
    if (negocios[n].agregarProducto(nombre, precio, stock)) {
        cout << "Producto agregado." << endl;
        guardarDatos();
    } else {
        cout << "El menu esta lleno." << endl;
    }
}

void Sistema::verMenu() {
    int n = elegirNegocio();
    if (n == -1) return;
    negocios[n].mostrarMenu();
}

void Sistema::reponerStock() {
    int n = elegirNegocio(true, true);     // solo negocios con stock y con productos
    if (n == -1) return;
    negocios[n].mostrarMenu();
    int p = leerEntero("Numero de producto: ") - 1;
    if (p < 0 || p >= negocios[n].getCantidadProductos()) {
        cout << "Producto invalido." << endl;
        return;
    }
    int cant = leerEntero("Unidades a agregar: ");
    if (cant <= 0) { cout << "Cantidad invalida." << endl; return; }
    negocios[n].reponerStock(p, cant);
    cout << "Stock actualizado." << endl;
    guardarDatos();
}

// ==========================================================================
// ORDENES
// ==========================================================================
bool Sistema::llenarCarrito(Orden& orden, int n, int enCarrito[]) {
    int opcion = -1;
    while (opcion != 0) {
        negocios[n].mostrarMenu();
        opcion = leerEntero("Numero de producto (0 para terminar): ");
        if (opcion >= 1 && opcion <= negocios[n].getCantidadProductos()) {
            int idx = opcion - 1;
            Producto p = negocios[n].getProducto(idx);

            int disponible = 0;
            if (negocios[n].getControlaStock()) {
                disponible = p.getStock() - enCarrito[idx];
                if (disponible <= 0) {
                    cout << p.getNombre() << " esta agotado." << endl;
                    continue;
                }
                cout << "Hay " << disponible << " unidades disponibles de "
                     << p.getNombre() << "." << endl;
            }

            int cant = leerEntero("Cantidad: ");
            if (cant <= 0) {
                cout << "Cantidad invalida." << endl;
            } else if (!negocios[n].hayStock(idx, enCarrito[idx] + cant)) {
                cout << "Stock insuficiente. Solo hay " << disponible << " unidades." << endl;
            } else if (!orden.agregarItem(p.getNombre(), p.getPrecio(), cant)) {
                cout << "Carrito lleno." << endl;
                opcion = 0;
            } else {
                enCarrito[idx] += cant;
                cout << "Agregado al carrito." << endl;
                if (negocios[n].getControlaStock())
                    cout << "Quedan " << disponible - cant << " unidades disponibles." << endl;
            }
        } else if (opcion != 0) {
            cout << "Producto invalido." << endl;
        }
    }
    return orden.getCantidadItems() > 0;
}

void Sistema::crearOrden() {
    string motivo = motivoBloqueoCrearOrden();
    if (motivo != "") {
        cout << "No se puede crear una orden: " << motivo << "." << endl;
        return;
    }

    int c = elegirCliente();
    if (c == -1) return;
    int n = elegirNegocio(false, true);    // solo negocios que tienen productos
    if (n == -1) return;

    Orden nueva;
    nueva.iniciar(siguienteId, clientes[c].getNombre(), c, negocios[n].getNombre());

    int enCarrito[MAX_PRODUCTOS];
    for (int i = 0; i < MAX_PRODUCTOS; i++) enCarrito[i] = 0;

    if (!llenarCarrito(nueva, n, enCarrito)) {
        cout << "Carrito vacio. Orden cancelada." << endl;
        return;
    }

    double km = negocios[n].getUbicacion().distanciaKm(clientes[c].getUbicacion());
    nueva.definirEntrega(km);

    int m = buscarMensajeroCercano(negocios[n].getUbicacion());
    if (m == -1) { cout << "No hay mensajeros disponibles. Orden cancelada." << endl; return; }
    mensajeros[m].setDisponible(false);
    nueva.asignarMensajero(mensajeros[m].getNombre(), m);

    for (int i = 0; i < negocios[n].getCantidadProductos(); i++) {
        if (enCarrito[i] > 0) negocios[n].descontarStock(i, enCarrito[i]);
    }

    ordenes[cantOrdenes] = nueva;
    cantOrdenes++;
    siguienteId++;
    guardarTransaccion(nueva);
    guardarDatos();

    cout << "ORDEN CREADA:" << endl;
    nueva.mostrar();
}

void Sistema::avanzarEstadoOrden() {
    if (contarOrdenesActivas() == 0) { cout << "No hay ordenes activas." << endl; return; }
    verOrdenesActivas();
    int id = leerEntero("ID de la orden a avanzar (0 para cancelar): ");
    if (id == 0) { cout << "Cancelado." << endl; return; }
    for (int i = 0; i < cantOrdenes; i++) {
        if (ordenes[i].getId() == id) {
            if (!ordenes[i].avanzarEstado()) {
                cout << "Esa orden ya fue entregada." << endl;
                return;
            }
            cout << "Trazado: ";
            ordenes[i].mostrarTrazado();

            if (ordenes[i].getEstado() == ENTREGADO) {
                int m = ordenes[i].getIndiceMensajero();
                int c = ordenes[i].getIndiceCliente();
                mensajeros[m].setDisponible(true);
                mensajeros[m].setUbicacion(clientes[c].getUbicacion());
                cout << "El mensajero " << mensajeros[m].getNombre() << " esta disponible otra vez." << endl;
            }
            guardarTransaccion(ordenes[i]);
            guardarDatos();
            return;
        }
    }
    cout << "No existe una orden con ese ID." << endl;
}

void Sistema::verOrdenes() const {
    if (cantOrdenes == 0) { cout << "No hay ordenes." << endl; return; }
    for (int i = 0; i < cantOrdenes; i++) ordenes[i].mostrar();
}

void Sistema::verOrdenesActivas() const {
    int mostradas = 0;
    for (int i = 0; i < cantOrdenes; i++) {
        if (ordenes[i].estaActiva()) { ordenes[i].mostrar(); mostradas++; }
    }
    if (mostradas == 0) cout << "No hay ordenes activas." << endl;
}

// ==========================================================================
// LISTADOS  (POLIMORFISMO REAL)
// mostrarLista recibe punteros a la clase BASE (Entidad). Al hacer
// lista[i]->mostrar() el programa decide EN EJECUCION si llama a la version
// de Negocio, de Cliente o de Mensajero. La misma funcion sirve para los tres.
// ==========================================================================
static void mostrarLista(const string& titulo, const Entidad* lista[], int cantidad) {
    cout << "=== " << titulo << " (" << cantidad << ") ===" << endl;
    if (cantidad == 0) cout << "(ninguno)" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". ";
        lista[i]->mostrar();           // <- llamada polimorfica
    }
}

void Sistema::listarNegocios() const {
    const Entidad* lista[MAX_NEGOCIOS];
    for (int i = 0; i < cantNegocios; i++) lista[i] = &negocios[i];
    mostrarLista("NEGOCIOS", lista, cantNegocios);
}

void Sistema::listarClientes() const {
    const Entidad* lista[MAX_CLIENTES];
    for (int i = 0; i < cantClientes; i++) lista[i] = &clientes[i];
    mostrarLista("CLIENTES", lista, cantClientes);
}

void Sistema::listarMensajeros() const {
    const Entidad* lista[MAX_MENSAJEROS];
    for (int i = 0; i < cantMensajeros; i++) lista[i] = &mensajeros[i];
    mostrarLista("MENSAJEROS", lista, cantMensajeros);
}

void Sistema::listarEntidades() const {
    listarNegocios();
    listarClientes();
    listarMensajeros();
}

void Sistema::cargarEjemplo() {
    if (!estaVacio()) {
        cout << "Ya hay datos cargados." << endl;
        return;
    }
    negocios[0] = Negocio("Pizzeria Titicaca", "restaurante", Ubicacion(-15.8402, -70.0219));
    negocios[0].agregarProducto("Pizza familiar", 35.0);
    negocios[0].agregarProducto("Gaseosa 1L", 6.0);
    negocios[0].agregarProducto("Pan al ajo", 8.5);
    negocios[1] = Negocio("Farmacia Salud", "farmacia", Ubicacion(-15.8350, -70.0280));
    negocios[1].agregarProducto("Paracetamol", 4.0, 50);
    negocios[1].agregarProducto("Alcohol 250ml", 7.0, 3);
    cantNegocios = 2;

    clientes[0] = Cliente("Ana Quispe", "951000111", Ubicacion(-15.8450, -70.0250));
    clientes[1] = Cliente("Luis Mamani", "951000222", Ubicacion(-15.8300, -70.0150));
    cantClientes = 2;

    mensajeros[0] = Mensajero("Carlos", "Moto", "ABC-123", Ubicacion(-15.8410, -70.0230));
    mensajeros[1] = Mensajero("Rosa", "Bicicleta", "S/P", Ubicacion(-15.8500, -70.0300));
    cantMensajeros = 2;

    guardarDatos();
    cout << "Datos de ejemplo cargados." << endl;
}
