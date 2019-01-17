//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#include"ListaAccesoPartidas.h"

//int main(){
//	tListaAccesoPartidas lista;
//	tParIdEn par;
//	iniciar(lista);
//	insertar(lista,par);
//}

bool comprobarTurnoUsuario(const tListaAccesoPartidas & lista, int & pos, const string &nombreUsuario);

void iniciar(tListaAccesoPartidas & lista){
	lista.contador = 0;
}

bool llena(const tListaAccesoPartidas & lista){
	return lista.contador == MAX_PAR_US;
}

bool insertar(tListaAccesoPartidas & lista, const tParIdEn & par){
	if (llena(lista) == false){
		lista.ParIdEn[lista.contador] = par;
		lista.contador++;
		return true;
	}
	else
	{
		return false;
	}
}

bool eliminar(tListaAccesoPartidas & lista, const int & pos){
	if (pos >= 0 && pos<MAX_PAR_US)
	{
		if (pos < lista.contador){

			for (int a = pos; a < lista.contador; a++)
			{
				lista.ParIdEn[a] = lista.ParIdEn[a + 1];
			}
		}
		lista.contador--;
		return true;
	}
	else { return false; }
}

void ordenar_Fecha(tListaAccesoPartidas & lista){
	tPartida *partida = NULL;; /*es una puntero a partida temporal para cambiarlos*/
	int i = 0;
	bool inter = true;
	while ((i < lista.contador - 1) && inter) {
		inter = false;
		for (int j = lista.contador - 1; j > i; j--) {
			if (lista.ParIdEn[j].puntPartida->ultimaActualizacion < lista.ParIdEn[j - 1].puntPartida->ultimaActualizacion){
				partida = lista.ParIdEn[j].puntPartida;
				lista.ParIdEn[j].puntPartida = lista.ParIdEn[j - 1].puntPartida;
				lista.ParIdEn[j - 1].puntPartida = partida;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}

void ordenar_Turno(tListaAccesoPartidas & lista, const string &nombreUsuario){
	tPartida *partida = NULL;; /*es una puntero a partida temporal para cambiarlos*/
	int i = 0;
	bool inter = true;
	bool cambio = false;/*para saber si cambiar o no*/
	while ((i < lista.contador - 1) && inter) {
		inter = false;
		for (int j = lista.contador - 1; j > i; j--) {
			if (comprobarTurnoUsuario(lista, j, nombreUsuario) == true){
				int t = j - 1;
				cambio = true;
				if (comprobarTurnoUsuario(lista, t, nombreUsuario) == true){
					if (lista.ParIdEn[j].puntPartida->ultimaActualizacion < lista.ParIdEn[j - 1].puntPartida->ultimaActualizacion){
						cambio = true;
					}
					else{ cambio = false; }
				}
				if (cambio == true)
					partida = lista.ParIdEn[j].puntPartida;
				lista.ParIdEn[j].puntPartida = lista.ParIdEn[j - 1].puntPartida;
				lista.ParIdEn[j - 1].puntPartida = partida;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}
bool comprobarTurnoUsuario(const tListaAccesoPartidas & lista, int & pos, const string &nombreUsuario){
	bool LeTocaJugar = false;

	/*comprobamos si al esuario le toca o no mover ficha*/
	switch (lista.ParIdEn[pos].puntPartida->juego.turno)
	{
	case 12:if (lista.ParIdEn[pos].puntPartida->jugador1 == nombreUsuario){ LeTocaJugar = true; }break;
	case 10:if (lista.ParIdEn[pos].puntPartida->jugador2 == nombreUsuario){ LeTocaJugar = true; }break;
	case 0: break;
	}

	return LeTocaJugar;

}/*esta funcion la hice para ordenar por turno, como lo que hace es comrpobar si es el turno del usuario la copio igual el esSuTurno*/

bool buscar(tListaAccesoPartidas const& lista, string const& id, int &pos){
	bool encontrado = false;
	if (id == lista.ParIdEn[pos].IdentificadorPartida){
		encontrado = true;
	}
	else{
		pos++;
		buscar(lista, id, pos);
	}
	return encontrado;
}