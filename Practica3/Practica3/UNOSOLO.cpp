/*RAMON CALABOZO MAROTO
JAIME PALAZON OTHON */



#include "UNOSOLO.h"
void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

bool cargar(tJuego &juego, string nombre) { // string que sirve para elegir la partida
	bool cargar = true;
	int color;
	tCelda ficha;
	short int movimientos;
	short int empezar;
	short int bi;
	short int fm;
	int cm;
	ifstream archivo;
	archivo.open(nombre);
	if (archivo.is_open()) {
		archivo >> empezar;		//volcar directamente del archivo a la estructura, sin necesidad de usar variables
		juego.dimensiones = empezar;
		if (juego.dimensiones == DIM) {

			//	Vamos introduciendo los datos del fichero en el Array

			archivo >> bi;
			juego.bolasiniciales = bi;
			archivo >> fm;
			juego.filameta = fm;
			archivo >> cm;
			juego.columnameta = cm;
			for (int i = 0; i < DIM; i++) {
				for (int j = 0; j < DIM; j++) {
					archivo >> color;
					ficha = conversion(color);
					juego.tablero[i][j] = ficha;
				}
			}
			archivo >> movimientos;
			juego.movimientos = movimientos;
		}
		else {
			cout << " las dimensiones del archivo no son correctas " << endl;
			cargar = false;
		}


	}
	else {
		cout << "el archivo no ha sido cargado con exito " << endl;
		cargar = false;
	}
	archivo.close();
	return cargar;
}

void mostrar(const tJuego &juego) {
	tCelda color;
	cout << " El numero de movimientos es ..." << juego.movimientos << endl;
	cout << " ";
	/* Escribe la primera fila que digamos que son las cordenadas del tablero*/
	for (int i = 1; i <= DIM; i++) {
		cout << "  " << i << " ";
	}
	cout << endl << endl;
	/*
	Esta parte de la funcion lo que hace es va pintando el tablero por fila pintando primero la cordenada
	Si la parte del tablero que vamos a pintar es la meta , utilizamos el char(254)
	*/
	for (int j = 1; j <= DIM; j++) {
		cout << j;
		for (int x = 0; x < DIM; x++) {
			color = juego.tablero[j - 1][x];
			cout << "  ";
			colorFondo(color);
			if (j == juego.filameta && x + 1 == juego.columnameta) {
				cout << char(254);
			}
			if (j != juego.filameta || x + 1 != juego.columnameta) {
				cout << " ";
			}
			colorFondo(0);
			cout << " ";
		}
		cout << endl << endl;
	}
	cout << endl;
}

tCelda conversion(int color) {  // combierte el color en enumerado dependiendo del numero
	tCelda ficha;
	switch (color) {
	case 0: ficha = NULA; break;
	case 2: ficha = VACIA; break;
	case 10: ficha = FICHA; break;
		return ficha;
	}
}

void guardar(const tJuego &juego, string nombre) {
	ofstream archivo;
	archivo.open(nombre);
	short int dimensiones;
	short int bolasiniciales;
	short int filameta;
	short int columnameta;
	short int movimientos;
	int colores;
	/*
	Esta funcion se encarga de coger los datos del array y los mete en el fichero
	*/
	dimensiones = juego.dimensiones;
	archivo << dimensiones << endl;
	bolasiniciales = juego.bolasiniciales;
	archivo << bolasiniciales << endl;
	filameta = juego.filameta;
	archivo << filameta << endl;
	columnameta = juego.columnameta;
	archivo << columnameta << endl;
	movimientos = juego.movimientos;
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			colores = juego.tablero[i][j];
			archivo << colores << " ";
		}
		archivo << endl;
	}
	archivo << movimientos;
	archivo << endl;
	archivo.close();
}


bool leermovimientos(const tJuego juego, tMovimiento &mov) {
	bool comprobacion;
	bool leer = true;
	int filaorigen;
	int columnaorigen;
	do {
		cout << "Indica que ficha quieres mover(fila columna)" << endl;
		cin >> filaorigen;
		cin >> columnaorigen;
		mov.filaorigen = filaorigen - 1;
		mov.columnaorigen = columnaorigen - 1;
		if (mov.filaorigen < 0 || mov.filaorigen >= DIM || mov.columnaorigen < 0 || mov.columnaorigen >= DIM) {
			cout << " La casilla seleccionada esta fuera del tablero " << endl;
		}
	} while (mov.filaorigen < 0 || mov.filaorigen >= DIM || mov.columnaorigen < 0 || mov.columnaorigen >= DIM);
	comprobacion = Comprobacion(mov, juego);
	if (comprobacion == true) {
		cout << " La ficha seleccionada puede mover para : " << endl;
		if (mov.posibles[ARRIBA] == true) {
			cout << " 0 - Arriba " << endl;
		}
		if (mov.posibles[ABAJO] == true) {
			cout << " 1 - Abajo " << endl;
		}
		if (mov.posibles[DERECHA] == true) {
			cout << " 2 - Derecha " << endl;
		}
		if (mov.posibles[IZQUIERDA] == true) {
			cout << " 3 - Izquierada " << endl;
		}
		cout << " 4 - Elegir otra ficha " << endl;
		cout << " 5 - Abandonar Partida " << endl;
	}
	else {
		leermovimientos(juego, mov);
	}
	return leer;
}

bool Comprobacion(tMovimiento &mov, tJuego juego) {
	/* Comprueba los distintos movimientos que puede hacer la ficha y intruduce los resultado
	en el array booleano
	*/
	bool leer = true;
	mov.posibles[ARRIBA] = false;
	mov.posibles[ABAJO] = false;
	mov.posibles[DERECHA] = false;
	mov.posibles[IZQUIERDA] = false;

	if (mov.filaorigen - 2 > 0) {// para asegurarse que no se recorre el array en posiciones que no existen
		if (juego.tablero[mov.filaorigen - 1][mov.columnaorigen] == FICHA && juego.tablero[mov.filaorigen - 2][mov.columnaorigen] == VACIA) {
			mov.posibles[ARRIBA] = true;
		}

		else {
			mov.posibles[ARRIBA] = false;
		}

	}
	else {
		mov.posibles[ARRIBA] = false;
	}




	if (mov.filaorigen + 2 < 6) {// para asegurarse que no se recorre el array en posiciones que no existen

		if (juego.tablero[mov.filaorigen + 1][mov.columnaorigen] == FICHA && juego.tablero[mov.filaorigen + 2][mov.columnaorigen] == VACIA) {
			mov.posibles[ABAJO] = true;
		}

		else {
			mov.posibles[ABAJO] = false;
		}
	}
	else {
		mov.posibles[ABAJO] = false;
	}




	if (mov.columnaorigen - 2 > 0) {// para asegurarse que no se recorre el array en posiciones que no existen

		if (juego.tablero[mov.filaorigen][mov.columnaorigen - 1] == FICHA && juego.tablero[mov.filaorigen][mov.columnaorigen - 2] == VACIA) {
			mov.posibles[IZQUIERDA] = true;
		}

		else {
			mov.posibles[IZQUIERDA] = false;
		}

	}

	else {
		mov.posibles[IZQUIERDA] = false;
	}



	if (mov.columnaorigen + 2 > 0) {//para asegurarse que no se recorre el array en posiciones que no existen
		if (juego.tablero[mov.filaorigen][mov.columnaorigen + 1] == FICHA && juego.tablero[mov.filaorigen][mov.columnaorigen + 2] == VACIA) {
			mov.posibles[DERECHA] = true;
		}

		else {
			mov.posibles[DERECHA] = false;
		}
	}
	else {
		mov.posibles[DERECHA] = false;
	}


	if (mov.posibles[DERECHA] == false && mov.posibles[IZQUIERDA] == false && mov.posibles[ARRIBA] == false && mov.posibles[ABAJO] == false) {
		leer = false;
		cout << " La casilla seleccionada no tiene movimientos posibles" << endl;
	}
	return leer;
}

void ejecutarMovimiento(tJuego &juego, tMovimiento &mov) {
	int opcion;
	bool leer;
	cin >> opcion;
	char guardar;
	if (opcion == 0) {
		if (mov.posibles[ARRIBA] == true) {
			juego.tablero[mov.filaorigen][mov.columnaorigen] = VACIA;
			juego.tablero[mov.filaorigen - 1][mov.columnaorigen] = VACIA;
			juego.tablero[mov.filaorigen - 2][mov.columnaorigen] = FICHA;
		}
		else {
			cout << " La casilla seleccionada no admite ese movimiento " << endl;
		}
	}
	if (opcion == 1) {
		if (mov.posibles[ABAJO] == true) {
			juego.tablero[mov.filaorigen][mov.columnaorigen] = VACIA;
			juego.tablero[mov.filaorigen + 1][mov.columnaorigen] = VACIA;
			juego.tablero[mov.filaorigen + 2][mov.columnaorigen] = FICHA;
		}
		else {
			cout << " La casilla seleccionada no admite ese movimiento " << endl;
		}
	}
	if (opcion == 2) {
		if (mov.posibles[DERECHA] == true) {
			juego.tablero[mov.filaorigen][mov.columnaorigen] = VACIA;
			juego.tablero[mov.filaorigen][mov.columnaorigen + 1] = VACIA;
			juego.tablero[mov.filaorigen][mov.columnaorigen + 2] = FICHA;
		}
		else {
			cout << " La casilla seleccionada no admite ese movimiento " << endl;
		}
	}
	if (opcion == 3) {
		if (mov.posibles[IZQUIERDA] == true) {
			juego.tablero[mov.filaorigen][mov.columnaorigen] = VACIA;
			juego.tablero[mov.filaorigen][mov.columnaorigen - 1] = VACIA;
			juego.tablero[mov.filaorigen][mov.columnaorigen - 2] = FICHA;
		}
		else {
			cout << " La casilla seleccionada no admite ese movimiento " << endl;
		}
	}
	if (opcion == 4) {
		leermovimientos(juego, mov);
	}
	if (opcion == 5) {
		cout << "Has decidido abandonar la partida " << endl;
		juego.estado = ABANDONO;
	}
	juego.movimientos = juego.movimientos + 1;
}

void partida(tJuego &juego) {
	string nombre;
	tMovimiento mov;
	bool leer;
	leer = leermovimientos(juego, mov);
	if (leer == true) {
		ejecutarMovimiento(juego, mov);
	}
}

void nuevoEstado(tJuego &juego) {
	if (juego.estado != ABANDONO) {
		int c = 0;
		int C = 0;
		juego.estado = BLOQUEO;
		for (int i = 0; i < DIM; i++) {
			for (int j = 0; j < DIM; j++) {
				if (juego.tablero[i][j] == FICHA) {
					C = C + 1;
					if ((juego.tablero[i - 1][j] == FICHA && juego.tablero[i - 2][j] == VACIA) ||
						(juego.tablero[i + 1][j] == FICHA && juego.tablero[i + 2][j] == VACIA) ||
						(juego.tablero[i][j - 1] == FICHA && juego.tablero[i][j - 2] == VACIA) ||
						(juego.tablero[i][j + 1] == FICHA && juego.tablero[i][j + 2] == VACIA)) {
						juego.estado = JUGANDO;
					}
				}
				c = C;
			}
		}

		if (c == 1 && juego.tablero[juego.filameta - 1][juego.columnameta - 1] == FICHA) {
			juego.estado = GANA;
			cout << "HAS GANADO " << endl;
		}
		if (juego.estado == BLOQUEO) {
			cout << "Lo sentimos estas bloqueado" << endl;
		}
	}
}

void generarTablero(tJuego &juego, int movimientos) {
	int contador = 0;
	bool inverso = true;
	iniciarTablero(juego);
	fijarMeta(juego);

	while (contador < movimientos || inverso == false) {
		inverso = movimientoInverso(juego);
		juego.movimientos = juego.movimientos + 1;
		mostrar(juego);

		contador = contador + 1;
	}
}
void iniciarTablero(tJuego &juego) {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			juego.tablero[i][j] = NULA;
		}
	}
}
void fijarMeta(tJuego &juego) {
	juego.filameta = ((rand() % ((DIM - 1) + 1)) + 1); // numero aleatorio
	juego.columnameta = ((rand() % ((DIM - 1) + 1)) + 1); // numero aleatorio
	juego.tablero[juego.filameta - 1][juego.columnameta - 1] = FICHA;
	juego.movimientos = 0;
}
bool movimientoInverso(tJuego &juego) {
	bool inverso = true;
	tCelda tengo = NULA;
	int i, j;
	int aleatorio;
	tDireccion direccion;
	bool ok = false;

	while (tengo != FICHA) {					// busco una ficha aleatoria en el tablero
		i = rand() % (DIM);
		j = rand() % (DIM);
		tengo = juego.tablero[i][j];
	}

	while (ok == false) {				// busco dirección aleatoria valida

		aleatorio = rand() % 4;
		direccion = tDireccion(aleatorio);

		if (direccion == ARRIBA && juego.tablero[i - 2][j] != NULA) {
			ok = false;
		}
		if (direccion == ABAJO && juego.tablero[i + 2][j] != NULA) {
			ok = false;
		}
		if (direccion == IZQUIERDA && juego.tablero[i][j - 2] != NULA) {
			ok = false;
		}
		if (direccion == DERECHA && juego.tablero[i][j + 2] != NULA) {
			ok = false;
		}
		if ((direccion == ARRIBA && juego.tablero[i - 2][j] != NULA) &&				// caso que no existe movimiento inverso posible
			(direccion == ABAJO && juego.tablero[i + 2][j] != NULA) &&
			(direccion == IZQUIERDA && juego.tablero[i][j - 2] != NULA) &&
			(direccion == DERECHA && juego.tablero[i][j + 2] != NULA)) {

			ok = true;
			inverso = false;
		}
		else {
			if ((direccion == ARRIBA && juego.tablero[i - 2][j] == (NULA)) ||		// caso que existe movimiento inverso posible
				(direccion == ABAJO && juego.tablero[i + 2][j] == (NULA)) ||
				(direccion == IZQUIERDA && juego.tablero[i][j - 2] == (NULA)) ||
				(direccion == DERECHA && juego.tablero[i][j + 2] == (NULA))) {
				ok = true;
			}
		}
	}

	if (ok == true && inverso == true) {					// crea las dos fichas en la direccion aleatoria y deja vacia la ficha del movimiento
		if (direccion == ARRIBA) {
			juego.tablero[i - 1][j] = FICHA;
			juego.tablero[i - 2][j] = FICHA;
		}
		if (direccion == ABAJO) {
			juego.tablero[i + 1][j] = FICHA;
			juego.tablero[i + 2][j] = FICHA;
		}
		if (direccion == IZQUIERDA) {
			juego.tablero[i][j - 1] = FICHA;
			juego.tablero[i][j - 2] = FICHA;
		}
		if (direccion == DERECHA) {
			juego.tablero[i][j + 1] = FICHA;
			juego.tablero[i][j + 2] = FICHA;
		}

		juego.tablero[i][j] = VACIA;

	}

	return inverso;

}
