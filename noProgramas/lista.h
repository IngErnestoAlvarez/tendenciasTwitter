#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdio.h>


typedef struct lista lista_t;

/*
 *Crea una lista enlazada.
 *pre:-
 *post:Devuelve una lista vacia.
*/
lista_t *lista_crear(void);

/*
 *Dada una lista devuelve verdadero si la misma tiene elementos o falso si no.
 *pre:Exista la lista.
 *post:-
*/
bool lista_esta_vacia(const lista_t *lista);

/*
 *Dada una lista le inserta al principio el dato que se le pase, devuelve verdadero
 *si se pudo insertar el dato, o falso si ocurrio algun error
 *pre:Existe la lista
 *post:Se agrego un elemento al principio de la lista.
*/
bool lista_insertar_primero(lista_t *lista, void *dato);

/*
 *Dada una lista le inserta al final el dato que se le pase, devolviendo verdadero
 *si se pudo insertar el dato, o falso si ocurrio algun error.
 *pre:Existe la lista
 *post:Se agrego un elemento al final de la lista
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/*
 *Elimina el primer dato de la lista, y libera su memoria, devolviendo el valor del dato.
 *Si la lista esta vacia, devuelve NULL.
 *pre:Existe la lista.
 *post:El primer elemento de la lista fue eliminado.
*/
void *lista_borrar_primero(lista_t *lista);

/*
 *Devuelve el primer elemento de la lista. En caso de estar vacia da NULL
 *pre:Existe la lista.
 *post:Devuelve el dato que esta en el primer lugar, si la lista esta vacia da NULL.
*/
void *lista_ver_primero(const lista_t *lista);

/*
 *Devuelve el ultimo elemento de la lista. En caso de estar vacia da NULL
 *pre:Existe la lista.
 *post:Devuelve el dato que esta en el ultimo lugar, si la lista esta vacia da NULL.
*/
void *lista_ver_ultimo(const lista_t* lista);

/*
 *Devuelve el largo de la lista, cuando esta vacia devuelve 0.
 *pre:Existe la lista.
 *post:Devuelve un size_t que indica el largo de la lista.
*/
size_t lista_largo(const lista_t *lista);

/*
 *Destruye la lista. Si se recibe la funcion destruir_dato por parametro,
 *para cada uno de los elementos de la lista llama a destruir_dato.
 *pre:Existe la lista, destruir_dato es una funcion que puede eliminar el/los dato(s)
 *    de la lista, y es NULL si no se utiliza.
 *post:Se eliminaron todos los elementos de la lista.
*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/*
 *Recorre toda la lista aplicando la funcion visitar, si visitar devuelve false, se detiene la iteracion
 *pre:La lista existe. 
 *post:Se recorre toda la lista aplicando visitar a todos sus datos.
*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);




/* *****************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/



typedef struct lista_iter lista_iter_t;


/*
 *Crea un iterador de la lista.
 *pre:-
 *post:Devuelve el iterador apuntando al primero de la lista, devuelve NULL si no hay memoria.
*/
lista_iter_t *lista_iter_crear(lista_t *lista);
/*
 *Avanza el iterador, devuelve verdadero si pudo avanzar, falso si llego al final.
 *pre:Existe el iterador.
 *post:Si devuelve verdadero, el iteroador avanzo una posicion, si no, llego al final.
*/
bool lista_iter_avanzar(lista_iter_t *iter);
/*
 *Devuelve el dato al cual este apuntando el iterador. Si la lista esta vacia(o esta al final) devuelve NULL.
 *pre:Existe el iterador.
 *post:Devuelve el dato al cual esta apuntando. Si la lista esta vacia(o esta al final) devuelve NULL.
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);
/*
 *Devuelve verdadero o falso dependiendo si el iterador esta en el final de la lista.
 *pre:Existe el iterador
 *post:Devuelve verdadero o falso dependiendo si el iterador esta en el final de la lista.
*/
bool lista_iter_al_final(const lista_iter_t *iter);
/*
 *Libera la memoria del iterador
 *pre:Existe el iterador
 *post:Se libero el iterador.
*/
void lista_iter_destruir(lista_iter_t *iter);
/*
 *Inserta un dato en la posicion del iterador y devuelve verdadero, falso en caso de error.
 *pre:Existe el iterador
 *post:Devuelve un booleano indicando si se pudo realizar el insertamiento o no.
*/
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
/*
 *Elimina el elemento de la lista apuntado por el iterador
 *pre:Existe la lista
 *post:Devuelve el valor eliminado, la lista ya no lo contiene.
*/
void *lista_iter_borrar(lista_iter_t *iter);




#endif // LISTA_H