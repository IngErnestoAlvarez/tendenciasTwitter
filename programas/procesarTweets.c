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

minsketch_t* cargar_sketch(lista_t* lista_tweets){
	lista_iter_t* iter = lista_iter_crear(lista_tweets);
	minsketch_t* sketch=min_crear();
	while(!lista_iter_al_final(iter)){
		char* tweet = lista_iter_ver_actual(iter);
		char** tweet_s = split(tweet, ',');
		int i = 1; //saltea el usuario
		while(tweet_s[i] != NULL){
			min_guardar(sketch, tweet_s[i]);
			i++;
		}
		free_strv(tweet_s);
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return(sketch);
}

/* *****************************************************************
 *                      FUNCION PRINCIPAL
 * *****************************************************************/
int main(int argc, char *argv[]){
	if(!validar_parametros(argc, argv)) return -1;	
	
	lista_t* lista_de_tweets = leer_tweets(stdin, atoi(argv[1])); 
	while(!lista_esta_vacia(lista_de_tweets)){
		
		minsketch_t* sketch = cargar_sketch(lista_de_tweets);
		heap_t* heap = cargar_heap(lista_de_tweets, sketch, atoi(argv[2]));
		imprimir_tt(heap,min);

		lista_destruir(lista_de_tweets,free);
		heap_destruir(heap);
		min_destruir(sketch);
		lista_de_tweets=leer_tweets(stdin,atoi(argv[1]));
	}

	lista_destruir(lista_de_tweets,free);
	return 0;
}
