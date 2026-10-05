// ============================================================
//  TIENDA ONLINE (versión MAL DISEÑADA a propósito) 
//
//  Funcionalidades:
//    1) Ver catálogo de productos
//    2) Agregar productos al carrito
//    3) Pagar (calcular total y descontar stock)
//============================================================
#include <iostream>
#include <string>
using namespace std;

// ------------------------------------------------------------
// CLASE PRODUCTO
// ❌ VIOLA ENCAPSULAMIENTO: atributos PUBLIC. Cualquiera puede
//    poner un precio negativo y nadie lo impide.
// ------------------------------------------------------------
class Producto {
public:
    string nombre;
    double precio;
    int stock;
};

// ------------------------------------------------------------
// CLASE ITEMCARRITO (un producto dentro del carrito)
// ❌ VIOLA ENCAPSULAMIENTO: datos públicos y sin control.
// ------------------------------------------------------------
class ItemCarrito {
public:
    string nombre;
    double precio;
    int cantidad;
};

// ------------------------------------------------------------
// CLASE TIENDA
// ❌ VIOLA ENCAPSULAMIENTO: los arreglos y el contador son
//    públicos; main los modifica directamente.
// ❌ VIOLA ABSTRACCIÓN: no existe un método "pagar()". Quien
//    use la clase debe conocer sus arreglos y contadores.
// ------------------------------------------------------------
class Tienda {
public:
    Producto catalogo[3];        // 3 productos
    ItemCarrito carrito[10];     // máximo 10 items en el carrito
    int totalItems;              // cuántos items hay en el carrito

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

    // FUNCIONALIDAD 1: Ver catálogo
    void mostrarCatalogo() {
        cout << "\n--- CATALOGO ---\n";
        for (int i = 0; i < 3; i++) {
            cout << i << ") " << catalogo[i].nombre
                 << " | Precio: $" << catalogo[i].precio
                 << " | Stock: " << catalogo[i].stock << endl;
        }
    }

    // FUNCIONALIDAD 2: Agregar al carrito
    // ❌ VIOLA ABSTRACCIÓN: el usuario debe saber el NÚMERO
    //    (índice) interno del producto.
    // ❌ VIOLA ENCAPSULAMIENTO: no valida que el número exista,
    //    ni que haya stock, ni que el carrito no esté lleno.
    void agregarAlCarrito(int indice, int cantidad) {
        carrito[totalItems].nombre = catalogo[indice].nombre;
        carrito[totalItems].precio = catalogo[indice].precio;
        carrito[totalItems].cantidad = cantidad;
        totalItems++;
        cout << "Agregado: " << catalogo[indice].nombre
             << " x" << cantidad << endl;
    }
};

int main() {
    Tienda tienda;
    int opcion;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Ver catalogo\n";
        cout << "2. Agregar al carrito\n";
        cout << "3. Pagar\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            tienda.mostrarCatalogo();
        }
        else if (opcion == 2) {
            int indice, cantidad;
            tienda.mostrarCatalogo();
            cout << "Numero de producto: ";
            cin >> indice;
            cout << "Cantidad: ";
            cin >> cantidad;
            tienda.agregarAlCarrito(indice, cantidad);
        }
        else if (opcion == 3) {
            // FUNCIONALIDAD 3: Pagar
            // ❌ VIOLA ABSTRACCIÓN: main calcula el total y
            //    descuenta el stock "a mano", recorriendo los
            //    arreglos internos. Debería existir tienda.pagar().
            double total = 0;
            for (int i = 0; i < tienda.totalItems; i++) {
                total += tienda.carrito[i].precio * tienda.carrito[i].cantidad;

                for (int j = 0; j < 3; j++) {
                    if (tienda.catalogo[j].nombre == tienda.carrito[i].nombre) {
                        tienda.catalogo[j].stock -= tienda.carrito[i].cantidad;
                    }
                }
            }
            cout << "\nTotal a pagar: $" << total << endl;
            tienda.totalItems = 0;   // "vaciar" el carrito manualmente
        }
    } while (opcion != 0);

    // --------------------------------------------------------
    // DEMOSTRACIÓN DEL PROBLEMA DE ENCAPSULAMIENTO
    // --------------------------------------------------------
    cout << "\n--- DEMO: datos corrompidos ---\n";
    tienda.catalogo[0].precio = -999;   // ¡precio negativo!
    tienda.catalogo[0].stock = -50;     // ¡stock negativo!
    tienda.mostrarCatalogo();

    return 0;
}