#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;

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

/*******************************************************************
 *                PRIMITIVAS DE ITERADOR INTERNO
 ******************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/*******************************************************************
 *                PRIMITIVAS DE ITERADOR EXTERNO
 ******************************************************************/


lista_iter_t *lista_iter_crear(lista_t *lista);


bool lista_iter_avanzar(lista_iter_t *iter);


void *lista_iter_ver_actual(const lista_iter_t *iter);


bool lista_iter_al_final(const lista_iter_t *iter);


void lista_iter_destruir(lista_iter_t *iter);


bool lista_iter_insertar(lista_iter_t *iter, void *dato);


void *lista_iter_borrar(lista_iter_t *iter);


#endif