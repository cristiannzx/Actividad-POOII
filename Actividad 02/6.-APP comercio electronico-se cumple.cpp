#include <iostream>
#include <vector>
#include <string>
using namespace std;

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

int main() {
    // Productos disponibles
    Producto producto1(1, "Laptop", 3500, 5);
    Producto producto2(2, "Mouse", 80, 10);
    Producto producto3(3, "Teclado", 120, 8);
    
    // Crear carrito
    Carrito carrito;
    
    // Agregar productos
    carrito.agregarProducto(producto1);
    carrito.agregarProducto(producto2);
    
    // Mostrar carrito
    carrito.mostrarCarrito();
    
    // Mostrar stock restante
    cout << "Stock restante de Laptop: ";
    cout << producto1.getStock() << endl;
    cout << "Stock restante de Mouse: " << producto2.getStock() << endl;
    
    // Comprar
    carrito.comprar();
    
    // Mostrar carrito después de comprar
    carrito.mostrarCarrito();
    
    return 0;
}