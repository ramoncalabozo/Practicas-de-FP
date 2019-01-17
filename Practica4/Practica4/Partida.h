// RAMON CALABOZO
// JAIME PALAZON
//Declaracion de Bibliotecas   
#ifndef PARTIDA_H
#define PARTIDA_H
#include <string>
#include "Fecha.h"
#include "Conecta4.h"
#include <fstream>
typedef enum { EnCurso, Terminada }tEstadoPartida;
typedef struct {
	std::string unico;
	std::string jugador1;
	std::string jugador2;
	tFecha fecha;
	tFecha ultimaactualizacion;
	tEstadoPartida estadopartida;
	tConecta4 estadoconecta4;
}tPartida;
//Declaracion de funciones
void nueva(tPartida & partida, const std::string & jugador1, const std::string & jugador2);//Recibe los identificadores de los adversarios y devuelve una partida con sus datos rellenos
bool aplicarJugada(tPartida & partida, int col);//Aplica la jugadoa col al juego,y si se puede realizar , devuelve true y actualiza los demas campos de la partida
void abandonar(tPartida & partida);//Modifica el estado de la partida a Terminada,y la fecha de la última actualización
void guardar(const tPartida & partida, std::ofstream & archivo);// Dado un flujo dearchivo de salida (ya abierto), escribe en el flujo los datos de la partida 
bool cargar(tPartida & partida, std::ifstream & archivo);// Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a una partida en partida.Devuelve false si la partida no se ha podido cargar correctamente.
#endif