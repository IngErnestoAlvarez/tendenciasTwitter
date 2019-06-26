#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minsketch.h"

#define TAM_VEC 10000

struct minsketch{
	size_t* vector1;
	size_t* vector2;
	size_t* vector3;
};


/* *****************************************************************
 *                    FUNCIONES DE HASHING
 * *****************************************************************/

size_t funcion1(const char* cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    return hash;
}
//Del tp del hash, sigo sin saber de donde es.
static unsigned long funcion2(const char *str)
 	{
        unsigned long hash = 0;
        int c;

        while ((c = *str++))
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }

    //Algoritmo creado para la base de datos sdbm, 
    //fuente: http://profesores.elo.utfsm.cl/~agv/elo320/miscellaneous/hashFunction/hashFunction.html
unsigned long funcion3(const char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
  	}
//djb2 la cual es una variante del algoritmo popularizado por Dan J. Bernstein.
//Fuente y mas informacion: http://profesores.elo.utfsm.cl/~agv/elo320/miscellaneous/hashFunction/hashFunction.html
/* *****************************************************************
 *                         PRIMITIVAS
 * *****************************************************************/

minsketch_t* min_crear(){
	minsketch_t* nuevo = malloc(sizeof(minsketch_t));
	if(!nuevo) return NULL;
	nuevo->vector1 = malloc(sizeof(size_t) * (TAM_VEC));
	if(!nuevo->vector1){
		free(nuevo);
		return NULL;
	}
	nuevo->vector2 = malloc(sizeof(size_t) * (TAM_VEC));
	if(!nuevo->vector2){
		free(nuevo->vector1);
		free(nuevo);
		return NULL;
	}
	nuevo->vector3 = malloc(sizeof(size_t) * (TAM_VEC));
	if(!nuevo->vector3){
		free(nuevo->vector1);
		free(nuevo->vector2);
		free(nuevo);
		return NULL;
	}
	for(int i = 0; i < TAM_VEC; i++){
		nuevo->vector1[i] = 0;
		nuevo->vector2[i] = 0;
		nuevo->vector3[i] = 0;
	}
	return nuevo;
}

void min_guardar(minsketch_t* min,const char* clave){
	min->vector1[funcion1(clave)%TAM_VEC]++;
	min->vector2[funcion2(clave)%TAM_VEC]++;
	min->vector3[funcion3(clave)%TAM_VEC]++;
}

size_t min_obtener(minsketch_t* min, const char* clave){
	size_t minimo = min->vector1[funcion1(clave)%TAM_VEC];

	if(minimo > min->vector2[funcion2(clave)%TAM_VEC]){
		minimo = min->vector2[funcion2(clave)%TAM_VEC];
	}

	if(minimo > min->vector3[funcion3(clave)%TAM_VEC]){
		minimo = min->vector3[funcion3(clave)%TAM_VEC];
	}
	return minimo;
}

void min_destruir(minsketch_t* min){
	free(min->vector1);
	free(min->vector2);
	free(min->vector3);
	free(min);
}
