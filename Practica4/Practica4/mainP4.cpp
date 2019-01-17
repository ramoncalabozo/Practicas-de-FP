// RAMON CALABOZO
// JAIME PALAZON
#include <iostream>
#include "Gestor.h"
#include <string>
using namespace std;
const string F_USUARIOS = "usuarios.txt";
const string F_PARTIDAS = "partidas.txt";
// Prototipos de las Funciones
void menuRegistro(tGestor & gestor);//Muestra y gestiona el menú inicial de la aplicación
void mostrarDatosUsu(tGestor & gestor);// Si el usuario de la sesión tiene avisos, losmuestra y pregunta si quiere eliminarlos. Y a continuación muestra su resumen de actividad 
void menuUsuario(tGestor & gestor);//Muestra y gestiona el menú principal de una sesión de usuario
void mostrarPartidasEnCurso(tGestor & gestor);//: Muestra las cabeceras de cada una de las partidas en curso del usuario de la sesión.
void elegirPartida(tGestor & gestor, int & posParEnCurso);//Solicita un número válido de partida (de entre la lista mostrada), y lo apunta como partida seleccionada del usuario de la sesión.
void menuPartida(tGestor & gestor);//Muestra y gestiona el menú de una partida
void leerJugada(int & col);//solicita y devuelve una columna válida.

int main(){//esta parte funciona
	tGestor gestor;
	string ficheroUsu = F_USUARIOS;
	string ficheroPar = F_PARTIDAS;
	if (iniciar(gestor, ficheroUsu, ficheroPar)){
		cout << "Se ha cargado con exito " << endl;
	}
	menuRegistro(gestor);
	cerrar(gestor, ficheroUsu, ficheroPar);
	return 0;
}

//Funciones
void menuRegistro(tGestor & gestor){//OK
	int opcion;
	string idUsu;
	string clave;
	ordenar_Fecha(gestor);//Esto se me ordena las partidas para que salgan en el orden que nos interesa (se actualiza cada vez que un usuario quiere entrar)
	do {
		cout << endl << endl;
		cout << " MENU REGISTRO " << endl;
		cout << "  1.Acceder a mi cuenta " << endl;
		cout << "  2.Registrarse " << endl;
		cout << "  0.Salir" << endl;
		cout << "  Elige una opcion : ";
		cin >> opcion;
	} while (opcion < 0 || opcion > 2);
	if (opcion == 1){
		cout << endl << endl;
		cout << "ACCESO" << endl;
		cout << "  Usuario : ";
		cin >> idUsu;
		cout << " Contraseña : ";
		cin >> clave;
		if (iniciarSesion(gestor, idUsu, clave)){
			cout << endl << endl;
			cout << " Ha abierto correctamente una nueva sesion " << endl << endl;
			cout << endl << endl;
			mostrarDatosUsu(gestor);
			menuUsuario(gestor);
		}
		else {
			cout << endl << endl;
			cout << " Nombre o clave INCORRECTOS" << endl << endl;
			cout << endl << endl;
		}
		menuRegistro(gestor);
	}
	else if (opcion == 2){
		cout << endl << endl;
		if (gestor.usuariosSistema.cont == MAX_USU){
			cout << " Lo sentimos no se puede registrar porque el cupo de usuarios esta completo " << endl << endl;
			//	menuRegistro(gestor);
		}
		else{
			cout << " REGISTRO" << endl;
			cout << " Nombre de Usuario : ";
			cin >> idUsu;
			cout << " Clave : ";
			cin >> clave;
			if (crearCuenta(gestor, idUsu, clave)){
				cout << endl << endl;
				cout << " Registro correcto, se ha abierto una sesion " << endl << endl;
				cout << " Su nivel actual es de Principiante" << endl;
				iniciarSesion(gestor, idUsu, clave);
				mostrarDatosUsu(gestor);
				menuUsuario(gestor);
			}
			else {
				cout << endl << endl;
				cout << "ERROR ese nombre ya existe " << endl << endl;
				cout << endl << endl;
			}
		}
		menuRegistro(gestor);
	}
}
void mostrarDatosUsu(tGestor & gestor){//OK
	char opcion;
	string aviso;
	string resumen;
	if (tieneAvisos(gestor, aviso) == true){
		cout << "Tiene avisos : " << endl;
		cout << aviso << endl << endl;
		do {
			cout << "¿Quieres eliminiar los avisos?<S/N> " << endl;
			cin >> opcion;
			cout << endl << endl << endl;
		} while (opcion != 'S' && opcion != 's' && opcion != 'N' && opcion != 'n');
		if (opcion == 'S' || opcion == 's'){
			limpiarAvisos(gestor);
		}
	}
	resumen = resumenActividad(gestor);
	cout << resumen << endl;
}


void menuUsuario(tGestor & gestor){
	bool ok = false;
	int opcion;
	do {
		cout << " MENU USUARIO " << endl << endl;
		cout << "#   T  Jugador1             Jugador2                 Fecha               " << endl;
		cout << " ---------------------------------------------------------------------------" << endl;
		mostrarPartidasEnCurso(gestor);
		do {
			cout << "  1.Ver partida " << endl;
			cout << "  2.Nueva partida " << endl;
			cout << "  3.Partidas por actualizacion " << endl;
			cout << "  4.Partidas por turnno y fecha " << endl;
			cout << "  0.Salir " << endl << endl;
			cout << " Elige una opcion : ";
			cin >> opcion;
			cout << endl;
		} while (opcion  < 0 || opcion > 4);
		//int partidaB;
		if (opcion == 1){
			int posParEnCurso;
			/*	do{
			cout << endl << endl;
			cout << " Indique la partida que quiere ver ";
			cin >> partidaB;
			cout << endl << endl;
			//ESTO HAY QUE CAMBIARLO PARA QUE LO HAGA CON LA FUNCION elegirPartida (gestor);
			} while (partidaB < 0 || partidaB >= gestor.partidasSistema.contador && gestor.partidasSistema.partida[partidaB].estadopartida == EnCurso);
			gestor.contListaPartida = partidaB;
			if (gestor.partidasSistema.partida[partidaB].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario || gestor.partidasSistema.partida[partidaB].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
			if (gestor.partidasSistema.partida[partidaB].estadopartida == EnCurso){
			ok = true;
			}
			else {
			ok = false;
			}
			}
			//elegirPartida(gestor);
			if (ok == true){
			mostrar(gestor.partidasSistema.partida[partidaB].estadoconecta4,gestor.partidasSistema.partida[partidaB].jugador1,gestor.partidasSistema.partida[partidaB].jugador2);
			gestor.contListaPartida = partidaB;
			menuPartida(gestor);
			}
			else {
			cout << "Esa partida no la puede visualizar porque no está dentro de tus partidas abiertas " << endl << endl ;
			cout << endl << endl;
			}
			}
			*/
			elegirPartida(gestor, posParEnCurso);
			if (posParEnCurso != 0){
				mostrar(gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4, gestor.partidasSistema.partida[gestor.contListaPartida].jugador1, gestor.partidasSistema.partida[gestor.contListaPartida].jugador2);
				menuPartida(gestor);
			}
		}

		else if (opcion == 2){

			if (nuevaPartida(gestor)){
				cout << endl << endl;
				cout << " se ha iniciado una partida " << endl << endl;
				cout << endl << endl;
			}
			else {
				if (gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador > MAX_PAR_US){
					cout << endl << endl;
					cout << "No puedes crear mas partidas " << endl << endl;
					cout << endl << endl;
				}

			}
		}
		else if (opcion == 3){
			ordenar_Fecha(gestor);
		}

		else if (opcion == 4){
			ordenar_Turno(gestor);
		}

	} while (opcion != 0);
}

void mostrarPartidasEnCurso(tGestor & gestor){
	string cabezera;
	/*for (int i = 0; i < gestor.partidasSistema.contador; i++){
	if (gestor.partidasSistema.partida[i].estadopartida == EnCurso){
	if (gestor.partidasSistema.partida[i].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario ||gestor.partidasSistema.partida[i].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
	cabezera = cabecera(gestor, i);
	cout << i;
	cout << cabezera <<endl;
	}
	}
	}*/
	int contador = partidasUsuario(gestor);
	int i = 0;
	int orden = 0;
	while (orden < contador && i < gestor.partidasSistema.contador){
		if (gestor.partidasSistema.partida[i].estadopartida == EnCurso){
			if (gestor.partidasSistema.partida[i].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario || gestor.partidasSistema.partida[i].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario){
				cabezera = cabecera(gestor, i);
				cout << orden + 1;
				cout << cabezera << endl;
				orden++;
			}

		}

		i++;
	}
	cout << endl;
}

void elegirPartida(tGestor & gestor, int & posParEnCurso){
	bool ok = false;
	bool ok2 = false;
	do {
		//gestor.contListaPartida = opcion;
		cout << endl;
		cout << " Indique la partida que quiere ver , si quiere salir de esta opcion pulse 0 " << endl << endl;
		cin >> posParEnCurso;
		//apuntaPartida(gestor, posParEnCurso);
		if (posParEnCurso <= MAX_PAR_US && posParEnCurso > 0){
			int partidas = partidasUsuario(gestor);
			if (posParEnCurso <= partidas){
				apuntaPartida(gestor, posParEnCurso);
				if ((gestor.partidasSistema.partida[gestor.contListaPartida].jugador1 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario && gestor.partidasSistema.partida[gestor.contListaPartida].estadopartida == EnCurso) || (gestor.partidasSistema.partida[gestor.contListaPartida].jugador2 == gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario && gestor.partidasSistema.partida[posParEnCurso].estadopartida == EnCurso)){
					ok = true;
				}
				ok2 = true;
			}
			//cout << " Esa partida no se puede visualizar por que no está dentro de tus partidas abiertas " << endl;
		}
		else {
			if (posParEnCurso != 0){
				cout << " Esa partida no se puede visualizar por que no está dentro de tus partidas abiertas " << endl << endl;
			}
		}
		if (!ok2){
			cout << " No puedes seleccionar esa partida porque es mayor al numero de partidas que tiene abiertas " << endl << endl;
		}
	} while (/*gestor.partidasSistema.partida[gestor.contListaPartida].estadopartida == EnCurso &&*/ !ok && !ok2 && posParEnCurso != 0);
	//apuntaPartida(gestor, posParEnCurso);
}

void menuPartida(tGestor & gestor){
	int pos;
	string idUser;
	string aviso;
	ostringstream flujo;
	tUsuario usuario;
	int col;
	int opcion;
	bool hora = true;
	do{
		if (esSuTurno2(gestor, gestor.contListaPartida)){
			cout << " 1.Jugar " << endl;
		}
		cout << " 2.Abandonar " << endl;
		cout << " 0.Salir " << endl;
		cout << " Elige una opcion : ";
		cin >> opcion;
	} while (opcion < 0 || opcion > 2);

	if (opcion == 1){
		leerJugada(col);
		jugarPartida(gestor, col);
		mostrar(gestor.partidasSistema.partida[gestor.contListaPartida].estadoconecta4, gestor.partidasSistema.partida[gestor.contListaPartida].jugador1, gestor.partidasSistema.partida[gestor.contListaPartida].jugador2);
	}

	else if (opcion == 2){
		tResultado resultado = Pierde;
		abandonarPartida(gestor);
		aplicarFinPartida(gestor.usuariosSistema.usuario[gestor.contUsu], gestor.partidasSistema.partida[gestor.contListaPartida].unico, resultado);
		flujo << " Ha  Ganado por abandono una partida contra  " << gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario << " el  ";
		flujo << stringFecha(gestor.partidasSistema.partida[gestor.contListaPartida].ultimaactualizacion, hora);
		aviso = flujo.str();
		if (gestor.usuariosSistema.usuario[gestor.contUsu].nombreUsuario == gestor.partidasSistema.partida[gestor.contListaPartida].jugador1){
			idUser = gestor.partidasSistema.partida[gestor.contListaPartida].jugador2;
			buscar(gestor.usuariosSistema, idUser, pos);
			gestor.usuariosSistema.usuario[pos].partidasEnJuego.contador--;
		}
		else{
			idUser = gestor.partidasSistema.partida[gestor.contListaPartida].jugador1;
			buscar(gestor.usuariosSistema, idUser, pos);
			gestor.usuariosSistema.usuario[pos].partidasEnJuego.contador--;
		}
		actualizarAvisos(gestor.usuariosSistema.usuario[pos], aviso);
		resultado = Gana;
		aplicarFinPartida(gestor.usuariosSistema.usuario[pos], gestor.partidasSistema.partida[gestor.contListaPartida].unico, resultado);
		gestor.usuariosSistema.usuario[gestor.contUsu].partidasEnJuego.contador--;
	}

}

void leerJugada(int & col){
	do{
		cout << " Elija una columna entre (1 y 7) ambos incluidos ";
		cin >> col;
		col = col - 1;
	} while (col <0 || col>6);
}