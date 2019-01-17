//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO

#include "partida.h"
#include <iostream>
using namespace std;

//int main(){
//	tListaPartidas partidas;
//	juego(partidas);
//
//}

//void juego(tPartida &partida){
/*por decrilo asi, aqui teniamos una mezcla de las demas funciones de partida.cpp, es decir,
era nueva partida, mostar partida y aplicar partida a la vez, luego las quitas y las pusimos
en su lugar*/
//}

void nueva(tPartida *partida, const string & jugador1, const string & jugador2){
	ostringstream unico;
	partida->fecha = fechaActual();
	unico << partida->fecha << "_" << jugador1 << "_" << jugador2;
	partida->único = unico.str();
	partida->jugador1 = jugador1;
	partida->jugador2 = jugador2;
	partida->EstadoPartida = EnCurso;
	iniciar(partida->juego);
}
bool aplicarJugada(tPartida *partida, int col){
	bool resultadoAplicarJugada = false;
	resultadoAplicarJugada = aplicarJugada(partida->juego, col);
	switch (partida->juego.estado)
	{
	case 0:partida->EstadoPartida = EnCurso; break;
	case 1:partida->EstadoPartida = Terminada; break;
	case 2:partida->EstadoPartida = Terminada; break;
	}
	return resultadoAplicarJugada;
}

void guardar(const tPartida *partida, ofstream & flujo){
	flujo << partida->único << '\n';
	flujo << partida->jugador1 << '\n';
	flujo << partida->jugador2 << '\n';
	flujo << partida->fecha << " ";
	flujo << partida->ultimaActualizacion << '\n';
	flujo << partida->EstadoPartida << '\n';
	guardar(partida->juego, flujo);
}
bool cargar(tPartida *partida, ifstream & flujo){
	flujo >> partida->único;
	flujo >> partida->jugador1;
	flujo >> partida->jugador2;
	flujo >> partida->fecha;
	int x;
	int estadoPartida;
	flujo >> x;
	if (x > 1){
		partida->ultimaActualizacion = x;
		flujo >> estadoPartida;
	}
	switch (estadoPartida)
	{
	case 0: partida->EstadoPartida = EnCurso; break;
	case 1: partida->EstadoPartida = Terminada; break;
	default:cout << "no se pudo cargar el estado de la oartida." << '\n';
	}
	cargar(partida->juego, flujo);
	return true;
}

void abandonar(tPartida *partida){
	partida->EstadoPartida = Terminada;
	partida->ultimaActualizacion = fechaActual();
	partida->juego.estado = Ganador;
}