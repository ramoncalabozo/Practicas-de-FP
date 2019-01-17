//Ramón Calabozo Maroto 
//Jaime Palazón Othon

#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

const int NADIE = 0;
const int MAQUINA = 1;
const int HUMANO = 2;
const int MAQUINA2 = 3;
const int MAXRONDAS = 7;
// ESTOS SON LOS PROTOTIPOS DE LAS FUNCIONES PEDIDAS EXPRESAMENTE
int monedasHumano(int); // Obtención de lo que saca el humano
int apuestaHumano(int, int, int); // Obtención de la apuesta del humano
int quienGana(int, int, int, int); // Determinación de resultado de la ronda
int ganadasMaquina(int);// numero de rondas ganadas por la maquina
int ganadasHumano(int);// numero de rondas ganadas por el humano 
int apuestaM(int, int);
int menu();// aparece el menu
int pedirMarcador(int);// cambia el marcador                            
int pedirMonedas(int);// cambia el numero de monedas que se pueden utilizar
bool mostrarReglas();// muestra las reglas
void juego(int, int);// Función que realiza lo que es el juego en si
void juego2(int, int); // Función que realiza lo que el juego entre las dos máquinas
int apuestaMaquina2(int, int, int);//Obtención de la apuesta del humano     
int monedasMaquina2(int, int);// Obtención de lo que saca la máquina 2
int quienGana2(int, int, int, int);// Determinación del resultado de la ronda en el juego entre las dos maquinas
int ganadasMaquina2(int);// numero de rondas ganadas por la máquina 2
int configurar1();// Permite leer del archivo el marcador
int configurar2();// Permite leer del archivo NUMMONEDAS
int main()
{
	srand(time(NULL)); // Iniciar con la hora actual el generador de números aleatorios
	int num;
	int marcador = configurar1();
	int NUMMONEDAS = configurar2();


	num = menu();
	while (num != 0) {

		if (num == 1) {
			marcador = pedirMarcador(NUMMONEDAS);

		}

		else if (num == 2) {
			NUMMONEDAS = pedirMonedas(marcador);

		}

		else if (num == 3) {
			mostrarReglas();

		}
		else if (num == 4) {

			juego(marcador, NUMMONEDAS);
		}
		else {
			(num == 5);
			juego2(marcador, NUMMONEDAS);
		}

		num = menu();
	}
	system("pause");
	return 0;


}


int monedasHumano(int NUMMONEDAS) {
	int monedasH;
	cout << " introduzca el numero de monedas que quiere sacar de o a  " << NUMMONEDAS << endl;
	cin >> monedasH;
	while (monedasH < NADIE || monedasH > NUMMONEDAS) {
		cout << " algun dato es erroneo introduzca de nuevo los datos " << endl;
		cin >> monedasH;
	}
	return monedasH;
}

int apuestaHumano(int eleccionM, int numMonedasH, int NUMMONEDAS) {
	int eleccionH;
	cout << " introduzca su apuesta " << endl;
	cin >> eleccionH;
	while (eleccionH < numMonedasH || eleccionH >(NUMMONEDAS * 2) || eleccionH == eleccionM) {
		cout << " algun dato es erroneo introduzca de nuevo los datos " << endl;
		cin >> eleccionH;
	}
	return eleccionH;
}

int quienGana(int eleccionM, int eleccionH, int numMonedasM, int numMonedasH) {
	int total = numMonedasM + numMonedasH;
	if (eleccionM == total) return MAQUINA;
	else {
		if (eleccionH == total)return HUMANO;
		else {
			return NADIE;
		}
	}
}
int ganadasMaquina(int ganadasM) {
	ganadasM = ganadasM + MAQUINA;
	return ganadasM;
}



int ganadasHumano(int ganadasH) {
	ganadasH = ganadasH + MAQUINA;
	return ganadasH;
}

int apuestaM(int monedasM, int NUMMONEDAS) {
	int eleccionM;
	eleccionM = monedasM + rand() % (NUMMONEDAS + MAQUINA);
	return eleccionM;
}
int menu() {
	int num;

	cout << " 1 - Cambiar el marcador " << endl;
	cout << " 2 - Cambiar numero de monedas " << endl;
	cout << " 3 - Acerca del juego de los chinos  " << endl;
	cout << " 4 - Jugar partida " << endl;
	cout << " 5 - Jugar una partida rapida " << endl;
	cout << " 0 - Salir" << endl;
	cin >> num;


	while (num < 0 || num > 5) {

		cout << " esa opcion no esta permitida" << endl << endl;

		cout << " 1 - Cambiar el marcador " << endl;
		cout << " 2 - Cambiar numero de monedas " << endl;
		cout << " 3 - Acerca del juego de los chinos  " << endl;
		cout << " 4 - Jugar partida " << endl;
		cout << " 5 - Jugar una partida rapida " << endl;
		cout << " 0 - Salir" << endl;
		cin >> num;
	}

	return num;
}

int pedirMarcador(int NUMMONEDAS) {
	int marcador;
	cout << " ¿ a cuantas rondas ganadas quieres jugar para ganar la partida ? " << endl;
	cin >> marcador;
	ofstream archivo;
	archivo.open("configP1.txt");
	archivo << marcador << endl;
	archivo << NUMMONEDAS << endl;
	archivo.close();
	cout << " el marcador se ha cambiado a " << marcador << endl;
	return marcador;
}

int pedirMonedas(int marcador) {
	int NUMMONEDAS;
	cout << " ¿cuantas monedas quieres tener? ";
	cin >> NUMMONEDAS;
	ofstream archivo;
	archivo.open("configP1.txt");
	archivo << marcador << endl;
	archivo << NUMMONEDAS << endl;
	archivo.close();
	cout << " el numero de monedas ahora es " << NUMMONEDAS << endl;
	return NUMMONEDAS;
}

bool mostrarReglas() {
	bool devuelve = false;
	string reglas;
	string final = "XXX";
	ifstream archivo;
	archivo.open("reglas.txt");
	if (!archivo.is_open()) {
		cout << "no se encuentra el archivo" << endl;
		devuelve = false;
	}
	else {
		getline(archivo, reglas);
		cout << reglas << endl;
		while (reglas != final) {
			getline(archivo, reglas);
			cout << reglas << endl;
		}
		devuelve = true;
	}

	return devuelve;
}
void  juego(int marcador, int NUMMONEDAS) {
	int monedasM, monedasH; // Monedas sacadas en cada ronda
	int eleccionM, eleccionH; // Apuestas en cada ronda
	int ganadasM, ganadasH; // Contadores de rondas ganadas
	int total, resultado; // Resultado de la ronda (NADIE = nadie gana; MAQUINA = gana la maquina; HUMANO = gana el humano)
	int rondas = 0;
	int opcion;
	int num;
	ganadasH = 0;
	ganadasM = 0;
	do {
		monedasM = rand() % (NUMMONEDAS + MAQUINA);
		eleccionM = apuestaM(monedasM, NUMMONEDAS);
		monedasH = monedasHumano(NUMMONEDAS);
		cout << " la maquina piensa que hay " << eleccionM << endl;
		eleccionH = apuestaHumano(eleccionM, monedasH, NUMMONEDAS);
		total = monedasH + monedasM;
		cout << " La maquina elige " << monedasM << endl;
		cout << " el total de monedas es  " << total << endl;
		resultado = quienGana(eleccionM, eleccionH, monedasH, monedasM);
		cout << " gana el " << resultado << endl << endl;
		cout << " NADIE = 0 , MAQUINA = 1 , HUMANO = 2  " << endl << endl;
		rondas = rondas + 1;

		if (resultado == MAQUINA) {
			ganadasM = ganadasMaquina(ganadasM);
		}
		else if (resultado == HUMANO) {

			ganadasH = ganadasHumano(ganadasH);
		}

		cout << " el numero de rondas ganadas por el humano es " << ganadasH << endl;
		cout << " el numero de rondas ganadas por la maquina es " << ganadasM << endl << endl;

		while (rondas == MAXRONDAS) {
			rondas = 0;
			cout << " ya has jugado mucho " << endl;
			cout << " 0 SALIR      1 SEGUIR" << endl;
			cin >> opcion;
			while (opcion != 0 && opcion != 1) {
				cout << "valor no valido " << endl;
				cin >> opcion;
			}
			if (opcion == 1) {
				cout << " perfecto sigues jugando " << endl;

			}
			else {
				return;
			}
		}
	} while (ganadasH < marcador && ganadasM < marcador);

	if (ganadasH == marcador)
		cout << " ha ganado el humano " << endl;
	else {
		cout << " ha ganado la maquina" << endl;
	}

	cout << " se ha acabado la partida" << endl << endl;
	system("pause");
	return;
}
void juego2(int marcador, int NUMMONEDAS) {
	int monedasM, monedasM2; // Monedas sacadas en cada ronda
	int eleccionM, eleccionM2; // Apuestas en cada ronda
	int ganadasM, ganadasM2; // Contadores de rondas ganadas
	int total, resultado; // Resultado de la ronda (NADIE = nadie gana; MAQUINA1 = gana la maquina 1; MAQUINA2 = gana la máquina 2)
	int rondas = 0;
	int opcion;
	ganadasM2 = 0;
	ganadasM = 0;
	do {

		monedasM = rand() % (NUMMONEDAS + MAQUINA);
		cout << " el numero de monedas sacadas por la maquina 1 es " << monedasM << endl;
		monedasM2 = monedasMaquina2(NUMMONEDAS, monedasM);
		eleccionM = apuestaM(monedasM, NUMMONEDAS);
		cout << " la maquina 1 piensa que hay " << eleccionM << " monedas" << endl;
		eleccionM2 = apuestaMaquina2(eleccionM, monedasM2, NUMMONEDAS);
		cout << " la maquina 2 piensa que hay " << eleccionM2 << " monedas" << endl;
		total = monedasM2 + monedasM;
		cout << " el total de monedas es  " << total << endl << endl;
		resultado = quienGana2(eleccionM, eleccionM2, monedasM2, monedasM);
		cout << " gana el " << resultado << endl << endl;
		cout << " NADIE = 0 , MAQUINA1 = 1 , MAQUINA2 = 3  " << endl << endl;
		rondas = rondas + 1;
		if (resultado == MAQUINA) {
			ganadasM = ganadasMaquina(ganadasM);
		}
		else if (resultado == MAQUINA2) {

			ganadasM2 = ganadasMaquina2(ganadasM2);
		}

		cout << " el numero de rondas ganadas por la maquina 1 es " << ganadasM << endl;
		cout << " el numero de rondas ganadas por la maquina 2 es " << ganadasM2 << endl << endl;
		system("pause");

		while (rondas == MAXRONDAS) {
			rondas = 0;
			cout << " ya has jugado mucho " << endl;
			cout << " 0 SALIR      1 SEGUIR" << endl;
			cin >> opcion;
			while (opcion != 0 && opcion != 1) {
				cout << "valor no valido " << endl;
				cin >> opcion;
			}
			if (opcion == 1) {
				cout << " perfecto sigues jugando " << endl;

			}
			else {
				return;
			}
		}
	} while (ganadasM2 < marcador && ganadasM < marcador);

	if (ganadasM == marcador)
		cout << " ha ganado la maquina l" << endl;
	else {
		cout << " ha ganado la maquina 2" << endl;
	}
	cout << " SE HA ACABADO LA PARTIDA" << endl << endl << endl;

	system("pause");
	return;
}


int apuestaMaquina2(int eleccionM, int monedasM2, int NUMMONEDAS) {

	int eleccionM2;

	if (eleccionM == 0) {
		eleccionM2 = monedasM2;
		cout << " como la maquina1 piensa que hay 0 monedas,eso quiere decir que el numero total de monedas es el mio que es " << endl;
		return eleccionM2;
	}

	else if (eleccionM == (NUMMONEDAS * 2)) {
		eleccionM2 = monedasM2 + NUMMONEDAS;
		cout << "como la maquina1 piensa que hay  6 moneda , eso quiere decir que el numero total de monedas es 3 + la monedas que yo he sacado " << endl;
		while (eleccionM2 == eleccionM) {
			cout << "algun dato es erroneo la maquina debe elegir otro numero " << endl;
			eleccionM2 = monedasM2 + rand() % (NUMMONEDAS + MAQUINA);
		}
		return eleccionM2;
	}
	else {
		eleccionM2 = monedasM2 + rand() % (NUMMONEDAS + MAQUINA);
		while (eleccionM2 == eleccionM) {
			cout << " algun dato es erroneo la maquina debe elegir otro numero " << endl;
			eleccionM2 = monedasM2 + rand() % (NUMMONEDAS + MAQUINA);
		}
		return eleccionM2;
	}

}
int monedasMaquina2(int NUMMONEDAS, int monedasM) {
	int monedasM2;
	monedasM2 = rand() % (NUMMONEDAS + MAQUINA);
	cout << " el numero de monedas sacadas por la maquina 2 es " << monedasM2 << endl;
	return monedasM2;
}
int quienGana2(int eleccionM, int eleccionM2, int monedasM2, int monedasM) {
	int total = monedasM + monedasM2;
	if (eleccionM == total) return MAQUINA;
	else {
		if (eleccionM2 == total)return MAQUINA2;
		else {
			return NADIE;
		}
	}
}
int ganadasMaquina2(int ganadasM2) {
	ganadasM2 = ganadasM2 + MAQUINA;
	return ganadasM2;
}
int configurar1() {
	ifstream archi;
	int marcador;
	archi.open("configP1.txt");
	if (!archi.is_open()) {
		cout << " no se abre archivo" << endl;
		cout << " el marcador esta a 2" << endl;
		return 2;
	}
	else {
		archi >> marcador;
		cout << " el marcador esta a " << marcador << endl;

	}

	archi.close();
	return marcador;



}
int configurar2() {
	ifstream arch;
	int NUMMONEDAS;
	arch.open("configP1.txt");
	if (!arch.is_open()) {
		cout << " el numero de monedas es 3" << endl;
		return 3;
	}
	else {
		arch >> NUMMONEDAS;
		arch >> NUMMONEDAS;
		cout << " el numero de monedas es " << NUMMONEDAS << endl;
	}
	return NUMMONEDAS;
}