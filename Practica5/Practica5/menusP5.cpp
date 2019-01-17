//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#include"menusP5.h"

//int main(){
//	tGestor gestor;
//	int col;
//	menuRegistro(gestor);
//	mostrarDatosUsu(gestor);
//	menuUsuario(gestor);
//	mostrarPartidasEnCurso(gestor);
//	elegirPartida(gestor);
//	menuPartida(gestor);
//	leerJugada(col);
//}

bool AccederMiCuenta(tGestor & gestor);
bool Registrarse(tGestor & gestor);
void jugar(tGestor & gestor);
void leerJugada(int & col);
void elegirPartida(tGestor & gestor, char & op3);
void mostrarDatosUsu(tGestor & gestor);
void mostrarPartidasEnCurso(tGestor & gestor);

void menuRegistro(tGestor & gestor, char & op1){
	bool menu = false;/*para saber si se ha registrado correctamente*/
	while (menu == false){
		cout << "MENU REGISTRO" << '\n';
		cout << "   1-Acceder a mi cuenta." << '\n';
		cout << "   2-Registrarse." << '\n';
		cout << "   0-Salir." << '\n';
		cout << "Elija una opcion: ";
		cin >> op1;
		cout << '\n';
		while (op1 != '1' && op1 != '2' && op1 != '0'){
			cout << "te has equivocado, vuelve a introducirlo: ";
			cin >> op1;
			cout << '\n';
		}
		switch (op1)
		{
		case '1':if (AccederMiCuenta(gestor) == false){ menu = false; cout << "Usuario o contraseña INCORRECTOS. :(" << '\n'; }
				 else{ menu = true; cout << "Has abierto correctamente una nueva sesion. :)" << '\n'; }break;
		case '2':if (Registrarse(gestor) == false){ menu = false; cout << "No puedes registrarte la  lista de usuarios esta llena o ya existe un usuario con ese nombre."; }
				 else{ menu = true; cout << "Te has registrado correctamente. :D "; }; break;
		case '0':return; break;
		}
	}
}
bool AccederMiCuenta(tGestor & gestor){
	string idUsu;
	string clave;
	cout << "================================================================================";
	cout << "ACCESO A MI CUENTA" << '\n';
	cout << "   -Nombre usuario: ";
	cin >> idUsu;
	cout << '\n';
	cout << "   -Contraseña: ";
	cin >> clave;
	cout << "================================================================================" << '\n';
	return iniciarSesion(gestor, idUsu, clave);
}
bool Registrarse(tGestor & gestor){
	bool registrarse = false;
	string idUsu;
	string clave;
	cout << "REGISTRO" << '\n';
	cout << "   -Nombre de usuario: ";
	cin >> idUsu;
	cout << '\n';
	cout << "   -Contraseña: ";
	cin >> clave;
	cout << '\n';
	if (crearCuenta(gestor, idUsu, clave) == true){
		registrarse = iniciarSesion(gestor, idUsu, clave);
	}

	return registrarse;
}

void mostrarDatosUsu(tGestor & gestor){
	if (gestor.usuarios.Usuario[gestor.Usuariosesión].avisos != ""){
		cout << '\n';
		cout << "Tiene avisos:" << '\n';
		cout << gestor.usuarios.Usuario[gestor.Usuariosesión].avisos;
		char opcion;
		cout << "desea borrar los avisos <S/N> ?: ";
		cin >> opcion;
		if (opcion == 's' || opcion == 'S'){ limpiarAvisos(gestor); }
	}
	else{ cout << "No tiene avisos." << '\n'; }
	cout << '\n' << '\n';
	cout << "Resumen actividad:" << '\n';
	cout << resumenActividad(gestor);
}


void menuUsuario(tGestor & gestor, char & op2){
	nuevoAdversario(gestor.ListaAdversarios, gestor.Usuariosesión);/*me salia un error muy raro y he tenidoque poner la funcion aquidentro*/

	/*se crea su nueva lista de Adversarios si no tenia*/
	generarAccesos(gestor);
	/*el orden se genera despues de generar los accesos*/
	if (op2 == '3'){
		ordenar_Fecha(gestor);
	}
	if (op2 == '4'){
		ordenar_Turno(gestor);
	}
	mostrarDatosUsu(gestor);
	cout << "MENU USUARIO" << '\n';
	cout << '\n' << '\n';
	cout << "#  T  Jugador1          Jugador2          Fecha" << '\n';
	cout << "-------------------------------------------------" << '\n';
	mostrarPartidasEnCurso(gestor);
	cout << '\n' << '\n';
	cout << "   1-Ver partida." << '\n';
	cout << "   2-Nueva partida." << '\n';
	cout << "   3-Partidas por actualizacion." << '\n';
	cout << "   4-Partida por turno y ultima actualizacion." << '\n';
	cout << "   5-Mostrar datos por adversario," << '\n';
	cout << "   0-Salir." << '\n' << '\n';
	cout << "Elija una opcion: ";
	cin >> op2;
	while (op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4' && op2 != '5' && op2 != '0'){
		cout << "Has introducido mal el numero, vuelve a introducirlo: ";
		cin >> op2;
	}
	cout << '\n';
	int pos = 0;
	switch (op2)
	{
	case '1':elegirPartida(gestor, op2); break;
	case '2':nuevaPartida(gestor); break;
	case '3':break;
	case '4':break;
	case '5':
		mostrarDatosAdversarios(gestor.ListaAdversarios.Adversarios[gestor.Usuariosesión], pos);
		system("PAUSE");
		break;
	case '0':return; break;
	}
}
void mostrarPartidasEnCurso(tGestor & gestor){
	int posEnCurso = 0;
	while (posEnCurso < gestor.ListaAccesoPartidas.contador){
		cout << cabecera(gestor, posEnCurso);
		cout << '\n';
		posEnCurso++;
	}
}
void elegirPartida(tGestor & gestor, char & op2){
	int posParEnCurso;
	cout << "Elija una partida <0 para salir>: ";
	cin >> posParEnCurso;
	if (posParEnCurso == 0){ op2 = 'x'; return; }
	else{
		posParEnCurso--;/*para que sea la misma posicion del array*/
		apuntaPartida(gestor, posParEnCurso);
	}
}

void menuPartida(tGestor & gestor, char & op3){
	mostrarPartida(gestor);
	cout << "MENU PARTIDA" << '\n';
	if (esSuTurno(gestor) == true && gestor.puntPartidaSeleccionada->EstadoPartida == EnCurso){
		cout << "  1-Jugar." << '\n';
	}
	if (gestor.puntPartidaSeleccionada->EstadoPartida == EnCurso){
		cout << "  2-Abandonar." << '\n';
	}
	cout << "  0-Salir." << '\n';
	cin >> op3;
	while (op3 != '1' && op3 != '2' && op3 != '0'){
		cout << "Has introducido mal el numero, vuelve a introducirlo: ";
		cin >> op3;
	}
	cout << '\n';
	switch (op3)
	{
	case '1':jugar(gestor); break;
	case '2':abandonarPartida(gestor); break;
	case '0':return; break;
	}
}
void jugar(tGestor & gestor){
	int col;
	leerJugada(col);
	jugarPartida(gestor, col);
	mostrarPartida(gestor);
}

void leerJugada(int & col){
	cout << "Elija una columna del 1 al 7: ";
	cin >> col;
	cout << '\n';
	while (col < 1 || col > 7){
		cout << "Elija una columna correcta: ";
		cin >> col;
	}
	col--; /*para coincidir con el array*/
}

