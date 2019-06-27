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

#define TAM 10000

typedef struct{
	char* clave;
	int cant;
}usuario_t;
/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

usuario_t* tt_crear(const char* clave, size_t cant){
	usuario_t* tt = malloc(sizeof(usuario_t));
	tt->clave = strdup(clave);
	tt->cant = (int)cant;
	return tt;
}

void tt_destruir_(usuario_t* tt){
	free(tt->clave);
	free(tt);
}

void tt_destruir(void* tt){
	tt_destruir_((usuario_t*)tt);
}

int cmp_(usuario_t* t1, usuario_t* t2){
	if(t1->cant > t2->cant) return -1;
	if(t1->cant < t2->cant) return 1;
	if(strcmp(t1->clave, t2->clave) > 0) return -1;
	return 1;
}

int cmp(const void* t1,const void* t2){
	return cmp_((usuario_t*) t1, (usuario_t*) t2);
}

bool validar_parametro(int argc,char* argv[]){
	if(argc != 2){
		fprintf(stderr, "Error: La cantidad de parametros no es valida.");
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

void counting_sort(lista_t* vector[], lista_t* final, int n){
	heap_t* heap = heap_crear(cmp);
	for(int i = 0; i < TAM; i++){
		if(!lista_esta_vacia(vector[i])){
			if(lista_largo(vector[i]) == 1) lista_insertar_ultimo(final, lista_borrar_primero(vector[i]));
			while(!lista_esta_vacia(vector[i])){
				heap_encolar(heap, lista_borrar_primero(vector[i]));
			}
			while(!heap_esta_vacio(heap)){
				lista_insertar_ultimo(final, heap_desencolar(heap));
			}
		}
	}
	heap_destruir(heap, tt_destruir);
}

lista_t* ordenamiento(hash_t* hash){
	hash_iter_t* iter = hash_iter_crear(hash);
	lista_t* vector[TAM];
	for(int i = 0; i<TAM; i++) vector[i] = lista_crear();
	while(!hash_iter_al_final(iter)){
		usuario_t* tt = tt_crear(hash_iter_ver_actual(iter), *(size_t*)hash_obtener(hash, hash_iter_ver_actual(iter)));
		lista_insertar_ultimo(vector[tt->cant], tt);
		hash_iter_avanzar(iter);
	}
	lista_t* final = lista_crear();
	counting_sort(vector, final, TAM);
	for(int j = 0; j < TAM; j++) lista_destruir(vector[j], NULL);
	hash_iter_destruir(iter);
	return final;
}

void imprimir(lista_t* lista){
	usuario_t* usuario = lista_borrar_primero(lista);
	size_t indice = usuario->cant;
	fprintf(stdout, "%ld:", indice);
	fprintf(stdout, " %s", usuario->clave);
	while(!lista_esta_vacia(lista)){
		usuario = lista_borrar_primero(lista);
		if(usuario->cant != indice){
			indice = usuario->cant;
			fprintf(stdout, "\n%ld:", indice);
			fprintf(stdout, " %s", usuario->clave);
		}
		else{
			fprintf(stdout, ", %s", usuario->clave);
		}
	}
}
/* *****************************************************************
 *                      FUNCION PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[]){
	if(!validar_parametro(argc, argv)) return -1;	
	FILE* archivo = fopen(argv[1], "r");
	if(!archivo) return -1;
	lista_t* lista_de_tweets = leer_tweets(archivo, atoi(argv[1])); 
	while(!lista_esta_vacia(lista_de_tweets)){
		hash_t* hash_usuarios = cargar_hash(lista_de_tweets);
		lista_t* lista_ordenada = ordenamiento(hash_usuarios); // de tts?
		imprimir(lista_ordenada);
		lista_destruir(lista_de_tweets, free);
		hash_destruir(hash_usuarios);
		lista_de_tweets = leer_tweets(archivo, atoi(argv[1]));
	}
	lista_destruir(lista_de_tweets,free);
	return 0;
}
