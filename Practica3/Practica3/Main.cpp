
/*RAMON CALABOZO MAROTO
JAIME PALAZON OTHON */




#include "UNOSOLO.h"
int main() {
	srand(time(NULL));
	bool leer;
	tMovimiento mov;
	string nombre;
	tJuego juego;
	char opcion;
	int movimientos;
	do {
		cout << " ¿ Qué partida quieres jugar ?" << endl;
		cin >> nombre;
		cout << endl << endl;
		bool funciondecarga = cargar(juego, nombre);
		nuevoEstado(juego);
		if (funciondecarga == true) {
			while (juego.estado == JUGANDO) {
				//la funcion cargar(juego, nombre) va a devolver true o false, que es igual al booleano funciondecarga (podeis sustituirlo por el llamamiento a la funcion
				mostrar(juego);
				//leer = leermovimientos(juego, mov);
				partida(juego);
				nuevoEstado(juego);
				if (juego.estado == JUGANDO) {
					mostrar(juego);
				}
			}
		}
		else {
			cout << " AL no poderse cargar la partida que deseaba se cargara un tablero aleatorio" << endl;
			cout << " Indique el numero de movimientos  de ese tablero " << endl;
			cin >> movimientos;
			generarTablero(juego, movimientos);

			nuevoEstado(juego);

			while (juego.estado == JUGANDO) {
				cout << "                 Juega Tablero Aleatorio" << endl;
				mostrar(juego);
				partida(juego);
				nuevoEstado(juego);
				if (juego.estado == JUGANDO) {
					mostrar(juego);
				}
			}
		}
		guardar(juego, nombre);
		cout << "¿Quieres intentarlo de nuevo?" << endl;
		cout << " SI--s  NO--n" << endl;
		cin >> opcion;
	} while (opcion == 's');
	system("pause");
	return 0;
}