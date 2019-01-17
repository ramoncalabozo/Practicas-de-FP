//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#include"ListaUsuarios.h"

void guardar(const tListaUsuarios & usuarios, ofstream & archivo);  /*Esta función guarda en el flujo abierto la lista de usuarios.*/
void redimensionar(tListaUsuarios &usuarios);

//int main(){
//	tListaUsuarios usuarios;
//	ifstream archivo;
//	archivo.open("usuarios.txt");
//	cargar(usuarios, archivo);
//	redimensionar(usuarios);
//	usuarios.Usuario[11].Nombre = "tete";
//	cout << usuarios.Usuario[11].Nombre;
//	cout << usuarios.Usuario[1].Nombre;
//	//cout << usuarios.Usuario[2].Nombre;
//	//tUsuario Usuario;
//	//Usuario.Nombre = "rafa";
//	//usuarios.contador = usuarios.capacidad;
//	//insertar(usuarios, Usuario);
//	//if (true)
//	//{
//	//	ofstream archivo;
//	//	archivo.open("usuarios.txt");
//	//	guardar(usuarios, archivo);
//	//}
//	//string idUser = "marta";
//	//int pos;
//	///*buscar(usuarios, idUser, pos);*/
//	//tNivel nivel = Experto;
//	//buscarUsuarioEsperando(usuarios,nivel,pos);
//}


void guardar(const tListaUsuarios & usuarios, ofstream & archivo){
	archivo << usuarios.contador << '\n';/*guardo el contador*/
	archivo << usuarios.capacidad << '\n';
	for (int contador = 0; contador < usuarios.contador; contador++)
	{
		guardar(usuarios.Usuario[contador], archivo);
	}
}

bool cargar(tListaUsuarios & usuarios, ifstream & archivo){
	archivo >> usuarios.contador;/*cargo el contador*/
	archivo >> usuarios.capacidad;
	usuarios.Usuario = new tUsuario[usuarios.capacidad];
	for (int contador = 0; contador < usuarios.contador; contador++){
		cargar(usuarios.Usuario[contador], archivo);
	}
	return true;
}


bool buscar(const tListaUsuarios & usuarios, const string & idUser, int & pos){
	int ini = 0, fin = usuarios.contador - 1, mitad;
	pos = -1;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;/*cogemos la mitasd*/
		if (idUser == usuarios.Usuario[mitad].Nombre)  {
			pos = mitad;
			encontrado = true;
		}
		else if (idUser < usuarios.Usuario[mitad].Nombre){
			fin = mitad - 1;/*desplazamo el fina la la mitad de larray meno la ya mirada para mira la mitad inferior*/
		}
		else{ ini = mitad + 1; }   /*desplazamos el inicio a la mitad para ver la mitad mayor,*/
	}
	return encontrado;
}


bool buscarUsuarioEsperando(const tListaUsuarios & usuarios, tNivel nivel, int & pos, int &Usuariosesión){
	int i = 0;	/*ya que no esta ordenado segun el nivle a que hacer una busqueda completa*/
	bool encontrado = false;
	while (pos != usuarios.contador && !encontrado){
		if (usuarios.Usuario[pos].nivelJuego == nivel && usuarios.Usuario[pos].espera == true)
		{
			if (usuarios.Usuario[Usuariosesión].Nombre != usuarios.Usuario[pos].Nombre){
				/* ya que no puedo dejar que juegue consigo mismo.......XD*/
				return true;
			}
		}
		pos++;
	}
	return encontrado;
}

bool insertar(tListaUsuarios & usuarios, const tUsuario & Usuario){
	bool ok = true;
	if (usuarios.contador == usuarios.capacidad) {
		redimensionar(usuarios); // lista llena, se redimensiona
	}
	int pos1 = 0;
	while ((pos1 < usuarios.contador) && (usuarios.Usuario[pos1].Nombre < Usuario.Nombre)) {
		pos1++;
	}
	// Insertamos en la posición pos1
	for (int j = usuarios.contador; j > pos1; j--) {
		// Desplazamos una posición a la derecha
		usuarios.Usuario[j] = usuarios.Usuario[j - 1];
	}
	usuarios.Usuario[pos1] = Usuario;
	return ok;
}

void redimensionar(tListaUsuarios &usuarios){
	tUsuario *newUsuario = new tUsuario[usuarios.capacidad];/*para hacer el traspase*/
	newUsuario = usuarios.Usuario;/*salvo los datos*/
	usuarios.Usuario = NULL;/*deja de apuntar dodne antes*/
	delete[]usuarios.Usuario;/*lo borro*/

	int nuevaCapacidad;
	int viejaCapacidad = usuarios.capacidad;
	nuevaCapacidad = (viejaCapacidad * 3) / 2 + 1;
	usuarios.capacidad = nuevaCapacidad;
	usuarios.Usuario = new tUsuario[nuevaCapacidad];/*lo creo de nuevo*/

	for (int i = 0; i < usuarios.contador; i++)
	{
		usuarios.Usuario[i] = newUsuario[i];/*devuelvo los datos al nuevo*/
	}
	newUsuario = NULL;/*deja de apuntar donde antes*/
	delete[]newUsuario;/*lo borro*/
}

void apagar(tListaUsuarios & usuarios, ofstream & archivo){
	guardar(usuarios, archivo);
	delete[] usuarios.Usuario;
}