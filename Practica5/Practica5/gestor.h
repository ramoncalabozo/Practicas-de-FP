//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#ifndef GESTOR_H
#define GESTOR_H

#include"ListaPartidas.h"
#include"ListaUsuarios.h"
#include"ListaAccesoPartidas.h"
#include "mostrarDatosAdversarios.h"
#include<string>
#include<iostream>
#include<fstream>
using namespace std;



typedef struct{
	tListaPartidas partidas;
	tListaUsuarios usuarios;
	tListaAccesoPartidas ListaAccesoPartidas;
	int Usuariosesión;
	tPartida *puntPartidaSeleccionada;
	tListaAdversarios ListaAdversarios;
}tGestor;


//Estos subprogramas se utilizan en mainP4.
bool iniciar(tGestor & gestor, const string & ficheroUsu, const string & ficheroPar);  /*Este subprograma abre los dos archivos(de tipo string) y carga la lista de partidas y de usuarios(de tipo t..).*/
void cerrar(tGestor & gestor, const string & ficheroUsu, const string & ficheroPar);   /*Este subprograma guarda las listas de usuarios y de partidas en su correspondiente archivo.*/

void generarAccesos(tGestor & gestor);/*ya que se necesita para la cabecera*/

//Estas funciones se usan en el menú registro del main.
bool iniciarSesion(tGestor & gestor, const string & idUsu, const string & clave);  /*Esta función booleana recibe el identificador y la clave(ambos de tipo string) ydevuelve true si ambos son correctos.*/
bool crearCuenta(tGestor & gestor, const string & idUsu, const string & clave);   /*Esta función booleana devolverá true y con ello creará la cuenta si el usuario no existe y hay espacio en la lista.*/
bool tieneAvisos(const tGestor & gestor, string & aviso);   /*Esta función booleana comprueba si hay avisos,por lo que devolverá true y false en caso contrario.*/
void limpiarAvisos(tGestor & gestor);   /*Esta función actualiza los avisos dejando el campo vacío.*/
string resumenActividad(const tGestor & gestor);   /*Devuelve un string con los datos del resumen de la actividad del usuario.*/

//Funciones que se usan en el menú usuario del main.
void ordenar_Fecha(tGestor & gestor);  /*Esta función ordena por la fecha de la última actualización la lista de partidas en curso del usuario de la sesión.*/
void ordenar_Turno(tGestor & gestor);  /* Esta función ordena por turno la lista de partidas en curso del usuario de la sesión.*/
int partidasUsuario(const tGestor & gestor);  /*Este entero devuelve el número de partidas en curso del usuario de la sesión.*/
string cabecera(const tGestor & gestor, int posEnCurso);  /*Devuelve un string que contiene la información que se mostrará en la lista de partidas en curso.*/
bool nuevaPartida(tGestor & gestor);  /*Esta función booleana creará una nueva partida siempre que no se haya alcanzado el numero máximo de partidas,devolviendo un true.*/
void apuntaPartida(tGestor & gestor, int posParEnCurso);  /*Esta función guarda en partida seleccionada, el índice(de tipo entero) de dicha partida en la lista de partidas.*/

//Funciones que se usan en el menú partida del main.
void mostrarPartida(const tGestor & gestor);  /*Esta función muestra el estado de la partida en curso.*/
bool esSuTurno(const tGestor & gestor);  /*Esta función booleana comprueba si el turno corresponde o no al usuario.*/
void jugarPartida(tGestor & gestor, int col);  /*Esta función aplica la jugada col(de tipo entero) a la partida,y actualiza los avisos del adversario.*/
void abandonarPartida(tGestor & gestor);  /*Esta función abandona la partida como su propio nombre indica y avisa quién gana y quién pierde.*/

#endif  // GESTOR_H