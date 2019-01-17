#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

//Constantes***********************************************************************
const int MAX_COLORES_DIFICIL = 17;
const int MAX_SECUENCIAS_DIFICIL = 15;
const int MAX_SECUENCIAS = 10;
const int MAX_COLORES = 12;
const int MAX_JUGADORES = 10;
const int MAX_PUNTOS = 1350;
//Prototipos de funciones**********************************************************
int main();
int menu(int);
typedef enum { facil, dificil } tModo;
typedef enum { rojo, verde, azul, dorado, blanco, marron, naranja } tColores;
typedef tColores tSecuencia[MAX_SECUENCIAS_DIFICIL];
tColores charToColor(char);
tColores intToColor(int);
void generarSecuencia(tSecuencia, tModo, int);
bool comprobarColor(const tSecuencia, int, tColores);
void mostrarSecuencia(const tSecuencia, int);
float Juego(string, tModo, int);
char comprobarLetra(char);
void mostrarcolores(int);
void utilizarAyuda(const tSecuencia, int, int&, bool&);
typedef struct {
	float puntuacion;
	string nombre;
}tJugador;
typedef tJugador tPlayers[MAX_JUGADORES];
void cargarRanking(tPlayers, int);
void escribirRanking(tPlayers, float, string);
void visualizarRanking(const tPlayers, float, string);
void visualizarMejorJugador(const tPlayers, float, string);
void ActualizarRanking(tPlayers, int, string);
int main() {
	int centinela = -1;
	string nombre;
	srand(time(NULL));
	bool ayudaUsada = false;
	int opcion = 0;
	tModo modo;
	int numAyudas = 3;
	float puntuacion = 0;
	tPlayers clasificacion;
	cargarRanking(clasificacion, centinela);
	cout << " ! Bienvenido a Simon dice ! " << endl;
	cout << " ¿ como te llamas ? " << endl;
	getline(cin, nombre);
	cout << " Hola " << nombre << ", presione <Enter> para continuar:" << endl;
	cin.get();
	opcion = menu(opcion);
	while (opcion != 0){
		switch (opcion){
		case 1: modo = facil; break;
		case 2: modo = dificil; break;
		}
		if (opcion == 1 || opcion == 2){
			puntuacion = Juego(nombre, modo, numAyudas);
			ActualizarRanking(clasificacion, puntuacion, nombre);
			cout << "Tu puntuacion ha sido " << puntuacion << endl << endl << endl;
		}
		else if (opcion == 3){

			visualizarRanking(clasificacion, puntuacion, nombre);
		}
		else if (opcion == 4) {

			visualizarMejorJugador(clasificacion, puntuacion, nombre);
		}

		escribirRanking(clasificacion, puntuacion, nombre);
		opcion = menu(opcion);
	}

	escribirRanking(clasificacion, puntuacion, nombre);

	system("pause");
	return 0;
}

int menu(int){
	int opcion;
	do{
		cout << "   MENU " << endl << endl;
		cout << "0. Salir del Juego" << endl;
		cout << "1. Modo Sencillo." << endl;
		cout << "2. Modo Dificil." << endl;
		cout << "3. Ver 10 mejores jugadores " << endl;
		cout << "4. Ver jugador(es) con la puntuacion mas alta" << endl;
		cin >> opcion;
		system("cls");
	} while (opcion != 0 && opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4);

	return opcion;
}


float Juego(string nombre, tModo modo, int ayudas){
	cout << "Recuerda que tienes 3 ayudas que puedes usar pulsando la x" << endl;
	int numColores = 3;//Numero de Colores que se quieren generar 
	int numero = 1;//Numero de colores que se muesran
	int indice = 0;//COntador para la comprobacion de los colores introducidos
	char colorjugador;// Letra introducida por el usuario que representa a un color
	bool comprobar = true;
	bool ayudaUsada = false;
	tColores Color;
	tSecuencia secuenciaColores;
	tColores color;
	float puntuacion = 0;
	int Max;
	if (modo == facil){
		Max = MAX_COLORES;
	}
	else {
		Max = MAX_COLORES_DIFICIL;
	}
	while (numColores <= Max && comprobar == true){
		cout << "secuencia numero  " << numero << endl;;
		generarSecuencia(secuenciaColores, modo, numColores);
		mostrarSecuencia(secuenciaColores, numero);
		cout << "Memoriza la secuencia y pulsa <Enter> para continuar:" << endl << endl;
		cin.get();
		system("pause");
		system("cls");
		cout << "introduzca la secuencia(Solo las iniciales de cada color):" << endl;

		while (indice < numColores && comprobar == true){
			Color = secuenciaColores[indice];
			cin >> colorjugador;
			colorjugador = comprobarLetra(colorjugador);
			if (colorjugador == 'x' || colorjugador == 'X'){
				utilizarAyuda(secuenciaColores, indice, ayudas, ayudaUsada);
				cin >> colorjugador;
				colorjugador = comprobarLetra(colorjugador);
				if (modo == dificil){
					puntuacion = puntuacion - (7 * 1.5);
				}
				else {
					puntuacion = puntuacion - 7;
				}
			}
			color = charToColor(colorjugador);

			comprobar = comprobarColor(secuenciaColores, indice, color);
			if (comprobar == true){
				indice++;
				if (modo == dificil){
					puntuacion = puntuacion + (5 * 1.5);
				}
				else {
					puntuacion = puntuacion + 5;
				}
			}
		}
		numero++;
		numColores++;
		indice = 0;
		if (comprobar == true){
			if (modo == dificil){
				puntuacion = puntuacion + (10 * 1.5);
			}
			else {
				puntuacion = puntuacion + 10;
			}
		}
	}
	if (puntuacion < 0){
		puntuacion = 0;
	}

	if (comprobar == true){
		cout << "             HAS GANADO ENORABUENA!            " << endl << endl;
	}
	return puntuacion;
}


void generarSecuencia(tSecuencia secuenciaColores, tModo modo, int numColores){

	int n;
	if (modo == facil){
		n = 4;
	}
	else {
		n = 7;
	}
	int numero;
	int ind = 0;
	while (ind < numColores && numColores <= 3){
		numero = rand() % n;
		tColores color = intToColor(numero);
		secuenciaColores[ind] = color;
		ind++;

	}
	if (numColores >= 4){
		numero = rand() % n;
		tColores color = intToColor(numero);
		secuenciaColores[numColores - 1] = color;
	}
}




void mostrarSecuencia(const tSecuencia secuenciaColores, int numero){

	for (int i = 0; i < numero + 2; i++){
		switch (secuenciaColores[i]){
		case 0: cout << "Rojo" << endl; break;
		case 1: cout << "Verde" << endl; break;
		case 2: cout << "Azul" << endl; break;
		case 3: cout << "Dorado" << endl; break;
		case 4: cout << "Blanco" << endl; break;
		case 5: cout << "Marron" << endl; break;
		case 6: cout << "Naranja" << endl; break;

		}
	}
}


tColores intToColor(int numero){
	tColores col;
	col = tColores(numero);
	return col;

}


tColores charToColor(char color){
	switch (color){
	case  'R':
	case  'r': return rojo; break;
	case  'V':
	case  'v': return verde; break;
	case  'A':
	case  'a': return azul; break;
	case  'D':
	case  'd': return dorado; break;
	case  'B':
	case  'b': return blanco; break;
	case  'M':
	case  'm': return marron; break;
	case  'N':
	case  'n': return naranja; break;

	}
}


bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color){
	if (color != secuenciaColores[indice]){

		cout << "El color " << indice + 1 << " no es correcto." << endl << endl;
		cout << "GAME OVER" << endl;
		return false;
	}
	else if (color == secuenciaColores[indice]){
		cout << "aciertooooooooooooooooooooooooooo" << endl;

		return true;
	}
}


char comprobarLetra(char colorjugador){
	while (colorjugador != 'r' && colorjugador != 'v' && colorjugador != 'a' && colorjugador != 'd' && colorjugador != 'R' && colorjugador != 'V' && colorjugador != 'A' && colorjugador != 'D' && colorjugador != 'b' && colorjugador != 'm' && colorjugador != 'n' && colorjugador != 'x' && colorjugador != 'X'){
		cout << "la letra introducida es erronea, introduzca letra de juego" << endl;
		cin >> colorjugador;
	}
	return colorjugador;
}

void utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &ayudas, bool& ayudaUsada){
	ayudas = ayudas - 1;
	int color;
	if (ayudas < 0 && ayudaUsada == true){
		cout << "Lo sentimos no te quedan ayudas " << endl;
	}
	else {
		cout << "El siguiente color es el ..." << endl;
		color = secuenciaColores[indice];
		charToColor(color);
		mostrarcolores(color);
		ayudaUsada = true;
		cout << "Te quedan " << ayudas << " ayudas" << endl;
	}
}

void mostrarcolores(int color){
	switch (color){
	case 0: cout << "Rojo" << endl; break;
	case 1: cout << "Verde" << endl; break;
	case 2: cout << "Azul" << endl; break;
	case 3: cout << "Dorado" << endl; break;
	case 4: cout << "Blanco" << endl; break;
	case 5: cout << "Marron" << endl; break;
	case 6: cout << "Naranja" << endl; break;

	}
}

void cargarRanking(tPlayers clasificacion, int centinela){
	ifstream archivo;
	int aux;
	archivo.open("top.txt");
	int i = 0;
	if (archivo.is_open()){
		archivo >> aux;
		while (i < MAX_JUGADORES && (!archivo.eof()) && aux != -1){ //Comprueba si el archivo esta vacio, e introduce el ranking en clasificacion.
			clasificacion[i].puntuacion = aux;
			getline(archivo, clasificacion[i].nombre);
			i++;
			archivo >> aux;
		}

		for (int k = i; k < MAX_JUGADORES; k++){ // introduce en los espacios vacios de clasificacion puntuacion -1, para rellenar todos los espacios del array. 
			clasificacion[k].puntuacion = -1;
		}

	}
	archivo.close();
}

void ActualizarRanking(tPlayers clasificacion, int puntuacion, string nombre){

	bool set = false;
	int i = 0;
	while (clasificacion[i].puntuacion != -1 && i < MAX_JUGADORES){ //Comprbar los jugadores que hay en clasificacion
		i++;
	}
	if (i < MAX_JUGADORES && clasificacion[i].puntuacion == -1){ // introducir el jugador en el espacio libre.
		clasificacion[i].puntuacion = puntuacion;
		clasificacion[i].nombre = nombre;
		set = true;
	}
	else if (clasificacion[MAX_JUGADORES - 1].puntuacion < puntuacion){  //Comparar el ultimo jugador con la puntuacion y nombre del jugador actual y si es mayor reemplazarla.
		clasificacion[MAX_JUGADORES - 1].puntuacion = puntuacion;
		clasificacion[MAX_JUGADORES - 1].nombre = nombre;
		set = true;

	}


	if (set == true){
		// Reordenar;

		tJugador mejorpunt;
		while (i < 100){
			int n = 0;
			while (clasificacion[n].puntuacion != -1 && n < MAX_JUGADORES){
				if (clasificacion[n + 1].puntuacion > clasificacion[n].puntuacion){
					mejorpunt.puntuacion = clasificacion[n].puntuacion;
					mejorpunt.nombre = clasificacion[n].nombre;

					clasificacion[n].puntuacion = clasificacion[n + 1].puntuacion;
					clasificacion[n].nombre = clasificacion[n + 1].nombre;

					clasificacion[n + 1].puntuacion = mejorpunt.puntuacion;
					clasificacion[n + 1].nombre = mejorpunt.nombre;
				}

				n++;
				i++;
			}
		}
		system("pause");



	}


}



void escribirRanking(tPlayers clasificacion, float puntuacion, string nombre){
	ofstream archivo;
	archivo.open("top.txt");
	int i = 0;
	for (int indice = 0; indice < MAX_JUGADORES && puntuacion >= -1; indice++){
		if (clasificacion[indice].puntuacion >= 0){
			archivo << clasificacion[indice].puntuacion << " ";
			archivo << clasificacion[indice].nombre << endl;
		}
		i++;

	}

}

void visualizarRanking(const tPlayers clasificacion, float puntuacion, string nombre){
	int centinela = -1;
	for (int indice = 0; indice < MAX_JUGADORES && clasificacion[indice].puntuacion != centinela; indice++){
		if (clasificacion[indice].puntuacion >= 0){
			cout << clasificacion[indice].puntuacion << " - ";
			cout << clasificacion[indice].nombre << endl;
		}
	}

}
void visualizarMejorJugador(const tPlayers clasificacion, float puntuacion, string nombre){
	if (clasificacion[0].puntuacion == -1){
		cout << "Todavdia no hay mejor jugador " << endl;
	}
	else {
		cout << clasificacion[0].puntuacion << " ";
		cout << clasificacion[0].nombre << endl;
	}
	for (int indice = 1; indice < MAX_JUGADORES; indice++){
		if (clasificacion[0].puntuacion == clasificacion[indice].puntuacion){
			cout << clasificacion[indice].puntuacion << " ";
			cout << clasificacion[indice].nombre << endl;
		}
	}
}
