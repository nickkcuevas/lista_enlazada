#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

struct nodo;
typedef struct nodo nodo_t;

typedef struct lista lista_t;


/*******************************************************************
 *                PRIMITIVAS DE LISTA ENLAZADA
 ******************************************************************/
// Aclaración: Al referirse a lista, abusando en si de la notación, se refiere
// a una Lista Enlazada.


// Crea una Lista Enlazada.
// Post: devuelve una nueva Lista Enlazada vacía.
lista_t* lista_crear(void);


// Se devuelve true si la lista contiene al menos un elemento.
// false en caso contrario.
// Pre: La Lista fue creada.
bool lista_esta_vacia(const lista_t *lista);


// Se devuelve true si se pudo insertar el dato al principio de
// la lista. false en caso contrario.
// Pre: La lista fue creada.
// Post: El largo de la lista crece.
bool lista_insertar_primero(lista_t *lista, void *dato);


// Se devuelve true si se pudo insertar el dato al final de la lista. false
// en caso contrario.
// Pre: La lista fue creada.
// Post: El largo de la lista crece.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Se devuelve un puntero al dato alojado al principio de la lista. Si esta está vacía
// se devuelve NULL.
// Pre: La lista fue creada.
// Post: El largo de la lista disminuye, excepto si el de esta es 0.
void* lista_borrar_primero(lista_t *lista);


// Se devuelve un puntero al dato alojado al principio de la lista. Si esta está vacía
// se devuelve NULL.
// Pre: La lista fue creada.
void* lista_ver_primero(const lista_t *lista);

// Se devuelve un puntero al dato alojado al final de la lista. Si esta está vacía
// se devuelve NULL.
// Pre: La lista fue creada.
void* lista_ver_ultimo(const lista_t* lista);

// Se devuelve un valor correspondiente a la cantidad de elementos que contenga la lista.
// Pre: La lista fue creada.
size_t lista_largo(const lista_t *lista);

// Se elimina la lista en si, sin considerar los datos que está aloja, en
// caso de pasarse por parámetro, también se eliminan los datos que esta aloja.
// Pre: La lista fue creada.
// Post: La lista fue destruida.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

#endif