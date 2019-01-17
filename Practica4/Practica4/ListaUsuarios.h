// RAMON CALABOZO
// JAIME PALAZON
#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

#include "Usuario.h"
#include <string>
#include <fstream>

const int  MAX_USU = 6;

typedef struct {
	tUsuario usuario[MAX_USU];
	int cont;
}tListaUsuarios;
//Fucniones
bool cargar(tListaUsuarios & usuarios, std::ifstream & archivo);// Carga la lista de usuarios desde el flujo (ya abierto) archivo
void guardar(const tListaUsuarios & usuarios, std::ofstream & archivo);// Guarda la lista de usuarios en el flujo (ya abierto) archivo
bool buscar(const tListaUsuarios & usuarios, const std::string & idUser, int &pos); /*Dado un identificador de usuario y la lista, devuelve,                                               si dicho identificador existe en la lista, su posici�n y
																					el valor true, y si no existe en la lista, la posici�n que le
																					corresponder�a y el valor false.*/
bool insertar(tListaUsuarios & usuarios, const tUsuario & usuario, int &pos); /*A�ade un usuario en la posici�n de la lista que le corresponde,
																			  si hay sitio para ello y no hay otro usuario con el mismo
																			  identificador. Adem�s devuelve un booleanoindicando si
																			  la operaci�n tuvo �xito o no, y la posici�n donde se
																			  ha insertado*/

bool buscarUsuarioEsperando(const tListaUsuarios & usuarios, tNivel nivel, int & pos); /*Devuelve true y la posici�n del primer usuario
																					   del nivel dado queest� esperando para iniciar una partida.
																					   Si no existe devuelve false.*/
#endif