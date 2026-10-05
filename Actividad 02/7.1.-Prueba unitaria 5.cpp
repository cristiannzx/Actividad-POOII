#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// ============================================================
//  CLASES ORIGINALES DE LA APP 5 (sin el main original)
// ============================================================
class Producto {
public:
    string nombre;
    double precio;
    int stock;
};

class ItemCarrito {
public:
    string nombre;
    double precio;
    int cantidad;
};

class Tienda {
public:
    Producto catalogo[3];
    ItemCarrito carrito[10];
    int totalItems;

    Tienda() {
        totalItems = 0;

        catalogo[0].nombre = "Laptop";
        catalogo[0].precio = 2500.0;
        catalogo[0].stock = 5;

        catalogo[1].nombre = "Mouse";
        catalogo[1].precio = 50.0;
        catalogo[1].stock = 20;

        catalogo[2].nombre = "Teclado";
        catalogo[2].precio = 120.0;
        catalogo[2].stock = 10;
    }

    void mostrarCatalogo() {
        cout << "\n--- CATALOGO ---\n";
        for (int i = 0; i < 3; i++) {
            cout << i << ") " << catalogo[i].nombre
                 << " | Precio: $" << catalogo[i].precio
                 << " | Stock: " << catalogo[i].stock << endl;
        }
    }

    void agregarAlCarrito(int indice, int cantidad) {
        carrito[totalItems].nombre = catalogo[indice].nombre;
        carrito[totalItems].precio = catalogo[indice].precio;
        carrito[totalItems].cantidad = cantidad;
        totalItems++;
        cout << "Agregado: " << catalogo[indice].nombre
             << " x" << cantidad << endl;
    }
};

// ============================================================
//  MINI SISTEMA DE PRUEBAS (cuenta aciertos y fallos)
// ============================================================
int pasaron = 0;
int fallaron = 0;

void verificar(const string &nombre, bool condicion, const string &motivo) {
    if (condicion) {
        pasaron++;
        cout << "[PASA  ] " << nombre << endl;
    } else {
        fallaron++;
        cout << "[FALLA ] " << nombre << "\n           -> " << motivo << endl;
    }
}

// Silencia cout mientras se ejecuta una acción (para no ensuciar la salida)
class SilenciarCout {
    ostringstream buffer;
    streambuf *original;
public:
    SilenciarCout()  { original = cout.rdbuf(buffer.rdbuf()); }
    ~SilenciarCout() { cout.rdbuf(original); }
    string texto()   { return buffer.str(); }
};

// ============================================================
//  PRUEBAS
// ============================================================

// P1: lo que SÍ funciona: mostrar el catálogo
void test_mostrarCatalogo() {
    Tienda t;
    string salida;
    {
        SilenciarCout s;
        t.mostrarCatalogo();
        salida = s.texto();
    }
    verificar("P1 mostrarCatalogo muestra los productos",
              salida.find("Laptop") != string::npos &&
              salida.find("Mouse") != string::npos &&
              salida.find("Teclado") != string::npos,
              "No aparecieron los productos");
}

// P2: caso normal: agregar 2 laptops (funciona, pero solo se puede
// comprobar mirando los atributos internos, porque todo es public)
void test_agregar_valido() {
    Tienda t;
    { SilenciarCout s; t.agregarAlCarrito(0, 2); }
    verificar("P2 agregar 2 Laptops (caso normal)",
              t.totalItems == 1 &&
              t.carrito[0].nombre == "Laptop" &&
              t.carrito[0].cantidad == 2,
              "El item no quedó bien guardado");
}

// P3: la Laptop tiene stock 5. Pedir 100 debería RECHAZARSE.
void test_cantidad_mayor_al_stock() {
    Tienda t;
    { SilenciarCout s; t.agregarAlCarrito(0, 100); }
    verificar("P3 rechazar cantidad (100) mayor al stock (5)",
              t.totalItems == 0,
              "Aceptó 100 laptops con stock 5 (totalItems = " +
              to_string(t.totalItems) + ")");
}

// P4: cantidad negativa debería RECHAZARSE.
void test_cantidad_negativa() {
    Tienda t;
    { SilenciarCout s; t.agregarAlCarrito(1, -3); }
    verificar("P4 rechazar cantidad negativa (-3)",
              t.totalItems == 0,
              "Aceptó cantidad negativa (el total a pagar saldría negativo)");
}

// P5: cantidad cero debería RECHAZARSE.
void test_cantidad_cero() {
    Tienda t;
    { SilenciarCout s; t.agregarAlCarrito(2, 0); }
    verificar("P5 rechazar cantidad cero",
              t.totalItems == 0,
              "Aceptó cantidad 0 y la guardó en el carrito");
}

// P6: nadie debería poder poner un precio negativo.
void test_precio_negativo() {
    Tienda t;
    t.catalogo[0].precio = -999;   // permitido porque es public
    verificar("P6 impedir precio negativo",
              t.catalogo[0].precio >= 0,
              "El precio quedó en " + to_string(t.catalogo[0].precio));
}

// P7: nadie debería poder poner un stock negativo.
void test_stock_negativo() {
    Tienda t;
    t.catalogo[0].stock = -50;     // permitido porque es public
    verificar("P7 impedir stock negativo",
              t.catalogo[0].stock >= 0,
              "El stock quedó en " + to_string(t.catalogo[0].stock));
}

// P8: probar "pagar". NO EXISTE tienda.pagar(), la lógica está en main().
// Lo único posible es COPIAR el código del main a una función de prueba.
// Esta prueba pasa, pero prueba una COPIA, no el código real.
double pagar_copiado_del_main(Tienda &tienda) {
    double total = 0;
    for (int i = 0; i < tienda.totalItems; i++) {
        total += tienda.carrito[i].precio * tienda.carrito[i].cantidad;
        for (int j = 0; j < 3; j++) {
            if (tienda.catalogo[j].nombre == tienda.carrito[i].nombre) {
                tienda.catalogo[j].stock -= tienda.carrito[i].cantidad;
            }
        }
    }
    tienda.totalItems = 0;
    return total;
}

void test_pagar_copia() {
    Tienda t;
    { SilenciarCout s; t.agregarAlCarrito(1, 2); }   // 2 Mouse = 100
    double total = pagar_copiado_del_main(t);
    verificar("P8 pagar (SOLO una copia del codigo de main)",
              total == 100 && t.catalogo[1].stock == 18,
              "El total o el stock no coinciden");
}

// ============================================================
//  PRUEBAS QUE NO SE PUEDEN EJECUTAR (comportamiento indefinido)
// ============================================================
//  NO se ejecutan porque podrían cerrar el programa o dar
//  resultados distintos en cada ejecución:
//
//    Tienda t;
//    t.agregarAlCarrito(7, 1);    // indice 7: NO existe (solo 0,1,2)
//    t.agregarAlCarrito(-1, 1);   // indice negativo
//
//    for (int i = 0; i < 11; i++) // el carrito solo tiene 10 espacios
//        t.agregarAlCarrito(0, 1);
//
//  Una prueba que puede pasar, fallar o hacer caer el programa
//  segun el momento NO es una prueba confiable.
// ============================================================

int main() {
    cout << "===== PRUEBAS UNITARIAS - APP 5 =====\n" << endl;

    test_mostrarCatalogo();
    test_agregar_valido();
    test_cantidad_mayor_al_stock();
    test_cantidad_negativa();
    test_cantidad_cero();
    test_precio_negativo();
    test_stock_negativo();
    test_pagar_copia();

    cout << "\n===== RESUMEN =====" << endl;
    cout << "Pasaron:  " << pasaron << endl;
    cout << "Fallaron: " << fallaron << endl;

    return 0;
}