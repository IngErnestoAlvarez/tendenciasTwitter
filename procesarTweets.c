#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "minsketch.h"
#include "strutil.h"
#include "lista.h"

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


/* Guarda tweets en una lista
 * Pre: Cantidad de lineas es un numero positivo.
 * Post: Devuelve una lista con todos los tweets leidos en 'cantidad_de lineas' lineas.
 */

lista_t* leer_tweets(size_t cantidad_de_lineas){
	
	lista_t* lista_de_tweets = lista_crear();
	char* new_line[1];
	new_line[0] = '\n';
	size_t contador_de_lineas = 1;
	size_t ultimo_new_line = 0;
	size_t aux = 0; //Variable donde empieza el tweet

	while(contador_de_lineas <= cantidad_de_lineas){
		aux = ultimo_new_line;
		ultimo_new_line = strcspn(stdin+ultimo_new_line, new_line); //Encuentra la posicion de '\n'
		char* tweet = substr(stdin[aux], ultimo_new_line-aux); 
		lista_insertar_ultimo(lista_de_tweets,tweet);
		contador_de_lineas++;
	}

	return lista_de_tweets;
}




/* *****************************************************************
 *                      FUNCION PRINCIPAL
 * *****************************************************************/
int main(int argc, char *argv[]){
	if(!validar_parametros(argc, argv)) return -1;	
	lista_de_tweets = leer_tweets(atoi(argv[1]));


	lista_destruir(lista_de_tweets,free);
	return 0;
}
