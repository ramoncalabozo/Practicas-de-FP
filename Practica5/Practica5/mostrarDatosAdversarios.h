//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO 
#ifndef mostrarDatosAdversarios_H
#define mostrarDatosAdversarios_H
#include "ListaUsuarios.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_ADVERSARIOS = 10;

typedef struct{
	string nombreAdversario;
	int ganadas;
	int perdidas;
	int empatadas;
}tAdversario;

typedef struct{
	tAdversario *Adversario[MAX_ADVERSARIOS];
	int contador;
}tAdversarios;

typedef struct{
	tAdversarios *Adversarios;/*esta ordenada igual que usuarios, es decir, el usuario 1 tiene su lista en la posion 1*/
	int *posUsuario;/*un puntero a un array que guarda las posiciones en la lista usuarios*/
	int contador;
	/*tamaño va con la cantidad de usuarios*/
}tListaAdversarios;

void mostrarDatosAdversarios(tAdversarios &Adversarios, int &pos);

void cargarListaAdversarios(tListaAdversarios &ListaAdversarios, int &tamañoLista, ifstream & archivo);

void apagarListaAdversarios(const tListaAdversarios &ListaAdversarios, ofstream & archivo);

//void actualizarListaAdversarios(tListaAdversarios & ListaAdversarios, const string &nombreAdversario, const tResultado &resultado, int & pos);

void nuevoAdversario(tListaAdversarios &ListaAdversarios, int &pos);
#endif  // mostrarDatosAdversarios_H