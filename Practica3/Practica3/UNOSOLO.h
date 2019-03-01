/*RAMON CALABOZO MAROTO
JAIME PALAZON OTHON */




#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
const int DIM = 6, NUM_DIRS = 4;
typedef enum { NULA = 0, VACIA = 2, FICHA = 10 } tCelda;
typedef enum { BLOQUEO, GANA, JUGANDO, ABANDONO }tEstado;
typedef bool tPosibles[NUM_DIRS];
typedef enum { ARRIBA, ABAJO, IZQUIERDA, DERECHA, INCORRECTA }tDireccion;
typedef tCelda tTablero[DIM][DIM];


/* Estrucutura que contiene lo esencial del juego que es lo siguiente
Los movimientos que has realizado hasta ese momento,las bolas iniciales,
donde se encuentra la meta, las dimensiones del tablero y el estado de la partida que es un enumerado
*/
typedef struct {
	tTablero tablero;
	int movimientos;
	int bolasiniciales;
	int filameta;
	int columnameta;
	int dimensiones;
	tEstado estado;
} tJuego;
/*Estructura que contiene los datos del movimiento que son los siguientes
La ficha seleccionada ,el array de las posibles movimientos ,enumerado de las direcciones;
*/
typedef struct {
	int filaorigen;
	int columnaorigen;
	tPosibles posibles;
	tDireccion direccion;
}tMovimiento;

void colorFondo(int);
bool cargar(tJuego &juego, string nombre); //quitar lo blanco     
void guardar(const tJuego &juego, string nombre);
void mostrar(const tJuego &juego);
tCelda conversion(int);
void guardar(const tJuego &juego, string nombre);
bool leermovimientos(const tJuego juego, tMovimiento &mov);
bool Comprobacion(tMovimiento &mov, tJuego);
void ejecutarMovimiento(tJuego &juego, tMovimiento &mov);
void partida(tJuego &juego);
void partida(tJuego &juego);
void nuevoEstado(tJuego &juego);
void generarTablero(tJuego &juego, int movimientos);
void iniciarTablero(tJuego &juego);
void fijarMeta(tJuego &juego);
bool movimientoInverso(tJuego &juego);
