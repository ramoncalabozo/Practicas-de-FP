//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  
#ifndef ListaUsuarios_H
#define ListaUsuarios_H

#include "usuario.h"
#include <iostream>

using namespace std;


typedef struct{
	tUsuario *Usuario;
	int contador;
	int capacidad;
}tListaUsuarios;


void apagar(tListaUsuarios & usuarios, ofstream & archivo);

bool cargar(tListaUsuarios & usuarios, ifstream & archivo);   /*Esta función booleana carga desde el flujo abierto la lista de usuarios.*/

bool buscar(const tListaUsuarios & usuarios, const string & idUser, int &pos);   /*Esta función booleana devolverá true cuando el identificador(de tipo string) se encuentre en la lista(de tipo tListaUsuarios), diciéndonos su posición(de tipo entero).
																				 En caso de que devuelva false nos indicará la posición en la que tendría que estar.*/

bool insertar(tListaUsuarios & usuarios, const tUsuario & Usuario);  /*Esta función booleana devolverá true,si no hay un usuario con el mismo identificador,pudiendo así,insertarlo donde le correspond alfabeticamente.*/

bool buscarUsuarioEsperando(const tListaUsuarios & usuarios, tNivel nivel, int & pos, int & Usuariosesión); /* Esta función booleana devuelve la posición del primer usuario del nivel(de tipo tNivel) siempre que sea true.*/

#endif  // ListaUsuarios_H