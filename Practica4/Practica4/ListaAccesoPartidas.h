// RAMON CALABOZO
// JAIME PALAZON
#ifndef LISTAACCESOPARTIDAS_H
#define LISTAACCESOPARTIDAS_H

#include "Conecta4.h"
#include "Fecha.h"
#include <string>
//CONSTANTES
const int MAX_PAR_US = 3;

// DECLARACION DE TIPOS
typedef struct {
	int Enlace;//indice del elemento en la lista de partidas
	std::string Identificador;//Identificador de la partida+
}tParIdEn;

typedef tParIdEn TaccesoPartidas[MAX_PAR_US];

typedef struct {
	TaccesoPartidas accesopartidas;
	int contador;
}tListaAccesoPartidas;

//FUNCIONES
void iniciar(tListaAccesoPartidas & lista);//incicia la lisga vacía
bool llena(const tListaAccesoPartidas & lista);//Comprueba si la lista esta vacía
bool insertar(tListaAccesoPartidas & lista, tParIdEn par);  /*Dado un
															//elemento, si la lista no está llena lo inserta al final de la lista
															//y devuelve true. En otro caso devuelve false.
															*/
bool eliminar(tListaAccesoPartidas & lista, const std::string & identificador);
#endif