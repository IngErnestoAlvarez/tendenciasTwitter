#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

#define TAMANIO 4
#define MULTIPLICADOR 2

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    if(!pila) return NULL;
    pila->capacidad = TAMANIO;
    pila->cantidad = 0;
    pila->datos = malloc(sizeof(void*) * pila->capacidad);
    if(!pila->datos){
        free(pila);
        return NULL;
    }
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return(!pila->cantidad);
}

bool pila_redimensionar(pila_t* pila, size_t nuevo){
    void** aux = realloc(pila->datos, sizeof(void*) * nuevo);
    if(!aux) return false;
    pila->datos = aux;
    pila->capacidad = nuevo;
    return true;
}

bool pila_apilar(pila_t *pila, void* valor){
    /*if(pila->cantidad == pila->capacidad){
        if(!pila_redimensionar(pila, pila->capacidad*MULTIPLICADOR)) return false;
    }*/
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void* pila_ver_tope(const pila_t *pila){
    if(pila_esta_vacia(pila)) return NULL;
    return(pila->datos[pila->cantidad-1]);
}

void* pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila)) return NULL;
    pila->cantidad--;
    if((pila->cantidad < (pila->capacidad/MULTIPLICADOR) ) && (pila->capacidad>TAMANIO)){
        pila_redimensionar(pila, pila->capacidad/MULTIPLICADOR);
    }
    return (pila->datos[pila->cantidad]);
}