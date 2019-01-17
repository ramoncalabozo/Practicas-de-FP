//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#ifndef MAINP4_H
#define MAINP4_H
#include"gestor.h"
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

const string F_USUARIOS = "usuarios.txt";
const string F_PARTIDAS = "partidas.txt";

void menuRegistro(tGestor & gestor, char & op1);  /*Esta función muestra y gestiona el menú inicial y llama a op1(de tipo char).*/
void menuUsuario(tGestor & gestor, char & op2);  /*Esta función muestra y gestiona el menú principal de una sesión de usuario y llama a otra opción(de tipo char).*/
void menuPartida(tGestor & gestor, char & op3);  /* Esta función muestra y gestiona el menú de una partida y llama a una tercera opción(de tipo char).*/

#endif  // MAINP4_H