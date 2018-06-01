#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
struct nodo;
typedef struct nodo nodo_t;

struct nodo {
    void* dato;
    nodo_t* proximo;
};

struct lista {
    size_t largo;    
    nodo_t* primero;
    nodo_t* ultimo;
};


struct lista_iter {
    nodo_t* actual;
    nodo_t* anterior;
    lista_t* lista;
};


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/


nodo_t* nodo_crear(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL; 
    nodo->dato = dato;
    nodo->proximo = NULL;
    return nodo;
}

void* nodo_destruir(nodo_t* nodo){
    void* dato = nodo->dato;
    free(nodo);
    return dato;
}


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/


lista_t* lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->largo = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}


void lista_destruir(lista_t *lista, void destruir_dato(void *)){
    while(!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato){
            destruir_dato(dato);
        }
    }
    free(lista);
}


bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}


size_t lista_largo(const lista_t *lista){
    return lista->largo;
}


bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nodo = nodo_crear(dato);
    if(!nodo) return false;    
    if (lista_esta_vacia(lista)){
        lista->primero = nodo;
        lista->ultimo = nodo;
    }
    else{
        nodo->proximo = lista->primero;
        lista->primero = nodo;
    }  
    lista->largo++;
    return true;
}


bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nodo = nodo_crear(dato);
    if(!nodo) return false;
    if (lista_esta_vacia(lista)){
        lista->primero = nodo;
        lista->ultimo = nodo;
    }
   
    else if (lista->primero == lista->ultimo){
        lista->ultimo = nodo;
        lista->primero->proximo = lista->ultimo;
    }
    else{
        lista->ultimo->proximo = nodo;
        lista->ultimo = nodo;
    }
    lista->largo++;
    return true;
}


void* lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;
    nodo_t* nodo = lista->primero;
    lista->largo--;
    if (lista->primero == lista->ultimo){
        lista->primero = NULL;
        lista->ultimo = NULL;
    }
    else{
        lista->primero = lista->primero->proximo;
    }
    return nodo_destruir(nodo);
}


void* lista_ver_primero(const lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->primero->dato;
}


void* lista_ver_ultimo(const lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ultimo->dato;
}


/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    lista_iter_t* iter = lista_iter_crear(lista);
    while(!lista_iter_al_final(iter)){
        void* dato = lista_iter_ver_actual(iter);
        if (visitar){
            visitar(dato, extra);
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return;
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = NULL;
    return iter;
}


bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}


void* lista_iter_ver_actual(const lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return NULL;
    }
    void* dato = iter->actual->dato;
    return dato;
}


bool lista_iter_avanzar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->proximo;
    return true;
}


void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}


void* lista_iter_borrar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return NULL;
    }
    else if (iter->anterior == NULL){
        iter->actual = iter->actual->proximo;
        return lista_borrar_primero(iter->lista);
    }
    else if (iter->actual->proximo == NULL){
        iter->lista->ultimo = iter->anterior;
    }
    nodo_t* pivot = iter->actual;
    iter->actual = iter->actual->proximo;
    iter->anterior->proximo = iter->actual;
    iter->lista->largo--;
    return nodo_destruir(pivot);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    if (lista_iter_al_final(iter)){
        lista_insertar_ultimo(iter->lista, dato);
        iter->actual = iter->lista->ultimo;
    }
    else if (iter->anterior == NULL){
        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->primero;
    }
    else{
        nodo_t* nodo = nodo_crear(dato);
        if (!nodo) return false;
        iter->anterior->proximo = nodo;
        nodo->proximo = iter->actual;
        iter->actual = nodo;
        iter->lista->largo++;
    }
    return true;
}