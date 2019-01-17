//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#ifndef LISTAACCESOPARTIDAS_H
#define LISTAACCESOPARTIDAS_H
#include "partida.h" /*ya que si no no se puede crear el array de punteros*/
#include <iostream>
#include <string>
using namespace std;

const int MAX_PAR_US = 10;
typedef struct{
	string IdentificadorPartida;
	tPartida *puntPartida; /*puntero que indica donse se encuentra la partida*/
}tParIdEn;
typedef struct{
	tParIdEn ParIdEn[MAX_PAR_US];
	int contador;
}tListaAccesoPartidas;


void iniciar(tListaAccesoPartidas & lista);   /*Esta función llama a lista que es del tipo tListaAccesoPartidas y la pone a vacía.*/
bool llena(const tListaAccesoPartidas & lista);  /*Esta función booleana comprueba si la lista está o no llena.*/
bool insertar(tListaAccesoPartidas & lista, const tParIdEn & par);  /*Esta función booleana inserta el elemento(par) al final de la lista,si ésta no está llena,devolviendo un true.En caso contrario devolverá false.*/
bool eliminar(tListaAccesoPartidas & lista, const int & pos);  /*Busca la posición del identificador de partida y si lo encuentra lo elimina devolviendo un  true.*/
void ordenar_Fecha(tListaAccesoPartidas & lista);
void ordenar_Turno(tListaAccesoPartidas & listaconst, const string &nombreUsuario);
bool buscar(tListaAccesoPartidas const& lista, string const& id, int &pos);
#endif  // LISTAACCESOPARTIDAS_H

