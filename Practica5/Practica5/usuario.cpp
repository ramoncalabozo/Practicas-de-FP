//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#include"fecha.h"
#include"ListaAccesoPartidas.h"
#include"usuario.h"

//int main(){
//	tUsuario Usuario;
//	string id="pepe";
//	string pas="12345";
//	iniciar(Usuario, id, pas);
//	if (true){
//		ofstream archivo;
//		archivo.open("usuario.txt");
//		guardar(Usuario, archivo);
//	}
//	ifstream archivo;
//	archivo.open("usuario.txt");
//	cargar(Usuario, archivo);
//	cout << "introduce contraseña";
//		string clave;
//		cin >> clave;
//		if (iniciarSesion(Usuario, clave) == true){ cout << "la contraseña es correcta"; }
//		else { cout << "la contraseña es falsa"; }
//	string aviso="fghf";
//	actualizarAvisos(Usuario, aviso);
//	tParIdEn par;
//	nuevaPartida(Usuario, par);
//	string idPar;
//	tResultado resultado;
//	aplicarFinPartida(Usuario, idPar, resultado)
//}

bool comprobarCentinela(string & centinela);

void iniciar(tUsuario & Usuario, const string & id, const string & pas){
	Usuario.Nombre = id;
	Usuario.contraseña = pas;
	Usuario.nivelJuego = Principiante;
	Usuario.racha = 0;
	Usuario.NumeroPartidas.ganadas = 0;
	Usuario.NumeroPartidas.perdidas = 0;
	Usuario.NumeroPartidas.empatadas = 0;
	Usuario.espera = false;
	Usuario.fecha = fechaActual();
	Usuario.avisos = "";
}

void guardar(const tUsuario & Usuario, ofstream & archivo){
	archivo << Usuario.Nombre << '\n';
	archivo << Usuario.contraseña << '\n';
	archivo << Usuario.nivelJuego << " ";
	archivo << Usuario.racha << " ";
	archivo << Usuario.espera << '\n';
	archivo << Usuario.NumeroPartidas.ganadas << " ";
	archivo << Usuario.NumeroPartidas.perdidas << " ";
	archivo << Usuario.NumeroPartidas.empatadas << '\n';
	archivo << Usuario.fecha << '\n';
	archivo << Usuario.avisos << '\n';
	archivo << "_X_X_X_" << '\n';
}

bool cargar(tUsuario & Usuario, ifstream & archivo){
	archivo >> Usuario.Nombre;
	archivo >> Usuario.contraseña;
	int n;/*para coger un numero y saber que nivel es*/
	archivo >> n;
	switch (n){
	case 0: Usuario.nivelJuego = Principiante; break;
	case 1:Usuario.nivelJuego = Medio; break;
	case 2:Usuario.nivelJuego = Experto; break;
	default: return false;
	}
	archivo >> Usuario.racha;
	int espera;
	archivo >> espera;
	switch (espera)
	{
	case 0:Usuario.espera = false; break;
	case 1: Usuario.espera = true; break;
	default:return false;
	}
	archivo >> Usuario.NumeroPartidas.ganadas;
	archivo >> Usuario.NumeroPartidas.perdidas;
	archivo >> Usuario.NumeroPartidas.empatadas;
	archivo >> Usuario.fecha;
	string centinela;
	bool Centinela = false;
	ostringstream flujo;
	while (Centinela == false)/*en el momento que encuentre el centinela para de coger avisos*/
	{
		archivo >> centinela;
		if (Centinela == comprobarCentinela(centinela)){
			flujo << centinela << " ";
			if (centinela == "."){ flujo << '\n'; }/*para saber que termino la linea del aviso y poner el siguiente aparte*/
		}
		else{ Centinela = true; Usuario.avisos = flujo.str(); }
	}
	return true;
}
bool comprobarCentinela(string & centinela){
	return centinela == "_X_X_X_";
}
bool iniciarSesion(tUsuario & Usuario, const string & clave){
	return Usuario.contraseña == clave;
}

void actualizarAvisos(tUsuario & Usuario, const string & aviso){
	ostringstream flujo;
	flujo << Usuario.avisos << '\n' << aviso;
	Usuario.avisos = flujo.str();
}

void limpiarAvisos(tUsuario & Usuario){
	Usuario.avisos = "";
}

bool nuevaPartida(tUsuario & Usuario){
	tListaAccesoPartidas lista;
	lista.contador = 0;
	if (llena(lista) == false){
		Usuario.espera = true;
		return true;
	}
	else{ return false; }

}

void aplicarFinPartida(tUsuario & Usuario, tResultado resultado){
	switch (resultado)
	{
	case 0:Usuario.NumeroPartidas.ganadas++; Usuario.racha++; break;
	case 1:Usuario.NumeroPartidas.perdidas++; Usuario.racha--; break;
	case 3:Usuario.NumeroPartidas.empatadas++; Usuario.racha = 0; break;
	}

	if (Usuario.racha - 1 == NRN){
		switch (Usuario.nivelJuego)
		{
		case 0:Usuario.nivelJuego = Medio; break;
		case 1: Usuario.nivelJuego = Experto; break;
		case 2:break;
		}
	}
	if (Usuario.racha + 1 == -NRN){
		switch (Usuario.nivelJuego)
		{
		case 2:Usuario.nivelJuego = Medio; break;
		case 1: Usuario.nivelJuego = Principiante; break;
		case 0: break;
		}
	}
}

