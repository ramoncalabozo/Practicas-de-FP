//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#include "fecha.h"

//int main(){
//	tListaPartidas partidas;
//	fecha(partidas);
//	cout << partidas.partida[partidas.contador].stringFechayHora;
//	system("PAUSE");
//}

string stringFecha(tFecha fecha, bool hora);

string fechaHoraDias(tFecha& fecha){
	bool hora = true;/*en funcion de si es true o false dira la hora o no*/
	return stringFecha(fecha, hora);/*genera la fecha y la devuelve para guardala en le array, la hora tambien dependiendo de si es false o no*/
}


tFecha fechaActual()
{
	return time(0);
}
string stringFecha(tFecha fecha, bool hora) {
	ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << setfill('0') << setw(4) << 1900 + ltm.tm_year << '/'
		<< setw(2) << 1 + ltm.tm_mon << '/' << setw(2) << ltm.tm_mday;
	if (hora) resultado << " (" << setw(2) << ltm.tm_hour << ':' << setw(2)
		<< ltm.tm_min << ':' << setw(2) << ltm.tm_sec << ')';

	return resultado.str();
}