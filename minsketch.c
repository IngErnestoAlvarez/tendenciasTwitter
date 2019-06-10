#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "minsketch.h"

#define TAM_VEC 10000

struct minsketch{
	int* v1;
	int* v2;
	int* v3;
};


/********************************************/
/*******FUNCIONES DE HASH********************/
/********************************************/

int funcion1(const char* clave);

int funcion2(const char* clave);

int funcion3(const char* clave);


/********************************************/
/*******PRIMITIVAS********************/
/********************************************/

minsketch_t* min_crear(){
	minsketch_t* nuevo = malloc(sizeof(minsketch_t));
	if(!nuevo) return NULL;
	nuevo->v1 = malloc(sizeof(int) * (TAM_VEC));
	if(!nuevo->v1){
		free(nuevo);
		return NULL;
	}
	nuevo->v2 = malloc(sizeof(int) * (TAM_VEC));
	if(!nuevo->v2){
		free(nuevo->v1);
		free(nuevo);
		return NULL;
	}
	nuevo->v3 = malloc(sizeof(int) * (TAM_VEC));
	if(!nuevo->v3){
		free(nuevo->v1);
		free(nuevo->v2);
		free(nuevo);
		return NULL;
	}
	return nuevo;
}

void min_guardar(minsketch_t* min,const char* clave){
	min->v1[funcion1(clave)]++;
	min->v2[funcion2(clave)]++;
	min->v3[funcion3(clave)]++;
}

int min_obtener(minsketch_t* min, const char* clave){
	int minimo = min->v1[funcion1(clave)];

	if(minimo > min->v2[funcion2(clave)]){
		minimo = min->v2[funcion2(clave)];
	}

	if(minimo > min->v3[funcion3(clave)]){
		minimo = min->v3[funcion3(clave)];
	}
	return minimo;
}

void min_destruir(minsketch_t* min){
	free(min->v1);
	free(min->v2);
	free(min->v3);
	free(min);
}
