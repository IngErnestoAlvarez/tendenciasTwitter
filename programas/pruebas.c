#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "strutil.h"
#include "lista.h"
#include "funcionesAuxiliares.h"
#define CANT 20

void pruebas_leer_tweets(void);

void pruebas_leer_tweets(){
	size_t cantidad=CANT;
	FILE* archivo=fopen("pruebas.txt","r");
	if(!archivo){
		fprintf(stderr, "No se pudo abrir pruebas.txt\n");
		return;
	}
	fprintf(stdout, "\n\nPRUEBAS LEER TWEETS (con cantidad de lineas igual a %ld): \n\n", cantidad);
	lista_t* lista = leer_tweets(archivo, cantidad);
	fprintf(stdout, "La cantidad de tweets es: %ld \n", lista_largo(lista));
	lista_iter_t* iter = lista_iter_crear(lista);
	int i=1;
	while(!lista_iter_al_final(iter)){
		char* tweet = lista_iter_ver_actual(iter);
		fprintf(stdout, "%d %s\n", i,tweet);
		lista_iter_avanzar(iter);
		i++;
	}

	lista_iter_destruir(iter);
	lista_destruir(lista,free);
	fclose(archivo);
}



int main(){
	pruebas_leer_tweets();
	return 0;
}
