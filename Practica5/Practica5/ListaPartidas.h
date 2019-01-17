//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO

#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H
#include "partida.h"
#include<iostream>
#include<fstream>
using namespace std;

const int MAX_PAR_USU = 5;


typedef struct{
	tPartida *partida[MAX_PAR_USU];
	int contador;
}tListaPartidas;

bool cargar(tListaPartidas & partidas, ifstream & flujo);  /*Esta función booleana cargará cuando sea true la lista de partidas desde el flujo abierto.*/
bool insertar(tListaPartidas & partidas, tPartida *partida); /*Esta función booleana insertará la partida al final de la lista si hay espacio disponible.Si no puede insertar será false.*/
void apagar(tListaPartidas & partidas, ofstream & flujo);
#endif  //LISTAPARTIDAS_H