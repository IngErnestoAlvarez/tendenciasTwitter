#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../noProgramas/minsketch.h"
#include "../noProgramas/strutil.h"
#include "../noProgramas/lista.h"
#include "../noProgramas/funcionesAuxiliares.h"
#include "../noProgramas/heap.h"
#include "../noProgramas/hash.h"
#include "../noProgramas/pila.h"
#define _POSIX_C_SOURCE 200809L

typedef struct{
	char* clave;
	int cant;
}tt_t;
/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

tt_t* tt_crear(char* clave, size_t cant){
	tt_t* tt = malloc(sizeof(tt_t));
	tt->clave = strdup(clave);
	tt->cant = (int)cant;
	return tt;
}

void tt_destruir_(tt_t* tt){
	free(tt->clave);
	free(tt);
}

void tt_destruir(void* tt){
	tt_destruir_((tt_t*)tt);
}

int cmp_(tt_t* t1, tt_t* t2){
	if(t1->cant > t2->cant) return -1;
	if(t1->cant < t2->cant) return 1;
	if(strcmp(t1->clave, t2->clave) > 0) return 1;
	return -1;
}

int cmp(const void* t1,const void* t2){
	return cmp_((tt_t*) t1, (tt_t*) t2);
}

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


hash_t* cargar_hash(lista_t* lista_tweets){
	hash_t* hash_usuarios_tts=hash_crear(NULL);
	lista_iter_t* iter=lista_iter_crear(lista_tweets);
	while(!lista_iter_al_final(iter)){
		char* tweet = lista_iter_ver_actual(iter);
		char** tweet_s = split(tweet, ',');
		hash_t* hash_local=hash_crear(NULL);
		size_t i = 1;
		while(tweet_s[i] != NULL){
			if(!hash_pertenece(hash_usuarios_tts,tweet_s[0])){
				size_t aux[1] = {0};
				hash_guardar(hash_usuarios_tts,tweet_s[0], &aux[0]); //Si el usuario no esta en el global, lo "inicializa"
			}
			if(!hash_pertenece(hash_local,tweet_s[i])){
				hash_guardar(hash_local,tweet_s[i],NULL);
				size_t* aux = hash_obtener(hash_usuarios_tts,tweet_s[0]);
				*(aux)++;
				hash_guardar(hash_usuarios_tts,tweet_s[0], aux);
			}
		}
		hash_destruir(hash_local);
		free_strv(tweet_s);
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return hash_usuarios_tts;
}

/* *****************************************************************
 *                      FUNCION PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[]){
	if(!validar_parametros(argc, argv)) return -1;	
	lista_t* lista_de_tweets = leer_tweets(stdin, atoi(argv[1])); 
	while(!lista_esta_vacia(lista_de_tweets)){
		hash_t* hash_usuarios = cargar_hash(lista_de_tweets);
		lista_t* lista_ordenada = ordenamiento(hash_usuarios); // de tts?
		imprimir(lista_ordenada);
		lista_destruir(lista_de_tweets, free);
		hash_destruir(hash_destruir);
		lista_de_tweets = leer_tweets(stdin, atoi(argv[1]));
	}
	lista_destruir(lista_de_tweets,free);
	return 0;
}