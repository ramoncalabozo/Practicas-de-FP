// RAMON CALABOZO
// JAIME PALAZON
#include <iostream>
#include "usuario.h"
using namespace std;
void iniciar(tUsuario & usuario, const string & id, const std::string & pas){
	usuario.nombreUsuario = id;
	usuario.contraseñaUsuario = pas;
	usuario.nivelUsuario = PRINCIPIANTE;
	usuario.rachaUsuario = 0;
	usuario.espera = false;
	usuario.ganadasU = 0;
	usuario.perdidasU = 0;
	usuario.empatadasU = 0;
	usuario.partidasEnJuego.contador = 0;
	usuario.avisos = "";
}
void guardar(const tUsuario & usuario, ofstream & archivo){
	string espacio = " ";
	string centinela = "_X_X_X_";
	archivo << usuario.nombreUsuario << endl;
	archivo << usuario.contraseñaUsuario << endl;
	archivo << usuario.nivelUsuario;
	archivo << espacio;
	archivo << usuario.rachaUsuario;
	archivo << espacio;
	archivo << usuario.espera << endl;
	archivo << usuario.ganadasU;
	archivo << espacio;
	archivo << usuario.perdidasU;
	archivo << espacio;
	archivo << usuario.empatadasU << endl;
	archivo << usuario.fechaConexion << endl;
	archivo << usuario.avisos << endl;
	archivo << centinela << endl;
}
bool cargar(tUsuario & usuario, ifstream & archivo){
	string aviso;
	ostringstream flujo;
	string d = "";
	string centinela = "_X_X_X_";
	string avisos1;
	string avisos2;
	bool cargar = true;
	int a;
	archivo >> usuario.nombreUsuario;
	archivo >> usuario.contraseñaUsuario;
	archivo >> a;
	if (a == 0){
		usuario.nivelUsuario = PRINCIPIANTE;
	}
	else if (a == 1){
		usuario.nivelUsuario = MEDIO;
	}
	else if (a == 2){
		usuario.nivelUsuario = EXPERTO;
	}

	archivo >> usuario.rachaUsuario;
	archivo >> usuario.espera;
	archivo >> usuario.ganadasU;
	archivo >> usuario.perdidasU;
	archivo >> usuario.empatadasU;
	archivo >> usuario.fechaConexion;
	do{
		aviso = "";
		flujo.str("");
		archivo >> avisos1;
		if (avisos1 != centinela && avisos1 != aviso){
			getline(archivo, avisos2);
			flujo << avisos1 << avisos2;
			aviso = flujo.str();
		}
		actualizarAvisos(usuario, aviso);
	} while (avisos1 != centinela && avisos1 != aviso);
	return cargar;
}


bool iniciarSesion(tUsuario & usuario, const string & clave){
	bool correcto;
	string user = usuario.nombreUsuario;
	string pass = usuario.contraseñaUsuario;

	if (clave == pass){
		correcto = true;
		usuario.fechaConexion = fechaActual();
	}

	else {
		correcto = false;
	}

	return correcto;
}

void actualizarAvisos(tUsuario & usu, const string & aviso){
	string centinela = "_X_X_X_";
	ostringstream flujo;
	if (usu.avisos.size() != 0 && aviso != centinela){
		flujo << usu.avisos << endl << aviso;
		usu.avisos = flujo.str();
	}
	else{
		if (aviso != centinela){
			usu.avisos = aviso;
		}
	}
}

void limpiarAvisos(tUsuario & usu){
	string nada = "";
	usu.avisos = nada;
}

bool nuevaPartida(tUsuario & usuario, const tParIdEn & par){
	bool ok = true;
	if (usuario.partidasEnJuego.contador < MAX_PAR_US){
		usuario.partidasEnJuego.accesopartidas[usuario.partidasEnJuego.contador] = par;
		usuario.partidasEnJuego.contador++;

	}
	else{
		ok = false;
	}
	return ok;
}

void aplicarFinPartida(tUsuario & usuario, const string & idPar, tResultado resultado){

	if (resultado == empata){
		usuario.rachaUsuario = 0;
		usuario.empatadasU++;
	}
	else if (resultado == Gana){
		usuario.ganadasU++;
		if (usuario.rachaUsuario >= 0){
			usuario.rachaUsuario = usuario.rachaUsuario++;
		}
		else{
			usuario.rachaUsuario = 1;
		}
	}
	else{
		usuario.perdidasU++;
		if (resultado <= 0){
			usuario.rachaUsuario = usuario.rachaUsuario--;
		}
		else {
			usuario.rachaUsuario = -1;
		}
	}


	if (usuario.rachaUsuario == NRN){
		if (usuario.nivelUsuario == PRINCIPIANTE){
			usuario.nivelUsuario = MEDIO;
		}
		else if (usuario.nivelUsuario == MEDIO){
			usuario.nivelUsuario = EXPERTO;
		}
		usuario.rachaUsuario = 0;
	}
	if (usuario.rachaUsuario == -NRN){
		if (usuario.nivelUsuario == EXPERTO){
			usuario.nivelUsuario = MEDIO;
		}
		else if (usuario.nivelUsuario == MEDIO){
			usuario.nombreUsuario = PRINCIPIANTE;
		}
	}
}