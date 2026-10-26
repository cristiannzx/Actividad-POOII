#pragma once
#include <string>

std::string aMinusculas(std::string texto);
bool tipoUsaStock(std::string tipo);

std::string leerTexto(std::string mensaje);
int leerEntero(std::string mensaje);
double leerDecimal(std::string mensaje);

// Lee una coordenada GPS y repite la pregunta si queda fuera de [minimo, maximo]
double leerCoordenada(std::string mensaje, double minimo, double maximo);
void pausar();

// Parte una linea en campos separados por ';' (usa arreglo, no vector).
// Devuelve cuantos campos encontro (maximo "maximo").
int dividir(const std::string& linea, std::string campos[], int maximo);
