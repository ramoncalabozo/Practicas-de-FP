//L1‐G07 CASARES SÁNCHEZ, RODRIGO  
//L1‐G07 LLORET BODELON, ALVARO  

#ifndef FECHA_H
#define FECHA_H
#include <iostream>
#include <sstream>
#include <iomanip> 
#include <ctime>
using namespace std;

typedef time_t tFecha;

string fechaHoraDias(tFecha & fecha);  /*Declara una funcion string que llama al tipo tFecha para mostrarla en formato Año / Mes / Día,y en formato Hora / Mins / Segs.*/

tFecha fechaActual();  /*Declara un tipo tFecha para consultar la fecha actual como su propio nombre indica.*/

#endif  // FECHA_H