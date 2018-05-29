#include "pila.h"
#include <stdlib.h>
size_t TAMANIO_INICIAL = 100;
size_t DIVISOR_REDIMENSION = 4;
size_t MAXIMIZAR_CAPACIDAD = 3;
size_t REDUCIR_CAPACIDAD = 2;

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Redimensiona el tamaño de La Pila.
//Pre: La pila fue creada.
//Post: Redimensiona el tamaño de La Pila.
bool pila_redimensionar(pila_t* pila, size_t factor_redimension){
    if(pila->capacidad < TAMANIO_INICIAL){
        return false;
    };
    void** datos_nuevo = realloc(pila->datos, factor_redimension * sizeof(void*));
    if (!datos_nuevo){
        free(datos_nuevo);
        return false;
    }
    pila->datos = datos_nuevo;
    pila->capacidad = factor_redimension;
    return true;
}


pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    if (pila == NULL) return NULL;
    pila->cantidad = 0;
    pila->capacidad = TAMANIO_INICIAL;
    pila->datos = malloc(sizeof(void*) * pila->capacidad);
    if (pila->datos == NULL){
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
    return pila->cantidad == 0;
}


bool pila_apilar(pila_t *pila, void* valor){
    if (pila->cantidad == pila->capacidad){
        size_t factor_redimension = pila->capacidad * MAXIMIZAR_CAPACIDAD;
        pila_redimensionar(pila, factor_redimension);
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void* pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    void* tope = pila->datos[pila->cantidad - 1];
    return tope;
}


void* pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    void* tope = pila_ver_tope(pila);
    pila->cantidad--;
    if (pila->cantidad  <= (pila->capacidad / DIVISOR_REDIMENSION)){
        size_t factor_redimension = pila->capacidad / REDUCIR_CAPACIDAD;
        pila_redimensionar(pila, factor_redimension);
    }
    return tope;
}

        