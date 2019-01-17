//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO 
#include "mostrarDatosAdversarios.h"

void cargarAdversarios(tAdversarios &Adversarios, ifstream & archivo);
void guardarAdversarios(tAdversarios &Adversarios, ofstream & archivo);

//int main(){
//	tListaAdversarios ListaAdversarios;
//	ifstream archivo;
//	ifstream flujo;
//	flujo.open("usuarios.txt", ios::app);
//	cargarListaAdversarios(ListaAdversarios,archivo);
//
//
//}
void mostrarDatosAdversarios(tAdversarios &Adversarios, int &pos){
	cout << "================================================================================";
	cout << "Contra " << Adversarios.Adversario[pos]->nombreAdversario << ":" << '\n';
	cout << "  -Has ganado: " << Adversarios.Adversario[pos]->ganadas << '\n';
	cout << "  -Has Perdido: " << Adversarios.Adversario[pos]->perdidas << '\n';
	cout << "  -Has empatado: " << Adversarios.Adversario[pos]->empatadas << '\n';
	cout << "================================================================================";
	cout << '\n';
	pos++;
	while (pos < Adversarios.contador)
		mostrarDatosAdversarios(Adversarios, pos);
}


void  cargarListaAdversarios(tListaAdversarios &ListaAdversarios, int &tamañoLista, ifstream & archivo){
	archivo >> ListaAdversarios.contador;
	ListaAdversarios.Adversarios = new tAdversarios[tamañoLista];
	ListaAdversarios.posUsuario = new int[tamañoLista];
	for (int i = 0; i < tamañoLista; i++)
	{
		ListaAdversarios.Adversarios[i].contador = 0;
	}
	for (int i = 0; i < ListaAdversarios.contador; i++)
	{
		archivo >> ListaAdversarios.posUsuario[i];
		cargarAdversarios(ListaAdversarios.Adversarios[ListaAdversarios.posUsuario[i]], archivo);
	}
}

void cargarAdversarios(tAdversarios &Adversarios, ifstream & archivo){
	archivo >> Adversarios.contador;
	for (int i = 0; i < Adversarios.contador; i++)
	{
		Adversarios.Adversario[i] = new tAdversario;
		archivo >> Adversarios.Adversario[i]->nombreAdversario;
		archivo >> Adversarios.Adversario[i]->ganadas;
		archivo >> Adversarios.Adversario[i]->perdidas;
		archivo >> Adversarios.Adversario[i]->empatadas;
	}

}

void apagarListaAdversarios(const tListaAdversarios &ListaAdversarios, ofstream & archivo){
	archivo << ListaAdversarios.contador << '\n';

	for (int i = 0; i < ListaAdversarios.contador; i++)
	{
		archivo << ListaAdversarios.posUsuario[i] << '\n';
		guardarAdversarios(ListaAdversarios.Adversarios[ListaAdversarios.posUsuario[i]], archivo);
	}
	delete[] ListaAdversarios.Adversarios;
	delete[] ListaAdversarios.posUsuario;
}

void guardarAdversarios(tAdversarios &Adversarios, ofstream & archivo){
	archivo << Adversarios.contador << '\n';
	for (int i = 0; i < Adversarios.contador; i++)
	{
		archivo << Adversarios.Adversario[i]->nombreAdversario << '\n';
		archivo << Adversarios.Adversario[i]->ganadas << " ";
		archivo << Adversarios.Adversario[i]->perdidas << " ";
		archivo << Adversarios.Adversario[i]->empatadas << '\n';
	}

}
void nuevoAdversario(tListaAdversarios &ListaAdversarios, int &pos);

void nuevoAdversario(tListaAdversarios &ListaAdversarios, int &pos){
	bool encontrada = false;
	int i = 0;
	while (encontrada == false && i < ListaAdversarios.contador)
	{
		if (ListaAdversarios.posUsuario[i] == pos)
		{
			encontrada = true;
		}
		i++;
	}
	if (encontrada == false)
	{
		ListaAdversarios.posUsuario[ListaAdversarios.contador] = pos;
		ListaAdversarios.contador++;
		ListaAdversarios.Adversarios[pos].contador = 0;
	}
}


//void actualizarListaAdversarios(tListaAdversarios & ListaAdversarios, const string &nombreAdversario, const tResultado &resultado,int & pos){
//	
//	nuevoAdversario(ListaAdversarios, pos); int posAdversario = 0;
//	bool encontrado = false;
//    int i = 0;
//
//	while (encontrado == false && i < ListaAdversarios.contador)
//	{
//		if (ListaAdversarios.Adversarios[pos].Adversario[i]->nombreAdversario== nombreAdversario){
//			encontrado = true;
//		}
//		i++;
//
//	}
//	/*si sale sin encontrarle crea uno con sus datos*/
//	if (encontrado == false){
//		ListaAdversarios.Adversarios[pos].Adversario[ListaAdversarios.Adversarios[pos].contador] = new tAdversario;
//		ListaAdversarios.Adversarios[pos].Adversario[ListaAdversarios.Adversarios[pos].contador]->ganadas = 0;
//		ListaAdversarios.Adversarios[pos].Adversario[ListaAdversarios.Adversarios[pos].contador]->perdidas = 0;
//		ListaAdversarios.Adversarios[pos].Adversario[ListaAdversarios.Adversarios[pos].contador]->empatadas = 0;
//		ListaAdversarios.Adversarios[pos].Adversario[ListaAdversarios.Adversarios[pos].contador]->nombreAdversario = nombreAdversario;
//		ListaAdversarios.Adversarios[pos].contador++;
//	}
//	switch (resultado)
//	{
//	case 0:ListaAdversarios.Adversarios[pos].Adversario[i]->ganadas++; break;
//	case 1:ListaAdversarios.Adversarios[pos].Adversario[i]->perdidas++; break;
//	case 2:ListaAdversarios.Adversarios[pos].Adversario[i]->empatadas++; break;
//	}
//}