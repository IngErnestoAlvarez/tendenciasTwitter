#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

#define TAM_MIN 100
#define MULT_REDIMENSIONAR 2
#define DIV_REDIMENSIONAR 4

struct heap{
    void** array;
    size_t cant;
    size_t cap;
    cmp_func_t cmp;
};
/**********************************************/
/* FUNCIONES AUXILIARES */
/*********************************************/
void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
}

bool heap_redimensionar(heap_t* heap, size_t nuevo){
    void** aux = realloc(heap->array, sizeof(void*) * nuevo);
    if(!aux) return false;
    heap->array = aux;
    heap->cap = nuevo;
    return true;
}

void downheap(void** arreglo, size_t cant, size_t pos, cmp_func_t cmp){
	size_t hijo_izq = (2 * pos) + 1;
	size_t hijo_der = (2 * pos) + 2;
	if((hijo_izq >= cant)) return;
	if(hijo_der >= cant){
		if(cmp(arreglo[pos], arreglo[hijo_izq]) < 0){
			swap(&arreglo[pos], &arreglo[hijo_izq]);
		}
		return;
	}
	size_t hijo_mayor = 0;
	if(cmp(arreglo[hijo_der], arreglo[hijo_izq]) > 0) hijo_mayor = hijo_der;
	else hijo_mayor = hijo_izq;
	if(cmp(arreglo[hijo_mayor], arreglo[pos]) > 0){
		swap(&arreglo[hijo_mayor], &arreglo[pos]);
		downheap(arreglo, cant, hijo_mayor, cmp);
	}
	return;
}

void upheap(void** arreglo, size_t pos, cmp_func_t cmp){
	if(!pos) return;
	size_t padre = (pos - 1)/2;
	if(cmp(arreglo[pos], arreglo[padre])>0){
		swap(&arreglo[pos], &arreglo[padre]);
		upheap(arreglo, padre, cmp);
	}
	return;
}

void heapify(void* arreglo, size_t n, cmp_func_t cmp){
    for(int i = 0; i<n; i++){
        downheap(arreglo,n, n-i-1, cmp);
    }
}
/**********************************************/
/* HEAP_SORT */
/*********************************************/

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);
    for(int i = 0; i < cant; i++){
        swap(&elementos[0], &elementos[cant-i-1]);
        downheap(elementos, cant-i-1, 0, cmp);
    }
}

/**********************************************/
/* FUNCIONES HEAP */
/*********************************************/
heap_t *heap_crear(cmp_func_t cmp){
    heap_t* nuevo = malloc(sizeof(heap_t));
    if(!nuevo) return NULL;
    nuevo->cant = 0;
    nuevo->cap = TAM_MIN;
    nuevo->array = malloc(sizeof(void*)*(nuevo->cap));
    if(!nuevo->array){
        free(nuevo);
        return NULL;
    }
    nuevo->cmp = cmp;
    return nuevo;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* nuevo = malloc(sizeof(heap_t));
    if(!nuevo) return NULL;
    nuevo->cant = n;
	nuevo->cap = TAM_MIN;
    nuevo->array = malloc(sizeof(void*)*(nuevo->cap));
    if(!nuevo->array){
        free(nuevo);
        return NULL;
    }
    for(int i = 0; i<n; i++) nuevo->array[i] = arreglo[i];
    nuevo->cmp = cmp;
    heapify(nuevo->array, n, cmp);
    return nuevo;
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
    return(!heap->cant);
}

void *heap_ver_max(const heap_t *heap){
    if(heap_esta_vacio(heap)) return NULL;
    return heap->array[0];
}

bool heap_encolar(heap_t *heap, void *elem){
	if(heap_esta_vacio(heap)){
		heap->array[0] = elem;
		heap->cant++;
		return true;
	}
    if(heap->cant == heap->cap){
        if(!heap_redimensionar(heap, heap->cap*MULT_REDIMENSIONAR)) return false;
    }
    heap->array[heap->cant] = elem;
    upheap(heap->array, heap->cant, heap->cmp);
    heap->cant++;
	return true;
}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap)) return NULL;
    heap->cant--;
    if((heap->cant == (heap->cap)/DIV_REDIMENSIONAR)&&(heap->cap > TAM_MIN)) heap_redimensionar(heap, heap->cap/MULT_REDIMENSIONAR);
    swap(&heap->array[0], &heap->array[heap->cant]);
    downheap(heap->array, heap->cant, 0, heap->cmp);
    return heap->array[heap->cant];
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(destruir_elemento) for(int i = 0; i < heap->cant; i++) destruir_elemento(heap->array[i]);
    free(heap->array);
    free(heap);
}
