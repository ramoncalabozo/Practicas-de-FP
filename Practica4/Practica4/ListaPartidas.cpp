// RAMON CALABOZO
// JAIME PALAZON
#include <iostream>
#include "ListaPartidas.h"
#include <iostream>
#include <fstream>
using namespace std;

void guardar(const tListaPartidas & partidas, ofstream & archivo){
	archivo << partidas.contador << endl;
	for (int i = 0; i<partidas.contador; i++){
		guardar(partidas.partida[i], archivo);
	}
}


bool cargar(tListaPartidas & partidas, std::ifstream & archivo){
	bool ok = true;
	bool ok2 = true;
	int i = 0;
	int j;
	inicializar(partidas);
	archivo >> partidas.contador;
	while (i < partidas.contador && ok2 == true){
		ok2 = cargar(partidas.partida[i], archivo);
		j = i;
		i++;
	}
	if (ok2 == false){
		ok = true;
	}
	return ok;
}

bool insertar(tListaPartidas & partidas, const tPartida & partida){
	bool insertar = true;
	if (partidas.contador < MAX_PAR_USU){
		partidas.partida[partidas.contador] = partida;
		partidas.contador++;
	}
	else {
		insertar = false;
	}
	return insertar;
}

void inicializar(tListaPartidas & partidas){
	partidas.contador = 0;
}