// RAMON CALABOZO
// JAIME PALAZON
#ifndef USUARIO_H
#define USUARIO_H


#include "ListaAccesoPartidas.h"
#include "Fecha.h"
#include <string>
#include <fstream>
#include <sstream>

const int NRN = 5;

typedef enum { PRINCIPIANTE, MEDIO, EXPERTO }tNivel;
typedef enum { Gana, Pierde, empata } tResultado;

typedef struct {
	std::string nombreUsuario;
	std::string contraseñaUsuario;
	tNivel nivelUsuario;
	int rachaUsuario;
	bool espera;
	int ganadasU;
	int empatadasU;
	int perdidasU;
	tFecha fechaConexion;
	std::string avisos;
	tListaAccesoPartidas partidasEnJuego;
}tUsuario;

void iniciar(tUsuario & usuario, const std::string & id, const std::string & pas);
void guardar(const tUsuario & usuario, std::ofstream & archivo);
bool cargar(tUsuario & usuario, std::ifstream & archivo);
bool iniciarSesion(tUsuario & usuario, const std::string & clave);
void actualizarAvisos(tUsuario & usu, const std::string & aviso);
void limpiarAvisos(tUsuario & usu);
bool nuevaPartida(tUsuario & usuario, const tParIdEn & par);
void aplicarFinPartida(tUsuario & usuario, const std::string & idPar, tResultado resultado);









#endif