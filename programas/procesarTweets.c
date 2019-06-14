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
	
	//se tiene que repetir hasta que no haya mas tweets
	//Otra funcion aux?
	lista_t* lista_de_tweets = leer_tweets(stdin, atoi(argv[1])); 
	lista_iter_t* iter = lista_iter_crear(lista_de_tweets);
	minsketch_t* sketch=min_crear();
	size_t historico=0;
	while( (historico<atoi(argv[2])) && (!lista_iter_al_final(iter)) ){
		char* tweet = lista_iter_ver_actual(iter);
		char** tweet_s = split(tweet, ',');
		int i=1; //saltea el usuario
		while(tweet_s[i] != NULL){
			min_guardar(sketch,tweet_s[i]);
			i++;
		}
		free_strv(tweet_s);
		lista_iter_avanzar(iter);
		historico++;
	}

	lista_destruir(lista_de_tweets,free);
	return 0;
}
