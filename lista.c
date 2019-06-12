#include "lista.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>




struct nodo;
typedef struct nodo nodo_t;

struct nodo{
	void* dato;
	nodo_t* siguiente;
};

struct lista{
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;

};

// refugio del iterador.c

struct lista_iter{
	nodo_t* posicion;
	nodo_t* posicion_anterior;
	lista_t* mi_lista;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* crear_nodo(void* dato_nuevo,nodo_t* siguiente){
	nodo_t* nodo=malloc(sizeof(nodo_t));
	if(nodo==NULL) return(NULL);
	nodo->dato=dato_nuevo;
	nodo->siguiente=siguiente;
	return(nodo);
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/


lista_t *lista_crear(void){
	lista_t* lista=malloc(sizeof(lista_t));
	if(lista==NULL) return(NULL);
	lista->primero=NULL;
	lista->ultimo=NULL;
	lista->largo=0;
	return(lista);
}

bool lista_esta_vacia(const lista_t *lista){
	return(lista->primero==NULL);
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo_nuevo=crear_nodo(dato,lista->primero);
	if(nodo_nuevo==NULL) return(false);
	lista->primero=nodo_nuevo;
	if(lista->largo==0) lista->ultimo=nodo_nuevo;
	lista->largo++;
	return(true);
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	if(lista->largo==0) return(lista_insertar_primero(lista,dato));
	nodo_t* nodo_nuevo=crear_nodo(dato,NULL);
	if(nodo_nuevo==NULL) return(false);
	lista->ultimo->siguiente=nodo_nuevo;
	lista->ultimo=nodo_nuevo;
	lista->largo++;
	return(true);
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return(NULL);
	if(lista->primero==lista->ultimo) lista->ultimo=NULL;
	nodo_t* nodo_auxiliar=lista->primero;
	void* dato=nodo_auxiliar->dato;
	lista->primero=nodo_auxiliar->siguiente;
	free(nodo_auxiliar);
	lista->largo--;
	return(dato);
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)) return(NULL);
	return(lista->primero->dato);
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)) return(NULL);
	return(lista->ultimo->dato);
}

size_t lista_largo(const lista_t *lista){
	return(lista->largo);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	if(lista_esta_vacia(lista)) return;
	nodo_t* posicion=lista->primero;
	bool sigue=true;
	while(posicion!=NULL && sigue){
		sigue=visitar(posicion->dato,extra);
		posicion=posicion->siguiente;
	}
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	nodo_t* posicion=lista->primero;
	while(posicion!=NULL){
		if(destruir_dato!=NULL) destruir_dato(posicion->dato);
		nodo_t*puntero_aux=posicion;
		posicion=posicion->siguiente;
		free(puntero_aux);
	}
	free(lista);
}


/* *****************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iterador=malloc(sizeof(lista_iter_t));
	if(iterador==NULL) return(NULL);
	iterador->mi_lista=lista;
	iterador->posicion=lista->primero;
	iterador->posicion_anterior=lista->primero;
	return(iterador);
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return(false);
	if(!lista_esta_vacia(iter->mi_lista)) iter->posicion_anterior=iter->posicion;
	iter->posicion=iter->posicion->siguiente;
	return(true);
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter) || lista_esta_vacia(iter->mi_lista)) return(NULL);
	return(iter->posicion->dato);
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return(iter->posicion==NULL && iter->posicion_anterior==iter->mi_lista->ultimo);
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if(iter->posicion == iter->mi_lista->primero){
		if(lista_insertar_primero(iter->mi_lista,dato)){
			iter->posicion=iter->mi_lista->primero;
			iter->posicion_anterior=iter->mi_lista->primero;
			return(true);
		}
		return (false);
	} 
	if(lista_iter_al_final(iter)){
		if(lista_insertar_ultimo(iter->mi_lista,dato)){
			iter->posicion=iter->posicion_anterior->siguiente;
			return(true);
		}
		return(false);
	}
	nodo_t* nodo_nuevo=crear_nodo(dato,iter->posicion);
	if(nodo_nuevo==NULL) return(false);
	iter->posicion=nodo_nuevo;
	iter->posicion_anterior->siguiente=nodo_nuevo;
	iter->mi_lista->largo++;
	return(true);
	
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_esta_vacia(iter->mi_lista) || lista_iter_al_final(iter)) return(NULL);
	void* dato_borrado=iter->posicion->dato;
	nodo_t* puntero_aux=iter->posicion;
	if(iter->posicion==iter->mi_lista->primero){
		lista_borrar_primero(iter->mi_lista);
		iter->posicion=iter->mi_lista->primero;
		iter->posicion_anterior=iter->mi_lista->primero;
		return(dato_borrado);
	}
	if(iter->posicion==iter->mi_lista->ultimo){
		iter->mi_lista->ultimo=iter->posicion_anterior;
		iter->posicion=NULL;
		iter->posicion_anterior->siguiente=NULL;
		iter->mi_lista->largo--;
		free(puntero_aux);
		return(dato_borrado);
	}
	iter->posicion=puntero_aux->siguiente;
	iter->posicion_anterior->siguiente=iter->posicion;
	iter->mi_lista->largo--;
	free(puntero_aux);
	return(dato_borrado);
}
