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

typedef struct{
	char* clave;
	size_t cant;
}tt_t;
/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

tt_t* tt_crear(const char* clave, size_t cant){
	tt_t* tt = malloc(sizeof(tt_t));
	//COPIAR CLAVE
	tt->clave = clave;
	tt->cant = cant;
	return tt;
}

void tt_destruir_(tt_t* tt){
	free(tt->clave);
	free(tt);
}

void tt_destruir(void* tt){
	tt_destruir_((tt_t*)tt);
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

heap_t* cargar_heap(lista_t* lista, minsketch_t* min, int k){
	hash_t* hash = hash_crear(NULL);
	heap_t* heap = heap_crear(cmp);
	char* linea;
	char** tweet = NULL;
	size_t i = 1;
	tt_t* tt = NULL;
	while(!lista_esta_vacia(lista)){
		linea = lista_borrar_primero(lista);
		tweet = split(linea, ',');
		free(linea);
		while(tweet[i]){
			if(!hash_pertenece(hash, tweet[i])){
				hash_guardar(hash, tweet[i], NULL);
				tt = tt_crear(tweet[i], min_obtener(min, tweet[i]));
				if(heap_cantidad(heap) < k){
					heap_encolar(heap, tt);
				}
				else if(cmp(heap_ver_max(heap), tt) > 0){
					tt_destruir(heap_desencolar(heap));
					heap_encolar(heap, tt);
				}
			}
			i++;
		}
		i = 1;
		free_strv(tweet);
	}
	hash_destruir(hash);
	return heap;
}

void imprimir_tt(heap_t heap){
	pila_t* pila = pila_crear();
	while(!heap_esta_vacio(heap)) pila_apilar(pila, heap_desencolar(heap));
	while(!pila_esta_vacia(pila)){
		tt_t* tt = pila_desapilar(pila);
		fprintf(stdout, "%d %s\n", tt->cant, tt->clave);
	}
}
/* *****************************************************************
 *                      FUNCION PRINCIPAL
 * *****************************************************************/
int main(int argc, char *argv[]){
	if(!validar_parametros(argc, argv)) return -1;	
	
	lista_t* lista_de_tweets = leer_tweets(stdin, atoi(argv[1])); 
	int indice = 1;
	while(!lista_esta_vacia(lista_de_tweets)){
		
		minsketch_t* sketch = cargar_sketch(lista_de_tweets);
		heap_t* heap = cargar_heap(lista_de_tweets, sketch, atoi(argv[2]));
		fprintf(stdout, "--- %d\n", indice);
		indice++;
		imprimir_tt(heap);

		lista_destruir(lista_de_tweets,free);
		heap_destruir(heap, tt_destruir);
		min_destruir(sketch);
		lista_de_tweets=leer_tweets(stdin,atoi(argv[1]));
	}

	lista_destruir(lista_de_tweets,free);
	return 0;
}
