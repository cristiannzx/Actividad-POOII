#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

const int MAX_JUGADORES = 7;


class Configuracion {
private:
    int numJugadores;
    int valorGanar;
    string figuras[4];

    string leerArchivo(const string& ruta) const {
        ifstream archivo(ruta.c_str());
        if (!archivo) return "";
        string texto, linea;
        while (getline(archivo, linea)) {
            texto += linea + "\n";
        }
        return texto;
    }

    size_t posicionValor(const string& texto, const string& clave) const {
        string buscada = "\"" + clave + "\"";
        size_t p = texto.find(buscada);
        if (p == string::npos) return string::npos;
        p = texto.find(':', p + buscada.size());
        if (p == string::npos) return string::npos;
        return p + 1;
    }

public:
    Configuracion() {
        // Valores por defecto (si no existe config.txt)
        numJugadores = 1;
        valorGanar = 21;
        figuras[0] = "Corazones";
        figuras[1] = "Diamantes";
        figuras[2] = "Treboles";
        figuras[3] = "Espadas";
    }

    int getNumJugadores() const { return numJugadores; }
    int getValorGanar() const { return valorGanar; }
    string getFigura(int i) const { return figuras[i]; }

    bool cargar(const string& ruta) {
        string texto = leerArchivo(ruta);
        if (texto.empty()) return false;

        // Numero de jugadores (1 a MAX_JUGADORES)
        size_t p = posicionValor(texto, "numero_de_jugadores");
        if (p != string::npos) {
            int n = atoi(texto.c_str() + p);
            if (n >= 1 && n <= MAX_JUGADORES) numJugadores = n;
        }

        // Valor para ganar (10 a 100)
        p = posicionValor(texto, "valor_para_ganar");
        if (p != string::npos) {
            int v = atoi(texto.c_str() + p);
            if (v >= 10 && v <= 100) valorGanar = v;
        }

        // Tipos de figuras (deben ser exactamente 4)
        p = posicionValor(texto, "tipo_de_figuras");
        if (p != string::npos) {
            size_t ini = texto.find('[', p);
            size_t fin = texto.find(']', p);
            if (ini != string::npos && fin != string::npos && ini < fin) {
                string nuevas[4];
                int cont = 0;
                size_t i = ini + 1;
                while (i < fin) {
                    size_t a = texto.find('"', i);
                    if (a == string::npos || a >= fin) break;
                    size_t b = texto.find('"', a + 1);
                    if (b == string::npos || b > fin) break;
                    if (cont < 4) nuevas[cont] = texto.substr(a + 1, b - a - 1);
                    cont++;
                    i = b + 1;
                }
                if (cont == 4) {
                    for (int k = 0; k < 4; k++) figuras[k] = nuevas[k];
                }
            }
        }
        return true;
    }
};

Configuracion config;   // configuracion global del juego

// ---------- CARTA ----------
class Carta {
private:
    int rango;
    int figura;
public:
    Carta() { rango = 1; figura = 0; }
    Carta(int r, int f) {
        if (r < 1 || r > 13) r = 1;
        if (f < 0 || f > 3) f = 0;
        rango = r;
        figura = f;
    }
    int getValor() const {
        if (rango == 1) return 11;
        if (rango >= 10) return 10;
        return rango;
    }
    bool esAs() const { return rango == 1; }
    string toString() const {
        string nombres[14] = {"", "A", "2", "3", "4", "5", "6", "7",
                            "8", "9", "10", "J", "Q", "K"};
        return nombres[rango] + " de " + config.getFigura(figura);
    }
};

// ---------- MAZO ----------
class Mazo {
private:
    Carta cartas[52];
    int siguiente;
public:
    Mazo() { siguiente = 0; }
    void barajar() {
        // Crear las 52 cartas
        int i = 0;
        for (int f = 0; f < 4; f++) {
            for (int r = 1; r <= 13; r++) {
                cartas[i] = Carta(r, f);
                i++;
            }
        }
        // Mezclarlas
        for (int k = 51; k > 0; k--) {
            int j = rand() % (k + 1);
            Carta temp = cartas[k];
            cartas[k] = cartas[j];
            cartas[j] = temp;
        }
        siguiente = 0;
    }
    Carta repartir() {
        if (siguiente >= 52) barajar();
        siguiente++;
        return cartas[siguiente - 1];
    }
};

// ---------- JUGADOR ----------
class Jugador {
private:
    Carta cartas[52];
    int cantidad;
public:
    Jugador() { cantidad = 0; }
    void limpiar() { cantidad = 0; }
    void agregar(Carta c) {
        if (cantidad >= 52) return;       // No se sale del arreglo
        cartas[cantidad] = c;
        cantidad++;
    }
    int total() const {
        int suma = 0;
        int ases = 0;
        for (int i = 0; i < cantidad; i++) {
            suma += cartas[i].getValor();
            if (cartas[i].esAs()) ases++;
        }
        // el As pasa de 11 a 1 si se supera el valor para ganar
        while (suma > config.getValorGanar() && ases > 0) {
            suma -= 10;
            ases--;
        }
        return suma;
    }
    void mostrar() const {
        for (int i = 0; i < cantidad; i++) {
            cout << "   - " << cartas[i].toString() << endl;
        }
        cout << "   Total: " << total() << endl;
    }
};

// ---------- FICHAS ----------
class Fichas {
private:
    int saldo;
    int apuesta;
public:
    Fichas() { saldo = 100; apuesta = 0; }
    int getSaldo() const { return saldo; }
    void setSaldo(int s) { saldo = s; }   // sirve para cargar la partida
    bool apostar(int monto) {
        if (monto <= 0 || monto > saldo) return false;
        apuesta = monto;
        saldo -= monto;
        return true;
    }
    void devolver() { saldo += apuesta; apuesta = 0; }  // cancela la apuesta
    void ganar()  { saldo += apuesta * 2; }  // recupera lo apostado + ganancia
    void empate() { saldo += apuesta; }      // recupera lo apostado
};

// ---------- JUEGO ----------
class Juego {
private:
    Mazo mazo;
    Jugador manos[MAX_JUGADORES];
    Jugador mesa;
    Fichas fichas[MAX_JUGADORES];
    bool activo[MAX_JUGADORES];
    string ultimoResultado[MAX_JUGADORES];
    int n;               // numero de jugadores (viene de config.txt)
    bool salir;

    bool hayActivos() const {
        for (int i = 0; i < n; i++) {
            if (activo[i] && fichas[i].getSaldo() > 0) return true;
        }
        return false;
    }

public:
    Juego() {
        n = config.getNumJugadores();
        salir = false;
        for (int i = 0; i < n; i++) {
            activo[i] = true;
            ultimoResultado[i] = "Ninguna";
        }
    }

    bool estaJugando() const { return !salir && hayActivos(); }

    int getNumJugadores() const { return n; }
    int getSaldo(int i) const { return fichas[i].getSaldo(); }
    string getUltimoResultado(int i) const { return ultimoResultado[i]; }

    // Guarda el saldo y el resultado de la ultima partida de cada jugador
    bool guardar() const {
        ofstream archivo("partida.txt");
        if (!archivo) return false;
        archivo << n << endl;
        for (int i = 0; i < n; i++) {
            archivo << fichas[i].getSaldo() << " " << ultimoResultado[i] << endl;
        }
        return true;
    }

    // Recupera los saldos y resultados desde el archivo
    bool cargar() {
        ifstream archivo("partida.txt");
        int cantidad;
        if (!(archivo >> cantidad)) return false;   // no existe
        if (cantidad != n) {
            cout << "La partida guardada es de " << cantidad
                << " jugadores y config.txt indica " << n << "." << endl;
            return false;
        }
        int saldos[MAX_JUGADORES];
        string resultados[MAX_JUGADORES];
        bool alguno = false;
        for (int i = 0; i < n; i++) {
            if (!(archivo >> saldos[i] >> resultados[i])) return false;
            if (saldos[i] < 0) return false;
            if (saldos[i] > 0) alguno = true;
        }
        if (!alguno) return false;
        for (int i = 0; i < n; i++) {
            fichas[i].setSaldo(saldos[i]);
            ultimoResultado[i] = resultados[i];
            activo[i] = (saldos[i] > 0);
        }
        return true;
    }

    void jugarRonda() {
        int meta = config.getValorGanar();
        bool enRonda[MAX_JUGADORES];
        bool pasado[MAX_JUGADORES];
        for (int i = 0; i < n; i++) {
            enRonda[i] = false;
            pasado[i] = false;
        }

        // 1. Apuestas de cada jugador
        for (int i = 0; i < n; i++) {
            if (!activo[i] || fichas[i].getSaldo() <= 0) continue;
            bool listo = false;
            while (!listo) {
                int monto;
                cout << "\nJugador " << i + 1 << " - Tus fichas: "
                    << fichas[i].getSaldo() << endl;
                cout << "Cuanto quieres apostar? (0 = retirarte, -1 = guardar y salir): ";
                cin >> monto;
                if (cin.fail()) {              // el usuario escribio letras
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Ingresa un numero valido." << endl;
                    continue;
                }
                if (monto == 0) {
                    activo[i] = false;
                    break;
                }
                if (monto == -1) {             // guardar y salir
                    for (int j = 0; j < i; j++) {
                        if (enRonda[j]) fichas[j].devolver();
                    }
                    if (guardar())
                        cout << "Guardando Partida..." << endl;
                    else
                        cout << "No se pudo guardar la partida." << endl;
                    salir = true;
                    return;
                }
                if (!fichas[i].apostar(monto)) {
                    cout << "Apuesta invalida (entre 1 y "
                        << fichas[i].getSaldo() << ")." << endl;
                    continue;
                }
                enRonda[i] = true;
                listo = true;
            }
        }

        bool alguno = false;
        for (int i = 0; i < n; i++) {
            if (enRonda[i]) alguno = true;
        }
        if (!alguno) return;

        // 2. Preparar y repartir
        mazo.barajar();
        mesa.limpiar();
        for (int i = 0; i < n; i++) manos[i].limpiar();
        for (int vuelta = 0; vuelta < 2; vuelta++) {
            for (int i = 0; i < n; i++) {
                if (enRonda[i]) manos[i].agregar(mazo.repartir());
            }
            mesa.agregar(mazo.repartir());
        }

        cout << "\nMano de la mesa:" << endl;
        mesa.mostrar();

        // 3. Turno de cada jugador
        for (int i = 0; i < n; i++) {
            if (!enRonda[i]) continue;
            cout << "\n===== Turno del Jugador " << i + 1 << " =====" << endl;
            cout << "Tu mano:" << endl;
            manos[i].mostrar();

            char opcion;
            while (manos[i].total() < meta) {
                cout << "\nPedir carta (p) o dejar (d)? ";
                cin >> opcion;
                if (opcion == 'p' || opcion == 'P') {
                    manos[i].agregar(mazo.repartir());
                    cout << "\nTu mano:" << endl;
                    manos[i].mostrar();
                } else if (opcion == 'd' || opcion == 'D') {
                    break;
                } else {
                    cout << "Opcion no valida." << endl;
                }
            }
            if (manos[i].total() > meta) {
                cout << "\nJugador " << i + 1 << ", te pasaste. Gana la mesa." << endl;
                pasado[i] = true;
                ultimoResultado[i] = "Perdiste";
            }
        }

        // 4. Turno de la mesa (solo si queda algun jugador sin pasarse)
        bool hayVivos = false;
        for (int i = 0; i < n; i++) {
            if (enRonda[i] && !pasado[i]) hayVivos = true;
        }
        if (hayVivos) {
            cout << "\n--- Turno de la mesa ---" << endl;
            while (mesa.total() <= meta - 5) {
                cout << "La mesa pide carta..." << endl;
                mesa.agregar(mazo.repartir());
                mesa.mostrar();
            }
        }

        // 5. Resultados
        for (int i = 0; i < n; i++) {
            if (!enRonda[i] || pasado[i]) continue;
            cout << "\nJugador " << i + 1 << " -> Tu total: " << manos[i].total()
                << " | Mesa: " << mesa.total() << endl;

            if (mesa.total() > meta || manos[i].total() > mesa.total()) {
                cout << "Gana el jugador " << i + 1 << "!" << endl;
                fichas[i].ganar();
                ultimoResultado[i] = "Ganaste";
            } else if (manos[i].total() < mesa.total()) {
                cout << "Gana la mesa." << endl;
                ultimoResultado[i] = "Perdiste";
            } else {
                cout << "Empate. Recuperas tu apuesta." << endl;
                fichas[i].empate();
                ultimoResultado[i] = "Empate";
            }
        }

        // 6. Jugadores sin fichas quedan fuera
        for (int i = 0; i < n; i++) {
            if (enRonda[i] && fichas[i].getSaldo() == 0) {
                activo[i] = false;
                cout << "\nEl jugador " << i + 1 << " se quedo sin fichas." << endl;
            }
        }
    }

    void mostrarResumen() const {
        cout << endl;
        for (int i = 0; i < n; i++) {
            if (fichas[i].getSaldo() == 0)
                cout << "Jugador " << i + 1 << ": se quedo sin fichas." << endl;
            else
                cout << "Jugador " << i + 1 << ": se retira con "
                    << fichas[i].getSaldo() << " fichas." << endl;
        }
    }
};

int main() {
    srand(time(0));

    // Cargar la configuracion desde config.txt
    bool configOk = config.cargar("config.txt");

    cout << "------Juego " << config.getValorGanar() << "------" << endl;
    if (!configOk) {
        cout << "No se encontro config.txt. Se usan los valores por defecto." << endl;
    }
    cout << "Jugadores: " << config.getNumJugadores() << endl;
    cout << "Figuras: " << config.getFigura(0) << ", " << config.getFigura(1)
        << ", " << config.getFigura(2) << ", " << config.getFigura(3) << endl;
    cout << "Valor para ganar: " << config.getValorGanar() << endl << endl;

    Juego juego;

    // recuperar la partida guardada
    char respuesta;
    cout << "Jugar una partida Guardada(s) o Jugar una nueva(n)?: ";
    cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
        if (juego.cargar()) {
            cout << "Partida cargada." << endl;
            for (int i = 0; i < juego.getNumJugadores(); i++) {
                cout << "Jugador " << i + 1 << ": " << juego.getSaldo(i)
                    << " fichas. Resultado anterior: "
                    << juego.getUltimoResultado(i) << endl;
            }
        } else {
            cout << "No hay partida guardada valida. Se inicia una nueva con 100 fichas por jugador." << endl;
        }
    } else {
        cout << "A cada jugador se le daran 100 fichas." << endl;
    }

    while (juego.estaJugando()) {
        juego.jugarRonda();
    }

    juego.mostrarResumen();
    cout << "Termino el juego" << endl;
    return 0;
}
