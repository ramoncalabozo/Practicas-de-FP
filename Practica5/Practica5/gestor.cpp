//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  
#include"gestor.h"
//int main(){
//	tGestor gestor;
//	string ficheroUsu = "usuarios.txt";
//	string ficheroPar = "partidas.txt";
//	iniciar(gestor, ficheroUsu, ficheroPar);
//	/*cerrar(gestor, ficheroUsu, ficheroPar);*/
//	string idUsu = "marta";
//	string clave = "marta";
//	iniciarSesion(gestor, idUsu, clave);
//	crearCuenta(gestor, idUsu, clave);
//	string aviso;
//	tieneAvisos(gestor, aviso);
//	limpiarAvisos(gestor);
//	/*cout << resumenActividad(gestor);*/
//	/*ordenar_Fecha(gestor);*/
//	ordenar_Turno(gestor);
//	/*partidasUsuario(gestor);*/
//	int posParEnCurso = 0;
//	cout<<cabecera(gestor, posEnCurso);
//	nuevaPartida(gestor);
//	apuntaPartida(gestor, posParEnCurso);
//	mostrarPartida(gestor);
//	/*esSuTurno(gestor);*/
//	int col=3;
//	jugarPartida(gestor, col);
//	mostrarPartida(gestor);
//	abandonarPartida(gestor);
//}


void avisarContrincante(tListaUsuarios &usuarios, const string & idUser, const int & pos, tResultado & resultado);
bool buscarListaAcceso(tGestor & gestor, int & pos);
bool comprobarTurnoUsuario(const tListaAccesoPartidas & lista, int & pos, const string &nombreUsuario);
/*las nuevas funcionalidades*/
void TerminarPartidas30D(tGestor &gestor);
void guardarHistorico(tGestor &gestor, ofstream &flujo);

void actualizarDatos(tGestor & gestor, const string &idUser, const int &posCotrincante, tResultado &resultado);

bool iniciar(tGestor & gestor, const string & ficheroUsu, const string & ficheroPar){
	bool iniciar;

	ifstream flujo;
	flujo.open(ficheroPar);

	ifstream archivo;
	archivo.open(ficheroUsu);

	if (cargar(gestor.usuarios, archivo) == true && cargar(gestor.partidas, flujo) == true) {
		cargarListaAdversarios(gestor.ListaAdversarios, gestor.usuarios.capacidad, archivo);
		iniciar = true;
	}
	else{ iniciar = false; }
	return iniciar;

}

void generarAccesos(tGestor & gestor){
	iniciar(gestor.ListaAccesoPartidas);
	//buscamos partidas en curso del usuario
	for (int i = 0; i < gestor.partidas.contador; i++)
	{
		/*si esta en curso y uno de los dso jugadores es el, se inseta*/
		if (gestor.partidas.partida[i]->EstadoPartida == EnCurso && (gestor.partidas.partida[i]->jugador1 == gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre || gestor.partidas.partida[i]->jugador2 == gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre)){
			tParIdEn par;
			par.IdentificadorPartida = gestor.partidas.partida[i]->único;
			par.puntPartida = gestor.partidas.partida[i];
			insertar(gestor.ListaAccesoPartidas, par);
		}
	}
}

void cerrar(tGestor & gestor, const string & ficheroUsu, const string & ficheroPar){
	TerminarPartidas30D(gestor);

	ofstream archivo;
	archivo.open(ficheroUsu);
	if (archivo.is_open()){
		apagar(gestor.usuarios, archivo);
		apagarListaAdversarios(gestor.ListaAdversarios, archivo);
	}

	ofstream flujoHistorico;
	flujoHistorico.open("historico.txt", ios::app);/*lo abro por el final para guardar los nuevos datos*/
	if (flujoHistorico.is_open()){
		guardarHistorico(gestor, flujoHistorico);
	}

	ofstream flujo;
	flujo.open(ficheroPar);
	if (flujo.is_open()){
		apagar(gestor.partidas, flujo);

	}
	//gestor.puntPartidaSeleccionada = NULL;/*no hace falta en si ya que a lo que apunta ya es eliminado en apagar partida*/
	//delete gestor.puntPartidaSeleccionada;
}

void TerminarPartidas30D(tGestor &gestor){
	string UsuTurno;
	string UsuNoTurno;
	for (int i = 0; i < gestor.partidas.contador; i++)
	{
		/*el numero 2592000 es un mes en segundos, es decir,si la diferencia entre la fecha de la
		ultiama actualizacion y la actual es mayor a un mes se mete en el if. */
		if (fechaActual() - gestor.partidas.partida[i]->ultimaActualizacion >= 2592000 && gestor.partidas.partida[i]->EstadoPartida != Terminada){
			gestor.partidas.partida[i]->EstadoPartida = Terminada;
			switch (gestor.partidas.partida[i]->juego.turno)
			{
			case 12: UsuTurno = gestor.partidas.partida[i]->jugador1; UsuNoTurno = gestor.partidas.partida[i]->jugador2; break;
			case 10: UsuTurno = gestor.partidas.partida[i]->jugador2; UsuNoTurno = gestor.partidas.partida[i]->jugador1; break;
			case 0: break;
			}
			int pos = 0;
			tResultado resultado = Pierde;
			/*actualizamos datos del usuario del truno y avisamos al contrincante*/
			buscar(gestor.usuarios, UsuNoTurno, pos);
			actualizarDatos(gestor, UsuTurno, pos, resultado);
			/*actualizamos datos del usuario que no tiene truno y avisamos al contrincante*/
			buscar(gestor.usuarios, UsuTurno, pos);
			resultado = Gana;
			actualizarDatos(gestor, UsuNoTurno, pos, resultado);
		}
	}

}
void guardarHistorico(tGestor &gestor, ofstream &flujo){
	/*supongo que el objetivo de esta funcion es liberar espacio, por lo que las partidas
	terminadas las eliminare del array para no guardarlas en partidas.txt*/
	int cotadorParaNULL = gestor.partidas.contador;/*on esto memorizo donde estaba la ultima partida antes de borrarlo y asi llenar las partidas con basura con null*/

	for (int i = 0; i < gestor.partidas.contador; i++)
	{
		if (gestor.partidas.partida[i]->EstadoPartida == Terminada){
			guardar(gestor.partidas.partida[i], flujo);/*lo guardo en el historico*/
			delete gestor.partidas.partida[i];/*La borro*/
			gestor.partidas.partida[i] = NULL;/*para que luego no la guarde si esta vacia y de error*/
			gestor.partidas.contador--;/*decremento el contador*/
		}
	}
	for (int i = cotadorParaNULL + 1; i < MAX_PAR_USU; i++)
	{
		gestor.partidas.partida[i] = NULL;/*lo hago para que al guardar no de error*/
	}
}

void actualizarDatos(tGestor &gestor, const string &idUser, const int &posCotrincante, tResultado &resultado){
	int pos = 0;
	buscar(gestor.usuarios, idUser, pos);
	aplicarFinPartida(gestor.usuarios.Usuario[pos], resultado);
	/*se cambia al resultado contario para avisar al contrincante*/
	switch (resultado)
	{
	case 0:resultado = Pierde; break;
	case 1:resultado = Gana; break;
	}
	avisarContrincante(gestor.usuarios, idUser, posCotrincante, resultado);
	string aviso = "ya que han pasado mas de 30 dias .";
	actualizarAvisos(gestor.usuarios.Usuario[posCotrincante], aviso);
}

bool iniciarSesion(tGestor & gestor, const string & idUsu, const string & clave){
	string idUser;
	tListaUsuarios usuarios;
	int pos;
	idUser = idUsu;
	usuarios = gestor.usuarios;
	if (buscar(usuarios, idUser, pos) == false){ return false; }
	tUsuario Usuario;
	Usuario = gestor.usuarios.Usuario[pos];
	if (iniciarSesion(Usuario, clave) == true){
		gestor.Usuariosesión = pos;
		generarAccesos(gestor);
		return true;
	}
	else{ return false; }
}

bool crearCuenta(tGestor & gestor, const string & idUsu, const string & clave){
	tListaUsuarios usuarios;
	tUsuario Usuario;
	string pas = clave;
	string id = idUsu;
	string idUser = idUsu;
	int pos;/*es basura, solo vale para la funcion*/
	usuarios = gestor.usuarios;
	if (buscar(usuarios, idUser, pos) == false){
		iniciar(Usuario, id, pas);
		insertar(usuarios, Usuario);
		gestor.usuarios = usuarios;
		gestor.usuarios.contador++;
		return true;
	}
	else{ return false; }
}

bool tieneAvisos(const tGestor & gestor, string & aviso){
	if (gestor.usuarios.Usuario[gestor.Usuariosesión].avisos != ""){
		aviso = gestor.usuarios.Usuario[gestor.Usuariosesión].avisos;
		return true;
	}
	else{ return false; }
}

void limpiarAvisos(tGestor & gestor){
	tUsuario Usuario = gestor.usuarios.Usuario[gestor.Usuariosesión];
	limpiarAvisos(Usuario);
	gestor.usuarios.Usuario[gestor.Usuariosesión] = Usuario;
}

string resumenActividad(const tGestor & gestor){
	ostringstream actividad;
	actividad << "   -partidas ganada: " << gestor.usuarios.Usuario[gestor.Usuariosesión].NumeroPartidas.ganadas << '\n';
	actividad << "   -partidas perdidas: " << gestor.usuarios.Usuario[gestor.Usuariosesión].NumeroPartidas.perdidas << '\n';
	actividad << "   -partidas empatadas: " << gestor.usuarios.Usuario[gestor.Usuariosesión].NumeroPartidas.empatadas << '\n';
	actividad << "   -nivel actual: ";
	switch (gestor.usuarios.Usuario[gestor.Usuariosesión].nivelJuego)
	{
	case 0:actividad << "Principiante"; break;
	case 1:actividad << "Medio"; break;
	case 2:actividad << "Experto"; break;
	}actividad << '\n';
	actividad << "   -racha actual: ";
	actividad << gestor.usuarios.Usuario[gestor.Usuariosesión].racha << '\n';
	return actividad.str();
}

void ordenar_Fecha(tGestor & gestor){
	ordenar_Fecha(gestor.ListaAccesoPartidas);
}

void ordenar_Turno(tGestor & gestor){
	ordenar_Turno(gestor.ListaAccesoPartidas, gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre);
}
int partidasUsuario(const tGestor & gestor){
	int partidasUsuario = 0;
	for (int i = 0; i < MAX_PAR_USU; i++)
	{
		if (gestor.partidas.partida[i]->jugador1 == gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre || gestor.partidas.partida[i]->jugador2 == gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre){
			partidasUsuario++;
		}
	}
	return partidasUsuario;
}

string cabecera(const tGestor & gestor, int posEnCurso){
	ostringstream cabecera;

	/*posicion*/
	cabecera << posEnCurso + 1 << "  ";
	/*para el turno*/
	if (comprobarTurnoUsuario(gestor.ListaAccesoPartidas, posEnCurso, gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre) == true){ cabecera << '*'; }
	else{ cabecera << " "; }
	cabecera << "  ";
	cabecera << gestor.ListaAccesoPartidas.ParIdEn[posEnCurso].puntPartida->jugador1 << "             ";
	cabecera << gestor.ListaAccesoPartidas.ParIdEn[posEnCurso].puntPartida->jugador2 << "          ";
	/*la fecha*/
	tFecha fecha = gestor.ListaAccesoPartidas.ParIdEn[posEnCurso].puntPartida->ultimaActualizacion;
	cabecera << fechaHoraDias(fecha);
	return cabecera.str();
}
bool nuevaPartida(tGestor & gestor){
	bool encontrar = false;

	if (gestor.partidas.contador < MAX_PAR_USU && gestor.usuarios.Usuario[gestor.Usuariosesión].espera == false){
		int pos = 0;
		encontrar = buscarUsuarioEsperando(gestor.usuarios, gestor.usuarios.Usuario[gestor.Usuariosesión].nivelJuego, pos, gestor.Usuariosesión);
		if (encontrar == true){
			string jugador1 = gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre;
			string jugador2 = gestor.usuarios.Usuario[pos].Nombre;
			gestor.partidas.partida[gestor.partidas.contador] = new tPartida;
			nueva(gestor.partidas.partida[gestor.partidas.contador], jugador1, jugador2);
			gestor.partidas.partida[gestor.partidas.contador]->ultimaActualizacion = fechaActual();
			tParIdEn par;
			par.IdentificadorPartida = gestor.partidas.partida[gestor.partidas.contador]->único;
			par.puntPartida = gestor.partidas.partida[gestor.partidas.contador];
			insertar(gestor.ListaAccesoPartidas, par);/*inserta en lista acceso partida*/
			gestor.partidas.contador++;
		}
		else{
			gestor.usuarios.Usuario[gestor.Usuariosesión].espera = true;
			string aviso = "no se encontro a nadie con quien jugar, se te pondra en modo espera.";
			actualizarAvisos(gestor.usuarios.Usuario[gestor.Usuariosesión], aviso);
		}
	}
	else{
		string aviso = "no se pudo crear una nueva partida, la lista de partidas esta llena.";
		actualizarAvisos(gestor.usuarios.Usuario[gestor.Usuariosesión], aviso);
	}
	return encontrar;
}

void apuntaPartida(tGestor & gestor, int posParEnCurso){
	gestor.puntPartidaSeleccionada = gestor.ListaAccesoPartidas.ParIdEn[posParEnCurso].puntPartida;
}

void mostrarPartida(const tGestor & gestor){
	tConecta4 juego = gestor.puntPartidaSeleccionada->juego;
	string jugador1 = gestor.puntPartidaSeleccionada->jugador1;
	string jugador2 = gestor.puntPartidaSeleccionada->jugador2;
	mostrar(juego, jugador1, jugador2);
}

bool esSuTurno(const tGestor & gestor){
	bool LeTocaJugar = false;

	/*comprobamos si al esuario le toca o no mover ficha*/
	switch (gestor.puntPartidaSeleccionada->juego.turno)
	{
	case 12:if (gestor.puntPartidaSeleccionada->jugador1 == gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre){ LeTocaJugar = true; }break;
	case 10:if (gestor.puntPartidaSeleccionada->jugador2 == gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre){ LeTocaJugar = true; }break;
	case 0: break;
	}

	return LeTocaJugar;

}

void jugarPartida(tGestor & gestor, int col){
	aplicarJugada(gestor.puntPartidaSeleccionada, col);
	/*fecha ultima*/
	gestor.puntPartidaSeleccionada->ultimaActualizacion = fechaActual();

	int pos;
	string idUserGana;
	string idUserPierde;
	tResultado resultado1; tResultado resultado2;/*un resultado por persona*/
	bool jugando = false;
	switch (gestor.puntPartidaSeleccionada->juego.estado)
	{
	case 0:jugando = true; break;
	case 1:resultado1 = Gana; resultado2 = Pierde; break;
	case 2:resultado1 = Empata; resultado2 = Empata; break;
	}
	if (jugando == false){
		if (gestor.puntPartidaSeleccionada->juego.turno == Jugador1){
			idUserPierde = gestor.puntPartidaSeleccionada->jugador2;/* si gana y el turno es del jugador 1, pierde el jugador 2*/
			idUserGana = gestor.puntPartidaSeleccionada->jugador1;/*aparte ya sabemos quien inicio sesion*/
		}
		else{
			idUserGana = gestor.puntPartidaSeleccionada->jugador2;/* si gana y el turno es del jugador 2, pierde el jugador 1*/
			idUserPierde = gestor.puntPartidaSeleccionada->jugador1;
		}

		buscar(gestor.usuarios, idUserGana, pos);/* buscamos la jugador en la lista*/
		aplicarFinPartida(gestor.usuarios.Usuario[pos], resultado1);/* cambiamos los datos del jugador ganador o empato*/
		/*actualizarListaAdversarios(gestor.ListaAdversarios, idUserPierde, resultado1, pos)*/;

		buscar(gestor.usuarios, idUserPierde, pos);/* buscamos la jugador perdedor en la lista*/
		aplicarFinPartida(gestor.usuarios.Usuario[pos], resultado2);/* cambiamos los datos del jugador*/
		avisarContrincante(gestor.usuarios, idUserGana, pos, resultado2);
		/*actualizarListaAdversarios(gestor.ListaAdversarios, idUserGana, resultado2, pos);*/

	}
}

void avisarContrincante(tListaUsuarios &usuarios, const string & idUser, const int & pos, tResultado &resultado){
	ostringstream avisoFlujo;
	string aviso;
	tFecha fecha = fechaActual();
	//avisar la jugador
	switch (resultado)
	{
	case 0:avisoFlujo << "has ganado la partida contra " << idUser << " el dia " << fechaHoraDias(fecha) << " ."; break;
	case 1:avisoFlujo << "has perdido la partida contra " << idUser << " el dia " << fechaHoraDias(fecha) << " ."; break;
	case 2:avisoFlujo << "la partida contra " << idUser << " se ha bloqueado" << "el dia " << fechaHoraDias(fecha) << " ."; break;
	}
	aviso = avisoFlujo.str();
	actualizarAvisos(usuarios.Usuario[pos], aviso);
}

void abandonarPartida(tGestor & gestor){
	/*cambiar el turno a la persona que gana*/
	string idUser;
	if (esSuTurno(gestor) == true){
		if (gestor.puntPartidaSeleccionada->juego.turno == Jugador1){
			gestor.puntPartidaSeleccionada->juego.turno = Jugador2;
			idUser = gestor.puntPartidaSeleccionada->jugador2;
		}
		else{
			gestor.puntPartidaSeleccionada->juego.turno = Jugador1;
			idUser = gestor.puntPartidaSeleccionada->jugador1;
		}
	}
	else{/*como no es su turno no hace falta cambiarlo*/
		if (gestor.puntPartidaSeleccionada->juego.turno == Jugador1){
			idUser = gestor.puntPartidaSeleccionada->jugador1;
		}
		else{ idUser = gestor.puntPartidaSeleccionada->jugador2; }
	}
	abandonar(gestor.puntPartidaSeleccionada);
	/*eliminar para el que inicia sesion*/
	int pos = 0;
	buscarListaAcceso(gestor, pos);/* para saber la posicion dentro de lista acceso partida*/
	eliminar(gestor.ListaAccesoPartidas, pos);
	tResultado resultado = Pierde;
	aplicarFinPartida(gestor.usuarios.Usuario[gestor.Usuariosesión], resultado);
	/*actualizarListaAdversarios(gestor.ListaAdversarios, idUser, resultado, gestor.Usuariosesión);*/
	/*eliminar para el contrincante*/
	pos = 0;
	buscar(gestor.usuarios, idUser, pos);
	resultado = Gana;
	aplicarFinPartida(gestor.usuarios.Usuario[pos], resultado);
	avisarContrincante(gestor.usuarios, gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre, pos, resultado);
	/*actualizarListaAdversarios(gestor.ListaAdversarios, gestor.usuarios.Usuario[gestor.Usuariosesión].Nombre, resultado,pos);*/
	string aviso = "por abandono .";
	actualizarAvisos(gestor.usuarios.Usuario[pos], aviso);
}
bool buscarListaAcceso(tGestor & gestor, int & pos){
	return buscar(gestor.ListaAccesoPartidas, gestor.puntPartidaSeleccionada->único, pos);
}


