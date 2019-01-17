// RAMON CALABOZO
// JAIME PALAZON
#include "Gestor.h"
#include <iostream>
using namespace std;
void generarAccesos(tGestor & gestor);
bool comprobarTurnoUsuario(const tGestor & gestor, int & pos);//comprueba si es el turno del usuario

bool iniciar(tGestor & gestor, const string & ficheroUsu, const string & ficheroPar){ // OK
	bool iniciar;
	bool ok1;
	bool ok2;
	ifstream archivoI;
	ifstream archivoII;

	archivoI.open("partidas.txt");
	if (archivoI.is_open()){
		ok1 = cargar(gestor.partidasSistema, archivoI);
		archivoI.close();
	}
	else{
		ok1 = false;
	}
	//usuarios

	archivoII.open("usuarios.txt");
	if (archivoII.is_open()){
		ok2 = cargar(gestor.usuariosSistema, archivoII);
		archivoII.close();
	}
	else{
		ok2 = false;
	}
	if (ok1 == true && ok2 == true){
		iniciar = true;
	}
	else{
		iniciar = false;
	}

	generarAccesos(gestor);
	return iniciar;
}
void generarAccesos(tGestor & gestor){       //
	for (int cont = 0; cont < MAX_PAR_USU; cont++){
		gestor.usuariosSistema.usuario[cont].partidasEnJuego.contador = 0;
	}
	for (int a = 0; a < MAX_USU; a++){
		for (int i = 0; i < gestor.partidasSistema.contador; i++){
			if (gestor.usuariosSistema.usuario[a].nombreUsuario == gestor.partidasSistema.partida[i].jugador1 || gestor.usuariosSistema.usuario[a].nombreUsuario == gestor.partidasSistema.partida[i].jugador2){
				if (gestor.partidasSistema.partida[i].estadopartida == EnCurso){
					gestor.usuariosSistema.usuario[a].partidasEnJuego.accesopartidas[gestor.usuariosSistema.usuario[a].partidasEnJuego.contador].Enlace = i;
					gestor.usuariosSistema.usuario[a].partidasEnJuego.accesopartidas[gestor.usuariosSistema.usuario[a].partidasEnJuego.contador].Identificador = gestor.partidasSistema.partida[a].unico;
					gestor.usuariosSistema.usuario[a].partidasEnJuego.contador++;
				}

			}
		}

	}
}
void cerrar(tGestor & gestor, const string & ficheroUsu, const string & ficheroPar){//OK
	ofstream archivoO;
	ofstream archivoOO;
	archivoO.open("partidas.txt");
	if (archivoO.is_open()){
		guardar(gestor.partidasSistema, archivoO);
	}
	archivoO.close();
	//usuarios
	archivoOO.open("usuarios.txt");
	if (archivoOO.is_open()){
		guardar(gestor.usuariosSistema, archivoOO);
	}
	archivoOO.close();
}
//Funciones del menú registro del main:



bool iniciarSesion(tGestor & gestor, const string & idUsu, const string & clave){//OK
	int posicion;
	bool ok, inicio;
	ok = buscar(gestor.usuariosSistema, idUsu, posicion);
	if (ok == true){
		if (iniciarSesion(gestor.usuariosSistema.usuario[posicion], clave)){
			gestor.contUsu = posicion;
			inicio = true;
		}
		else {
			inicio = false;
		}
	}
	else {
		inicio = false;
	}
	return inicio;
}

bool crearCuenta(tGestor & gestor, const string & idUsu, const string & clave){//ok
	tUsuario usuario;
	int posicion;
	bool ok, crea;
	iniciar(usuario, idUsu, clave);
	ok = buscar(gestor.usuariosSistema, usuario.nombreUsuario, posicion);
	if (ok == false){
		insertar(gestor.usuariosSistema, usuario, posicion);
		crea = true;
	}
	else if (ok == true){
		crea = false;
	}

	return crea;
}

bool tieneAvisos(const tGestor & gestor, string & aviso){//ok
	bool ok = false;
	if (gestor.usuariosSistema.usuario[gestor.contUsu].avisos != ""){
		aviso = gestor.usuariosSistema.usuario[gestor.contUsu].avisos;
		ok = true;
	}
	return ok;
}

void limpiarAvisos(tGestor & gestor){//ok
	limpiarAvisos(gestor.usuariosSistema.usuario[gestor.contUsu]);
}

string resumenActividad(const tGestor & gestor){//ok
	string resumen;
	int ganadas = gestor.usuariosSistema.usuario[gestor.contUsu].ganadasU;
	int perdidas = gestor.usuariosSistema.usuario[gestor.contUsu].perdidasU;
	int empatadas = gestor.usuariosSistema.usuario[gestor.contUsu].empatadasU;
	tNivel niveles = gestor.usuariosSistema.usuario[gestor.contUsu].nivelUsuario;

	int racha = gestor.usuariosSistema.usuario[gestor.contUsu].rachaUsuario;
	ostringstream flujo;
	cout << endl;
	flujo << "Resumen de actividad " << endl << "Partidas ganadas : " << ganadas << endl << "Partidas perdidas : " << perdidas << endl
		<< "Partidas empatadas : " << empatadas << endl << "Nivel actual : ";
	switch (niveles){
	case PRINCIPIANTE: flujo << "Principiante"; break;
	case MEDIO: flujo << " Medio "; break;
	case EXPERTO:flujo << " Experto"; break;
	}
	flujo << endl << "Racha actual : " << racha << endl << endl;
	resumen = flujo.str();
	return resumen;
}
//Funciones del menú usuario del main:

void ordenar_Fecha(tGestor & gestor){ //Hay que comprobar que funciona bien esta funcion
	bool inter = true;
	int i = 0;
	while ((i <MAX_PAR_USU - 1) && inter) {
		inter = false;
		for (int j = MAX_PAR_USU - 1; j > i; j--) {
			if (gestor.partidasSistema.partida[j].ultimaactualizacion > gestor.partidasSistema.partida[j - 1].ultimaactualizacion)
			{
				tPartida partida;
				partida = gestor.partidasSistema.partida[j];
				gestor.partidasSistema.partida[j] = gestor.partidasSistema.partida[j - 1];
				gestor.partidasSistema.partida[j - 1] = partida;
				inter = true;
			}
		}
		if (inter) { i++; }
	}
}


void ordenar_Turno(tGestor & gestor){ // Hay que comprobar que funciona bien esta funcion
	tPartida nuevo;
	int pos;
	for (int i = 0; i < gestor.partidasSistema.contador; i++) {
		nuevo = gestor.partidasSistema.partida[i];
		pos = 0;
		while ((pos < i) && comprobarTurnoUsuario(gestor, pos)){
			pos++;
		}
		for (int j = i; j > pos; j--) {
			gestor.partidasSistema.partida[j] = gestor.partidasSistema.partida[j - 1];
		}
		gestor.partidasSistema.partida[pos] = nuevo;
	}
}

bool comprobarTurnoUsuario(const tGestor & gestor, int & pos){
	bool LeTocaJugar = false;
	switch (gestor.partidasSistema.partida[pos].estadoconecta4.turno)
	{
	case 12:if (gestor.partidasSistema.partida[pos].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
				LeTocaJugar = true;
	} break;
	case 10:if (gestor.partidasSistema.partida[pos].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
				LeTocaJugar = true;
	} break;
	case 0: break;
	}

	return LeTocaJugar;

}



int partidasUsuario(const tGestor & gestor){ // ok
	return gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador;
}


string cabecera(const tGestor & gestor, int posEnCurso){//Funciona bien pero a veces se descuadra
	string cabecera;
	ostringstream flujo;
	bool hora = true;
	if (esSuTurno2(gestor, posEnCurso) == true){
		if (gestor.partidasSistema.partida[posEnCurso].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
			flujo << "  * " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario << "                   " << gestor.partidasSistema.partida[posEnCurso].jugador2;//ya funciona
		}
		else {
			flujo << "    " << gestor.partidasSistema.partida[posEnCurso].jugador1 << "                * " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario;
		}
	}
	else{
		if (gestor.partidasSistema.partida[posEnCurso].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
			flujo << "    " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario << "                 * " << gestor.partidasSistema.partida[posEnCurso].jugador2;//ya funciona
		}
		else{
			flujo << "  * " << gestor.partidasSistema.partida[posEnCurso].jugador1 << "                   " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario;//ya funciona
		}
	}

	flujo << "                " << stringFecha(gestor.partidasSistema.partida[posEnCurso].ultimaactualizacion, hora);
	return cabecera = flujo.str();
}



bool nuevaPartida(tGestor & gestor){//Así ya funciona pero sería mejor insertarlo con la función insertar
	bool ok = false, busca;
	int posicion;
	string idUser;
	tPartida nuevaPartida;
	if (gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador < MAX_PAR_US){
		if (gestor.usuariosSistema.usuario[gestor.contUsu].espera == false){
			//insertar(tListaAccesoPartidas & lista, tParIdEn par);//añadir bien
			//insertar(gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego,);
			busca = buscarUsuarioEsperando(gestor.usuariosSistema, gestor.usuariosSistema.usuario[gestor.contUsu].nivelUsuario, posicion);
			if (busca == true){
				gestor.partidasSistema.contador++;
				nueva(nuevaPartida, gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario, gestor.usuariosSistema.usuario[posicion].nombreUsuario);
				gestor.partidasSistema.partida[gestor.partidasSistema.contador - 1] = nuevaPartida;//inserta la partida en la lista de partidas,pero está no sería la manera correcta
				gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador++;

				if (gestor.partidasSistema.partida[gestor.partidasSistema.contador - 1].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
					idUser = gestor.partidasSistema.partida[gestor.partidasSistema.contador - 1].jugador2;
					buscar(gestor.usuariosSistema, idUser, posicion);
				}
				else{
					idUser = gestor.partidasSistema.partida[gestor.partidasSistema.contador - 1].jugador1;
					buscar(gestor.usuariosSistema, idUser, posicion);
				}
				gestor.usuariosSistema.usuario[posicion].partidasEnJuego.contador++;
				gestor.usuariosSistema.usuario[posicion].espera = false;
				ok = true;
			}
			else {
				gestor.usuariosSistema.usuario[gestor.contUsu].espera = true;
				cout << endl << endl;
				cout << " Se ha puesto en espera a que haya un oponente de su mismo nivel buscando una partida " << endl << endl;
			}
		}
		else {
			cout << " Recuerda que está en espera de crear una nueva partida" << endl << endl;
			cout << " No se ha podido crear una nueva partida " << endl << endl;
		}
	}
	else {
		cout << " NO puede crear más partidas " << endl << endl;
	}
	return ok;
}


void apuntaPartida(tGestor & gestor, int posParEnCurso){// meterlo cadavez que el usario meta una partida
	bool encontrado = false;
	int numero = 0;
	int i = 0;
	int partidaElegida = partidasUsuario(gestor);
	while (!encontrado && i < MAX_PAR_USU){
		if (gestor.partidasSistema.partida[i].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario || gestor.partidasSistema.partida[i].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
			if (gestor.partidasSistema.partida[i].estadopartida == EnCurso){
				gestor.contListaPartida = i;
				numero++;
			}
		}
		if (numero == posParEnCurso){
			encontrado = true;
		}
		i++;
	}
}
// funciones del menu partida del main


void mostrarPartida(const tGestor & gestor){//ok
	mostrar(gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4, gestor.partidasSistema.partida[gestor.contListaPartida].jugador1, gestor.partidasSistema.partida[gestor.contListaPartida].jugador2);
}


/*bool esSuTurno(const tGestor & gestor){//ok
bool turno;
if (gestor.partidasSistema.partida[gestor.contListaPartida].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
if (gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4.turno == Jugador1){
turno = true;
}
}
else if (gestor.partidasSistema.partida[gestor.contListaPartida].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
if (gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4.turno == Jugador2){
turno = true;
}
else {
turno = false;
}

}
return turno;
}
*/




void jugarPartida(tGestor & gestor, int col){//Repito codigo que podría hacerse una sola vez en vez de dos veces
	int pos;
	bool hora = true;
	tResultado resultado;
	string idUser;
	tUsuario usu;
	string aviso;
	ostringstream flujo;
	flujo.str("");
	aplicarJugada(gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4, col);
	gestor.partidasSistema.partida[gestor.contListaPartida].ultimaactualizacion = fechaActual();

	if (gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4.estado == Bloqueo){
		resultado = empata;
		flujo << " Ha empatado con " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario;
		flujo << " el ";
		flujo << stringFecha(gestor.partidasSistema.partida[gestor.contListaPartida].ultimaactualizacion, hora);
		aviso = flujo.str();
		gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador--;

		if (gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario == gestor.partidasSistema.partida[gestor.contListaPartida].jugador1){
			idUser = gestor.partidasSistema.partida[gestor.contListaPartida].jugador2;
			buscar(gestor.usuariosSistema, idUser, pos);
			gestor.usuariosSistema.usuario[pos].partidasEnJuego.contador--;
			gestor.usuariosSistema.usuario[pos].empatadasU++;
			gestor.usuariosSistema.usuario[pos].rachaUsuario = 0;
		}
		else{
			idUser = gestor.partidasSistema.partida[gestor.contListaPartida].jugador1;
			buscar(gestor.usuariosSistema, idUser, pos);
			gestor.usuariosSistema.usuario[pos].partidasEnJuego.contador--;
			gestor.usuariosSistema.usuario[pos].empatadasU++;
			gestor.usuariosSistema.usuario[pos].rachaUsuario = 0;
		}
		actualizarAvisos(gestor.usuariosSistema.usuario[pos], aviso);
		aplicarFinPartida(gestor.usuariosSistema.usuario[gestor.contUsu], gestor.partidasSistema.partida[gestor.contListaPartida].unico, resultado);
		gestor.partidasSistema.partida[gestor.contListaPartida].estadopartida = Terminada;
	}

	else if (gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4.estado == Ganador){
		resultado = Gana;
		flujo << " Ha  perdido contra " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario << " ";
		flujo << " el ";
		flujo << stringFecha(gestor.partidasSistema.partida[gestor.contListaPartida].ultimaactualizacion, hora);
		aviso = flujo.str();
		gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador--;

		if (gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario == gestor.partidasSistema.partida[gestor.contListaPartida].jugador1){
			idUser = gestor.partidasSistema.partida[gestor.contListaPartida].jugador2;
			buscar(gestor.usuariosSistema, idUser, pos);
			gestor.usuariosSistema.usuario[pos].partidasEnJuego.contador--;
			gestor.usuariosSistema.usuario[pos].perdidasU++;
			gestor.usuariosSistema.usuario[pos].rachaUsuario = -1;
		}
		else{
			idUser = gestor.partidasSistema.partida[gestor.contListaPartida].jugador1;
			buscar(gestor.usuariosSistema, idUser, pos);
			gestor.usuariosSistema.usuario[pos].partidasEnJuego.contador--;
			gestor.usuariosSistema.usuario[pos].perdidasU++;
			gestor.usuariosSistema.usuario[pos].rachaUsuario = -1;
		}
		actualizarAvisos(gestor.usuariosSistema.usuario[pos], aviso);
		aplicarFinPartida(gestor.usuariosSistema.usuario[gestor.contUsu], gestor.partidasSistema.partida[gestor.contListaPartida].unico, resultado);
		gestor.partidasSistema.partida[gestor.contListaPartida].estadopartida = Terminada;
	}
}


void abandonarPartida(tGestor & gestor){
	abandonar(gestor.partidasSistema.partida[gestor.contListaPartida]);
	cout << " ha decidido abandonar está partida " << endl << endl;
}



bool esSuTurno2(tGestor gestor, int posEnCurso){
	bool turno;
	if (gestor.partidasSistema.partida[posEnCurso].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
		if (gestor.partidasSistema.partida[posEnCurso].estadoconecta4.turno == Jugador1){
			turno = true;
		}
		else {
			turno = false;
		}
	}
	else if (gestor.partidasSistema.partida[posEnCurso].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){

		if (gestor.partidasSistema.partida[posEnCurso].estadoconecta4.turno == Jugador2){
			turno = true;
		}

		else {
			turno = false;
		}
	}
	return turno;
}
