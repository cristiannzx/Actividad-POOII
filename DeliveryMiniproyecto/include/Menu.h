#pragma once
#include <string>

const int MAX_OPCIONES_MENU = 12;

class Menu {
private:
    std::string titulo;
    std::string estado;                         // linea de resumen bajo el titulo
    std::string textos[MAX_OPCIONES_MENU];
    std::string motivos[MAX_OPCIONES_MENU];     // por que esta bloqueada
    bool habilitadas[MAX_OPCIONES_MENU];
    int codigos[MAX_OPCIONES_MENU];
    int cantidad;

    void mostrar(const std::string& textoSalir) const;

public:
    Menu(std::string titulo, std::string estado = "");

    void agregarOpcion(int codigo, std::string texto,
                       bool habilitada = true, std::string motivo = "");

    // Muestra el menu y repite hasta que elijan algo valido.
    // Devuelve el codigo de la opcion elegida, o 0 si eligen salir/volver.
    int elegir(std::string textoSalir);
};
