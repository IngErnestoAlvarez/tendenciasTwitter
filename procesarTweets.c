#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minsketch.h"
#include "strutil.h"
#include "lista.h"
#include "funcionesAuxiliares.h"

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

bool validar_parametros(int argc,char* argv[]){
	if(argc != 3){
		fprintf(stderr, "Error: La cantidad de parametros no es valida.");
		return false;
	}
	if(atoi(argv[1]) <= 0){
		fprintf(stderr, "Error: El numero de lineas a leer no es valido.");
		return false;
	}
	if(atoi(argv[2]) <= 0){
		fprintf(stderr, "Error: El numero de tendencias que pides no es valido");
		return false;
	}
	return true;
}


/* *****************************************************************
 *                      FUNCION PRINCIPAL
 * *****************************************************************/
int main(int argc, char *argv[]){
	if(!validar_parametros(argc, argv)) return -1;	
	lista_de_tweets = leer_tweets(stdin,atoi(argv[1]));


	lista_destruir(lista_de_tweets,free);
	return 0;
}
