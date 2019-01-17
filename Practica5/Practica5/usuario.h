//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#ifndef USUARIO_H
#define USUARIO_H
#include "fecha.h"
#include<string>
#include<iostream>
#include<fstream>

using namespace std;
typedef enum{ gana, pierde, empata }tNRN;
typedef enum{ Principiante, Medio, Experto }tNivel;
typedef enum { Gana, Pierde, Empata }tResultado;
const int NRN = 5;
typedef struct{
	int ganadas;
	int perdidas;
	int empatadas;
}nPartidas;
typedef struct{
	string Nombre;
	string contraseña;
	tNivel nivelJuego;
	int racha;
	bool espera;
	nPartidas NumeroPartidas;
	tFecha fecha;
	string avisos;
}tUsuario;


void iniciar(tUsuario & Usuario, const string & id, const string & pas);  /*Esta función recibe el identificador y la contraseña(ambos de tipo string) e actualiza los campos del usuario(del tipo tUsuario).*/

void guardar(const tUsuario & Usuario, ofstream & archivo);  /*Esta función escribe en el flujo abierto los datos del usuario.*/

bool cargar(tUsuario & Usuario, ifstream & archivo);  /* Esta función booleana lee del flujo abierto los datos de un usuario.*/

bool iniciarSesion(tUsuario & Usuario, const string & clave);  /*Esta función booleana recibe una clave(de tipo string) y un usuario(de tipo tUsuario) y comprueba si la contraseña es correcta o no.*/

void actualizarAvisos(tUsuario & Usuario, const string & aviso);   /*Esta función como su propio nombre indica, actualiza el campo avisos(de tipo string).*/

void limpiarAvisos(tUsuario & Usuario);  /*Esta función pone los avisos a 0, y para ello llama a usuario.*/

bool nuevaPartida(tUsuario & Usuario);  /*Esta función booleana añade en la lista de partidas,la información de acceso a la par(de tipo tParIdEn).*/

void aplicarFinPartida(tUsuario &Usuario, tResultado resultado);  /*Este procedimiento modifica el campo resultado(de tipo tResultado) tras finalizar la partida.*/

#endif  // USUARIO_H