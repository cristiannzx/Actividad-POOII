#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Cada clase hace UNA sola cosa

class Carrito {
private:
    vector<string> productos;
    vector<double> precios;
    double total;
public:
    Carrito() { total = 0; }
    void agregarProducto(string nombre, double precio) {
        productos.push_back(nombre);
        precios.push_back(precio);
        total += precio;
        cout << nombre << " agregado al carrito." << endl;
    }
    double getTotal() const { return total; }
    vector<string> getProductos() const { return productos; }
    vector<double> getPrecios() const { return precios; }
};

class CalculadoraImpuestos {
public:
    double calcular(double monto) {
        return monto * 0.18;
    }
};

class GeneradorFactura {
public:
    void generar(string cliente, Carrito& carrito, double impuesto) {
        cout << "===== FACTURA =====" << endl;
        cout << "Cliente: " << cliente << endl;
        cout << "Total: S/ " << (carrito.getTotal() + impuesto) << endl;
    }
};

class AlmacenamientoVentas {
public:
    void guardar(string cliente) {
        cout << "[Archivo] Guardando venta de " << cliente << "..." << endl;
    }
};

class NotificadorCorreo {
public:
    void enviar(string cliente) {
        cout << "[Correo] Enviando factura a " << cliente << "..." << endl;
    }
};

int main() {
    cout<<"-----Refactoring------"<<endl;
    string cliente = "Carlos";
    Carrito carrito;
    CalculadoraImpuestos impuestos;
    GeneradorFactura factura;
    AlmacenamientoVentas almacen;
    NotificadorCorreo correo;

    carrito.agregarProducto("Mouse", 25.0);
    carrito.agregarProducto("Teclado", 60.0);

    double impuesto = impuestos.calcular(carrito.getTotal());
    factura.generar(cliente, carrito, impuesto);
    almacen.guardar(cliente);
    correo.enviar(cliente);

    return 0;
}
