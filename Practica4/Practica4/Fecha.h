// RAMON CALABOZO
// JAIME PALAZON
// Ya funciona
#ifndef FECHA_H
#define FECHA_H
#include <ctime>
#include <sstream>
#include "Conecta4.h"
// Declaracion del tipo time tFecha
typedef time_t tFecha;

// Declaracion de Funciones

tFecha fechaActual(); // Funcion que sirve para consultar la fecha actual
std::string stringFecha(tFecha fecha, bool hora); // Para mostrar la fecha
#endif