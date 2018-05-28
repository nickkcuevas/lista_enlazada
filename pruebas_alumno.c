#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

int get_int(void* dato){
    return *((int*)dato);
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

    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}


void pruebas_lista_volumen() {
    printf("INICIO DE PRUEBAS LISTA VOLUMEN \n");
}


void pruebas_lista_alumno() {
    pruebas_lista_vacia();
    printf("------------------\n");
    pruebas_lista_pocos_elementos();
    printf("------------------\n");
    pruebas_lista_volumen();
}
