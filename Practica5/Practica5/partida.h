//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#ifndef PARTIDA_H
#define PARTIDA_H
#include "Conecta4.h"
#include "fecha.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip> 
using namespace std;

typedef enum  tEstadoPartida { EnCurso, Terminada };

typedef struct{
	string único;
	string jugador1;
	string jugador2;
	tFecha fecha;
	tFecha ultimaActualizacion;
	tEstadoPartida EstadoPartida;
	tConecta4 juego;
} tPartida;

//void juego(tPartida *partida);  /* Esta función es un procedimiento que llama a la partida y permite jugar.*/
void nueva(tPartida *partida, const string & jugador1, const string &jugador2);  /*Pide los identificadores de los jugadores y rellena la nueva partida(a la que llama la función) con los mismos.*/
bool aplicarJugada(tPartida *partida, int col);  /*Esta función booleana tiene un col de tipo entero que hará que se actualicen los campos de la partida siempre y cuando sea true.*/
void guardar(const tPartida *partida, ofstream & flujo);  /*Esta función se encarga de guardar la partida escribiendo los datos a través del flujo de salida.*/
bool cargar(tPartida *partida, ifstream & flujo);   /*Esta función booleana cargará la partida solo cuando sea true mediante la lectura de los datos a través del flujo de entrada.*/
void abandonar(tPartida *partida);  /*Esta función actualiza la fecha de la partida y cambia el estado de la misma a terminada.*/
#endif  // PARTIDA_H