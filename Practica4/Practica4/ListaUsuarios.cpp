// RAMON CALABOZO
// JAIME PALAZON
#include <iostream>
#include "ListaUsuarios.h"
#include <iostream>//hay que quitarlo
using namespace std;
// Funciones

bool cargar(tListaUsuarios & usuarios, std::ifstream & archivo){
	bool ok = true;
	archivo >> usuarios.cont; // Leemos contador
	for (int i = 0; i < usuarios.cont; i++){
		if (!cargar(usuarios.usuario[i], archivo)){
			ok = false;
		}
	}
	return ok;
}
void guardar(const tListaUsuarios & usuarios, std::ofstream & archivo){
	archivo << usuarios.cont << endl;

	for (int i = 0; i < usuarios.cont; i++){
		guardar(usuarios.usuario[i], archivo);
	}


}

bool buscar(const tListaUsuarios & usuarios, const std::string & idUser, int & pos){
	int mitad;
	int inicio = 0;
	int final = usuarios.cont - 1;
	bool existe = false;

	while (inicio <= final && !existe){
		mitad = (inicio + final) / 2;
		if (idUser == usuarios.usuario[mitad].nombreUsuario){
			existe = true;
		}
		else if (idUser < usuarios.usuario[mitad].nombreUsuario){
			final = final - 1;
		}
		else {
			inicio = mitad + 1;
		}

	}
	if (existe){
		pos = mitad;
	}
	else{
		pos = inicio;
	}
	return existe;

}




bool insertar(tListaUsuarios & usuarios, const tUsuario & usuario, int & pos){
	bool ok = true;
	int contador = pos + 1;
	int i = 0;
	bool insertar = true;
	bool unico = true;
	for (int i = 0; i <= usuarios.cont; i++){
		if (usuario.nombreUsuario == usuarios.usuario[i].nombreUsuario){
			unico = false;
		}
	}
	if (usuarios.cont < MAX_USU && unico){
		i = usuarios.cont;
		usuarios.cont++;
		//int peperoni(usuarios.cont - pos);
		while ((usuarios.cont - contador) >/*=*/ 0){
			usuarios.usuario[i] = usuarios.usuario[i - 1];
			contador++;
			i--;
		}
		usuarios.usuario[pos /* +1*/] = usuario;
		usuarios.usuario[pos/* + 1*/].fechaConexion = fechaActual();
	}
	else{
		ok = false;
	}
	return ok;
}

bool buscarUsuarioEsperando(const tListaUsuarios & usuarios, tNivel nivel, int & pos){
	int i = 0;
	bool existe = false;
	while (i < usuarios.cont && !existe){
		if (usuarios.usuario[i].nivelUsuario == nivel && usuarios.usuario[i].espera == true){
			existe = true;
			pos = i;
		}
		i++;
	}
	return existe;
}