#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
using namespace std;

// ============================================================
//  CLASES ORIGINALES DE LA APP 6 (sin el main original)
// ============================================================
class Producto {
private:
    int id;
    string nombre;
    double precio;
    int stock;
public:
    Producto(int id, string nombre, double precio, int stock) {
        this->id = id;
        this->nombre = nombre;
        this->precio = precio;
        this->stock = stock;
    }

    // Métodos para acceder a los datos
    int getId() {
        return id;
    }
    string getNombre() {
        return nombre;
    }
    double getPrecio() {
        return precio;
    }
    int getStock() {
        return stock;
    }

    // Controla la modificación del stock
    bool reducirStock(int cantidad) {
        if (cantidad > 0 && cantidad <= stock) {
            stock -= cantidad;
            return true;
        }
        return false;
    }
};

class Carrito {
private:
    vector<Producto> productos;
public:
    // FUNCIONALIDAD 1: Agregar producto
    bool agregarProducto(Producto &producto) {
        if (producto.reducirStock(1)) {
            productos.push_back(producto);
            cout << "Producto agregado: ";
            cout << producto.getNombre() << endl;
            return true;
        }
        cout << "No hay stock disponible." << endl;
        return false;
    }

    // FUNCIONALIDAD 2: Mostrar carrito
    void mostrarCarrito() {
        if (productos.empty()) {
            cout << "El carrito esta vacio." << endl;
            return;
        }
        double total = 0;
        cout << "\n===== CARRITO =====" << endl;
        for (Producto producto : productos) {
            cout << "Producto: " << producto.getNombre() << endl;
            cout << "Precio: S/" << producto.getPrecio() << endl;
            total += producto.getPrecio();
            cout << "------" << endl;
        }
        cout << "TOTAL: S/" << total << endl;
    }

    // FUNCIONALIDAD 3: Realizar compra
    void comprar() {
        if (productos.empty()) {
            cout << "No puedes comprar porque el carrito esta vacio." << endl;
            return;
        }
        double total = 0;
        for (Producto producto : productos) {
            total += producto.getPrecio();
        }
        cout << "\nCompra realizada correctamente." << endl;
        cout << "Total pagado: S/" << total << endl;
        productos.clear();
    }
};

// ============================================================
//  PRUEBAS UNITARIAS DE Producto
// ============================================================
void test_reducirStock_valido() {
    Producto p(1, "Mouse", 80, 10);
    assert(p.reducirStock(3) == true);   // debe aceptar
    assert(p.getStock() == 7);           // 10 - 3 = 7
}

void test_reducirStock_mayor_al_stock() {
    Producto p(1, "Mouse", 80, 10);
    assert(p.reducirStock(11) == false); // no hay suficiente
    assert(p.getStock() == 10);          // el stock NO cambió
}

void test_reducirStock_cantidad_invalida() {
    Producto p(1, "Mouse", 80, 10);
    assert(p.reducirStock(0) == false);
    assert(p.reducirStock(-5) == false); // no permite "agregar" stock con negativos
    assert(p.getStock() == 10);
}

void test_getters() {
    Producto p(7, "Teclado", 120, 8);
    assert(p.getId() == 7);
    assert(p.getNombre() == "Teclado");
    assert(p.getPrecio() == 120);
    assert(p.getStock() == 8);
}

// ============================================================
//  PRUEBAS UNITARIAS DE Carrito
// ============================================================
void test_agregar_con_stock() {
    Producto p(1, "Laptop", 3500, 5);
    Carrito c;
    assert(c.agregarProducto(p) == true);
    assert(p.getStock() == 4);           // bajó 1
}

void test_agregar_sin_stock() {
    Producto p(1, "Laptop", 3500, 1);
    Carrito c;
    assert(c.agregarProducto(p) == true);   // el primero sí entra
    assert(c.agregarProducto(p) == false);  // el segundo no: stock = 0
    assert(p.getStock() == 0);
}

// Como comprar() y mostrarCarrito() imprimen en pantalla,
// "capturamos" lo que imprimen para poder verificarlo
string capturarSalida(Carrito &c, bool comprar) {
    ostringstream buffer;
    streambuf *original = cout.rdbuf(buffer.rdbuf()); // desviamos cout
    if (comprar) c.comprar(); else c.mostrarCarrito();
    cout.rdbuf(original);                             // restauramos cout
    return buffer.str();
}

void test_comprar_carrito_vacio() {
    Carrito c;
    string salida = capturarSalida(c, true);
    assert(salida.find("vacio") != string::npos);
}

void test_comprar_calcula_total_y_vacia() {
    Producto mouse(2, "Mouse", 80, 10);
    Producto teclado(3, "Teclado", 120, 8);
    Carrito c;
    c.agregarProducto(mouse);
    c.agregarProducto(teclado);

    string salida = capturarSalida(c, true);
    assert(salida.find("Total pagado: S/200") != string::npos); // 80 + 120

    string despues = capturarSalida(c, false);                   // mostrarCarrito
    assert(despues.find("vacio") != string::npos);               // quedó vacío
}

// ============================================================
//  MAIN: ejecuta todas las pruebas
// ============================================================
int main() {
    test_reducirStock_valido();
    cout << "OK  test_reducirStock_valido" << endl;

    test_reducirStock_mayor_al_stock();
    cout << "OK  test_reducirStock_mayor_al_stock" << endl;

    test_reducirStock_cantidad_invalida();
    cout << "OK  test_reducirStock_cantidad_invalida" << endl;

    test_getters();
    cout << "OK  test_getters" << endl;

    test_agregar_con_stock();
    cout << "OK  test_agregar_con_stock" << endl;

    test_agregar_sin_stock();
    cout << "OK  test_agregar_sin_stock" << endl;

    test_comprar_carrito_vacio();
    cout << "OK  test_comprar_carrito_vacio" << endl;

    test_comprar_calcula_total_y_vacia();
    cout << "OK  test_comprar_calcula_total_y_vacia" << endl;

    cout << "\nTODAS LAS PRUEBAS PASARON" << endl;
    return 0;
}