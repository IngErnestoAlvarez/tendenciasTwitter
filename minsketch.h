#ifndef MINSKETCH_H
#define MINSKETCH_H
#include <stdbool.h>
typedef struct minsketch minsketch_t;

/*Crea un nuevo TDA minsketch, devuelve un puntero al struct,
 *si pudo ser creado exitosamente. En caso contrario, devuelve NULL.
 * Post: Crea un TDA minsketch.
 */
minsketch_t* min_crear();

/*Guarda un elemento en minsketch, si pudo ser guardado correctamente, devuelve true.
 * En caso contrario devuelve false.
 * Pre: minsketch fue creado.
 * Post: guarda el elemento en el TDA. 
 */
void min_guardar(minsketch_t* min, char* clave);

/* Devuelve la cantidad (que se estima) de veces que se guarda la clave solicitada.
 * Si devuelve 0, quiere decir que nunca fue guardada.
 * Pre: El TDA fue creado.
 */
int min_obtener(minsketch_t* min, const char* clave);

/* Destruye el minsketch pasado por parametro.
 * Pre: El TDA fue creado.
 * Post: Destruye minsketch (min)
 */
void min_destruir(minsketch_t* min);
#endif // MINSKETCH_H
