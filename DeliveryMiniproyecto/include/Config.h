#pragma once
#include <string>

const int MAX_NEGOCIOS   = 5;
const int MAX_CLIENTES   = 20;
const int MAX_MENSAJEROS = 10;
const int MAX_ORDENES    = 50;
const int MAX_PRODUCTOS  = 20;
const int MAX_ITEMS      = 10;

const double TARIFA_BASE   = 3.0;
const double TARIFA_POR_KM = 1.5;
// ordenes.txt = bitacora de transacciones (una linea por cada evento de una orden)
const std::string ARCHIVO       = "ordenes.txt";
// datos.txt   = foto del sistema (negocios, clientes, mensajeros, ordenes) para no perder nada al cerrar
const std::string ARCHIVO_DATOS = "datos.txt";
