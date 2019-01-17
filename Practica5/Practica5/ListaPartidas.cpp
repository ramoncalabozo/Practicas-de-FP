//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#include"ListaPartidas.h"

//int main(){
//	tListaPartidas partidas;
//	insertar(partidas);
//
//	ifstream flujo;
//	flujo.open("partidas.txt");
//	cargar(partidas, flujo);
//	if (true){
//		ofstream flujo;
//		flujo.open("partidas.txt");
//		apagar(partidas, flujo);
//	}
//}

void guardar(const tListaPartidas & partidas, ofstream & flujo);  /*Este procedimiento guarda las partidas a través del flujo abierto.*/

void guardar(const tListaPartidas & partidas, ofstream & flujo){
	int contador = 0;
	flujo << partidas.contador << '\n';/*guardo el contador con las partidas*/
	while (contador < MAX_PAR_USU){/*como borro partidas salteadas, no se donde termina la lista
								   con que tendre que recorrerla entera*/
		if (partidas.partida[contador] != NULL){/*si la partida esta vacia no la guardo*/
			guardar(partidas.partida[contador], flujo);
		}
		contador++;
	}
}


bool cargar(tListaPartidas & partidas, ifstream & flujo){
	int contador = 0;
	flujo >> partidas.contador;/*cargo el contador con las partidas*/
	bool ok = true;
	if (partidas.contador > MAX_PAR_USU){ ok = false; }
	while (ok == true && contador < partidas.contador){
		partidas.partida[contador] = new tPartida;
		ok = cargar(partidas.partida[contador], flujo);
		contador++;
	}
	return ok;
}

bool insertar(tListaPartidas & partidas, tPartida *partida){
	bool insertado = false;
	if (partidas.contador < MAX_PAR_USU){
		partidas.partida[partidas.contador] = partida;
		insertado = true;
	}
	else{ insertado = false; }
	return insertado;
}

void apagar(tListaPartidas & partidas, ofstream & flujo){
	guardar(partidas, flujo);
	for (int i = 0; i < partidas.contador; i++) {
		delete partidas.partida[i];
	}
}
