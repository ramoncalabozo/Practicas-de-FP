// RAMON CALABOZO
// JAIME PALAZON

#ifndef GESTOR_H
#define GESTOR_H

#include "ListaPartidas.h"
#include "ListaUsuarios.h"

typedef struct{
	tListaPartidas partidasSistema;
	tListaUsuarios usuariosSistema;
	int contUsu;
	int contListaPartida;

}tGestor;

bool iniciar(tGestor & gestor, const std::string & ficheroUsu, const std::string & ficheroPar);
void cerrar(tGestor & gestor, const std::string & ficheroUsu, const std::string & ficheroPar);
//Funciones del menú registro del main:
bool iniciarSesion(tGestor & gestor, const std::string & idUsu, const std::string & clave);
bool crearCuenta(tGestor & gestor, const std::string & idUsu, const std::string & clave);
bool tieneAvisos(const tGestor & gestor, std::string & aviso);
void limpiarAvisos(tGestor & gestor);
std::string resumenActividad(const tGestor & gestor);
//Funciones del menú usuario del main:
void ordenar_Fecha(tGestor & gestor);
void ordenar_Turno(tGestor & gestor);
int partidasUsuario(const tGestor & gestor);
std::string cabecera(const tGestor & gestor, int posEnCurso);
bool nuevaPartida(tGestor & gestor);
void apuntaPartida(tGestor & gestor, int posParEnCurso);
//Funciones del menú partida del main:
void mostrarPartida(const tGestor & gestor);
//bool esSuTurno(const tGestor & gestor);
void jugarPartida(tGestor & gestor, int col);
void abandonarPartida(tGestor & gestor);
bool esSuTurno2(tGestor, int posEnCurso);


#endif