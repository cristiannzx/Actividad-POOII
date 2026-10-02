#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ========================================================
// GOD CLASS: hace TODO en el sistema
// ========================================================
class GestorDeVentas {
private:
    string nombreCliente;
    vector<string> productos;
    vector<double> precios;
    double totalVenta;

public:
    GestorDeVentas(string cliente) {
        nombreCliente = cliente;
        totalVenta = 0;
    }

    // --- Responsabilidad 1: manejar el carrito de compras ---
    void agregarProducto(string nombre, double precio) {
        productos.push_back(nombre);
        precios.push_back(precio);
        totalVenta += precio;
        cout << nombre << " agregado al carrito." << endl;
    }

    void mostrarCarrito() {
        cout << "Carrito de " << nombreCliente << ": ";
        for (string p : productos) cout << p << " ";
        cout << endl;
    }

    // --- Responsabilidad 2: calcular impuestos ---
    double calcularImpuesto() {
        return totalVenta * 0.18;
    }

    // --- Responsabilidad 3: generar factura (texto) ---
    void generarFactura() {
        cout << "===== FACTURA =====" << endl;
        cout << "Cliente: " << nombreCliente << endl;
        for (int i = 0; i < (int)productos.size(); i++) {
            cout << productos[i] << " - S/ " << precios[i] << endl;
        }
        cout << "Impuesto: S/ " << calcularImpuesto() << endl;
        cout << "Total: S/ " << (totalVenta + calcularImpuesto()) << endl;
    }

    // --- Responsabilidad 4: guardar en archivo ---
    void guardarEnArchivo() {
        cout << "[Archivo] Guardando venta de " << nombreCliente
             << " en 'ventas.txt'..." << endl;
    }

    // --- Responsabilidad 5: enviar notificacion ---
    void enviarCorreo() {
        cout << "[Correo] Enviando factura a " << nombreCliente << "..." << endl;
    }

    // --- Responsabilidad 6: validar stock ---
    bool validarStock(string producto, int cantidadDisponible) {
        if (cantidadDisponible > 0) {
            cout << "Stock disponible para " << producto << endl;
            return true;
        }
        cout << "Sin stock para " << producto << endl;
        return false;
    }

    // --- Responsabilidad 7: aplicar descuentos ---
    void aplicarDescuento(double porcentaje) {
        totalVenta = totalVenta - (totalVenta * porcentaje / 100);
        cout << "Descuento aplicado. Nuevo total: S/ " << totalVenta << endl;
    }
};

int main() {

    cout<<"God Class"<<endl;
    GestorDeVentas venta("Carlos");

    venta.validarStock("Mouse", 5);
    venta.agregarProducto("Mouse", 25.0);
    venta.agregarProducto("Teclado", 60.0);
    venta.aplicarDescuento(10);
    venta.generarFactura();
    venta.guardarEnArchivo();
    venta.enviarCorreo();

    return 0;
}
