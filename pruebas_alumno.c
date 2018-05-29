#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
size_t CANT_GUARDAR = 500; 

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

int get_int(void* dato){
    return *((int*)dato);
}

void pila_destruir_wrapper(void* pila){
    pila_destruir(pila);
}

// /* ******************************************************************
//  *                   PRUEBAS UNITARIAS ALUMNO
//  * *****************************************************************/


void pruebas_lista_vacia() {
    printf("INICIO DE PRUEBAS CON LISTA VACIA \n");
    lista_t* lista = lista_crear();

    print_test("La lista fue creada es true", lista != NULL);
    print_test("La lista esta vacia es true", lista_esta_vacia(lista) == true);
    print_test("Lista largo devuelve 0", lista_largo(lista) == 0);
    print_test("Lista ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Lista borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}


void pruebas_lista_pocos_elementos() {
    printf("INICIO DE PRUEBAS LISTA POCOS ELEMENTOS \n");
    lista_t* lista = lista_crear();
    int elementos[] = {1,2,3};

    print_test("Lista insertar 1 al principio devuelve true", lista_insertar_primero(lista, &elementos[0]) == true);
    print_test("Lista esta vacia devuelve false", lista_esta_vacia(lista) == false);
    print_test("Lista largo devuelve 1", lista_largo(lista) == 1);
    print_test("Lista insertar 2 al final devuelve true", lista_insertar_ultimo(lista, &elementos[1]) == true);
    print_test("Lista largo devuelve 2", lista_largo(lista) == 2);
    print_test("Lista insertar 3 al final devuelve true", lista_insertar_ultimo(lista, &elementos[2]) == true);
    print_test("Lista largo devuelve 3", lista_largo(lista) == 3);
    print_test("Lista borrar primero devuelve 1", get_int(lista_borrar_primero(lista)) == elementos[0]);
    print_test("Lista ver primero devuelve 2", get_int(lista_ver_primero(lista)) == elementos[1]);   
    print_test("Lista ver ultimo devuelve 3", get_int(lista_ver_ultimo(lista)) == elementos[2]);
    print_test("Lista insertar 3 al principio devuelve true", lista_insertar_primero(lista, lista_ver_ultimo(lista)) == true);   
    print_test("Lista ver primero devuelve 3", get_int(lista_ver_primero(lista)) == elementos[2]);
    print_test("Lista largo devuelve 3", lista_largo(lista) == 3);
    print_test("Lista insertar 1 al final devuelve true", lista_insertar_ultimo(lista, &elementos[0]) == true);
    
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}


void pruebas_lista_volumen() {
    printf("INICIO DE PRUEBAS LISTA VOLUMEN \n");

    lista_t* lista = lista_crear();    
    pila_t** pilas = malloc(CANT_GUARDAR * sizeof(pila_t*));
    for (int i=0; i< CANT_GUARDAR; i++){
        pila_t* pila = pila_crear();
        pilas[i] = pila;
    }
    bool insertando_ok = true;
    for (int i=0; i< CANT_GUARDAR; i++){
        if(!lista_insertar_primero(lista, pilas[i])){
            insertando_ok = false;
        }
    }
    printf("Lista insertar al principio ");
    printf("%zd elementos de tipo pila ", CANT_GUARDAR);
    print_test("devuelve True", insertando_ok == true);
    print_test("Lista esta vacia devuelve False", lista_esta_vacia(lista) == false);
    printf("Lista largo devuelve ");
    printf("%zd", CANT_GUARDAR);
    print_test("", lista_largo(lista) == CANT_GUARDAR);
    

    lista_destruir(lista, pila_destruir_wrapper);
    free(pilas);
    print_test("Se eliminaron todos los elementos de la Lista", true);
}


void pruebas_lista_alumno() {
    pruebas_lista_vacia();
    printf("------------------\n");
    pruebas_lista_pocos_elementos();
    printf("------------------\n");
    pruebas_lista_volumen();
}
