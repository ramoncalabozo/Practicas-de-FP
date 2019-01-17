// RAMON CALABOZO
// JAIME PALAZON
#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H
#include "Partida.h"
#include "Conecta4.h"
#include "Fecha.h"
//CONSTANTES
const int MAX_PAR_USU = 6;
// DECLARACIÓN DE TIPOS 
typedef tPartida tLista[MAX_PAR_USU];
typedef struct{
	tLista partida;
	int contador;
}tListaPartidas;

// FUNCIONES
void inicializar(tListaPartidas &partidas);// No si si hay que hacer algo con esto

void guardar(const tListaPartidas  & partidas, std::ofstream & archivo);//Guarda la lista de partidas en el flujo (ya abierto) archivo

bool cargar(tListaPartidas & partidas, std::ifstream & archivo);/*Carga la lista departidas desde el flujo (ya abierto) archivo.
																Devuelve false si la lista no se ha podidocargar correctamente.
																*/
bool insertar(tListaPartidas & partidas, const tPartida & partida); /* Dada una partida, si hay espacio en la lista, la añade al final de la
																	lista y devuelve true. Si no se ha podido insertar devuelve false.
																	*/
#endif