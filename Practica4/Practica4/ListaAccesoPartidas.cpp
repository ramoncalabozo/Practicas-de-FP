// RAMON CALABOZO
// JAIME PALAZON
#include <iostream>
#include "ListaAccesoPartidas.h"
using namespace std;
//FUNCIONES
void iniciar(tListaAccesoPartidas & lista){
	lista.contador = 0;
}

bool llena(const tListaAccesoPartidas & lista){
	bool llena = false;
	if (lista.contador == MAX_PAR_US){
		llena = true;
	}
	return llena;
}
bool insertar(tListaAccesoPartidas & lista, tParIdEn par){
	bool insertar = false;
	if (llena(lista) == false){
		lista.contador = lista.contador + 1;
		lista.accesopartidas[lista.contador] = par;
	}
	return insertar;
}

bool eliminar(tListaAccesoPartidas & lista, const string & identificador){
	int i = 0;
	bool encontrado = false;
	int j;
	while (i < MAX_PAR_US && !encontrado){
		j = i;
		if (lista.accesopartidas[i].Identificador == identificador){
			while (j < lista.contador - 1){
				lista.accesopartidas[j] = lista.accesopartidas[j + 1];
				j++;
			}

			lista.contador = lista.contador--;
			encontrado = true;
		}
		i++;
	}
	return encontrado;
}