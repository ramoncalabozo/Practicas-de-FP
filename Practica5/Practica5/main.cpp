//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

/*he intentado hacer la parte opcional, pero no me ha dado tiempo a todo...funciona todo
menos la parte que mete nuevos adversarios o los actualizas, lo dejo comentado por si sube nota.
mastrar si muestra, aunque los datos estan inventados*/
#include "menusP5.h"
#include "stdlib.h"
int main(){
	tGestor gestor;
	char op1 = 'N';/*el numero que introduce(es un char para que no se vuelva loco si ponen una letra)*/
	char op2;/*centineña menu usuario*/
	char op3;/*centinela menu partida*/
	string ficheroUsu = F_USUARIOS;
	string ficheroPar = F_PARTIDAS;
	iniciar(gestor, ficheroUsu, ficheroPar);/*cargamos las partidas*/

	while (op1 != '0'){ /*mientras que no elijan salir no saldra*/
		system("cls");
		op2 = 'N';
		op3 = 'N';
		menuRegistro(gestor, op1);
		if (op1 != '0'){
			while (op2 != '0'){
				op3 = 'N';
				menuUsuario(gestor, op2);
				if (op2 != 'x' && op2 != '0' && op2 == '1'){
					while (op3 != '0'){
						menuPartida(gestor, op3);
					}
				}
			}
		}
	}

	cerrar(gestor, ficheroUsu, ficheroPar);
}