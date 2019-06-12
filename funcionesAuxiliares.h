#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "strutil.h"
#include "lista.h"


//!No verifica memoria, si falta explota todo.
/* Guarda tweets en una lista
 * Pre: Cantidad de lineas es un numero positivo. ()
 * Post: Devuelve una lista con todos los tweets leidos en 'cantidad_de lineas' lineas.
 */
lista_t* leer_tweets(FILE* archivo,size_t cantidad);

/* Lee de un archivo hasta que se encuentra con 'caracter' o el fin de archivo.
 * Pre: El archivo debe estar abierto.
 * Post: Devuelve un string (DINAMICO) que termina en '\0' (No resetea el cursor del archivo). 
 */
char* leer_hasta_char(FILE* archivo,char caracter);



#endif // FUNCIONESAUXILIARES_H