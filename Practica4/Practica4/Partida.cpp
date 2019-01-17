// RAMON CALABOZO
// JAIME PALAZON
#include <iostream>
#include <string>
#include "Partida.h"
#include <sstream>
using namespace std;
//FUNCIONES
string ToString(tFecha fecha, string jugador1, string jugador2);

void nueva(tPartida & partida, const string & jugador1, const string &jugador2){
	tFecha fecha;
	ostringstream flujo;
	fecha = fechaActual();
	flujo << fecha << "_" << jugador1 << "_" << jugador2;
	partida.unico = flujo.str();
	partida.jugador1 = jugador1;
	partida.jugador2 = jugador2;
	partida.estadopartida = EnCurso;
	partida.fecha = fecha;
	partida.ultimaactualizacion = fecha;
	iniciar(partida.estadoconecta4);
}

bool aplicarJugada(tPartida & partida, int col){
	return aplicarJugada(partida.estadoconecta4, col);
}

void abandonar(tPartida & partida){
	partida.estadopartida = Terminada;
	partida.ultimaactualizacion = fechaActual();
}

void guardar(const tPartida & partida, ofstream & archivo){
	archivo << partida.unico << endl;
	archivo << partida.jugador1 << endl;
	archivo << partida.jugador2 << endl;
	archivo << partida.fecha << " " << partida.ultimaactualizacion << endl;
	archivo << partida.estadopartida << endl;
	guardar(partida.estadoconecta4, archivo);
}
bool cargar(tPartida & partida, ifstream & archivo){
	int numero;
	archivo >> partida.unico;
	archivo >> partida.jugador1;
	archivo >> partida.jugador2;
	archivo >> partida.fecha;
	archivo >> partida.ultimaactualizacion;
	archivo >> numero;
	partida.estadopartida = tEstadoPartida(numero); // pone como estado de la partida el numero segun el tipo definido 
	return cargar(partida.estadoconecta4, archivo);
}