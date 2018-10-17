#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
size_t CANT_INSERTAR_INICIO = 200;
size_t CANT_INSERTAR_ULTIMO = 300;

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

int get_int(void* dato){
    return *((int*)dato);
}

void pila_destruir_wrapper(void* pila){
    pila_destruir(pila);
}

void visitar(void* extra){

}

bool sumar(void* dato, void* extra){
    int valor = *(int*)dato + *(int*)extra; 
    *(int*)extra = valor;
    return true;
}

bool visitar_wrapper(void* dato, void* extra){
    return sumar(dato, extra);
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
    pila_t** pilas_inicio = malloc(CANT_INSERTAR_INICIO * sizeof(pila_t*));
    for (int i=0; i< CANT_INSERTAR_INICIO; i++){
        pila_t* pila = pila_crear();
        pilas_inicio[i] = pila;
    }
    bool insertando_primero_ok = true;
    for (int i=0; i< CANT_INSERTAR_INICIO; i++){
        if(!lista_insertar_primero(lista, pilas_inicio[i])){
            insertando_primero_ok = false;
        }
    }
    printf("Lista insertar al principio ");
    printf("%zd elementos de tipo pila ", CANT_INSERTAR_INICIO);
    print_test("devuelve True", insertando_primero_ok == true);
    print_test("Lista esta vacia devuelve False", lista_esta_vacia(lista) == false);
    printf("Lista largo devuelve ");
    printf("%zd", CANT_INSERTAR_INICIO);
    print_test("", lista_largo(lista) == CANT_INSERTAR_INICIO);
    
    pila_t** pilas_final = malloc(CANT_INSERTAR_ULTIMO * sizeof(pila_t*));
    for (int i=0; i< CANT_INSERTAR_ULTIMO; i++){
        pila_t* pila = pila_crear();
        pilas_final[i] = pila;
    }
    bool insertando_ultimo_ok = true;
    for (int i=0; i< CANT_INSERTAR_ULTIMO; i++){
        if(!lista_insertar_ultimo(lista, pilas_final[i])){
            insertando_ultimo_ok = false;
        }
    }
    
    printf("Lista insertar al final ");
    printf("%zd elementos de tipo pila ", CANT_INSERTAR_ULTIMO);
    print_test("devuelve True", insertando_ultimo_ok == true);
    printf("Lista largo devuelve ");
    printf("%zd", CANT_INSERTAR_ULTIMO + CANT_INSERTAR_INICIO);
    print_test("", lista_largo(lista) == CANT_INSERTAR_ULTIMO + CANT_INSERTAR_INICIO);
    
    lista_destruir(lista, pila_destruir_wrapper);
    free(pilas_inicio);
    free(pilas_final);
    print_test("Se eliminaron todos los elementos de la Lista", true);
}


void pruebas_lista_vacia_con_iterador_externo() {
    printf("INICIO DE PRUEBAS LISTA VACIA CON ITERADOR EXTERNO \n");
    lista_t* lista = lista_crear();

    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("El iterador fue creado es true", iter != NULL);
    print_test("El iterador esta al final es true", lista_iter_al_final(iter) == true);
    print_test("Iterador ver actual devuelve NULL es true", lista_iter_ver_actual(iter) == NULL);
    print_test("Iterador avanzar devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Iterador borrar devuelve NULL", lista_iter_borrar(iter) == NULL);

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
    print_test("La lista fue destruida", true);
    print_test("El iterador fue destruido", true);
}


void pruebas_lista_con_pocos_elementos_con_iterador_externo() {
    printf("INICIO DE PRUEBAS LISTA CON POCOS ELEMENTOS CON ITERADOR EXTERNO \n");
    lista_t* lista = lista_crear();
    int elementos[] = {1,2,3};
    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("Iterador esta al final es true", lista_iter_al_final(iter) == true);
    print_test("Iterador insertar 1 es true", lista_iter_insertar(iter, &elementos[0]) == true);
    print_test("Largo de lista es 1", lista_largo(lista) == 1);
    print_test("Iterador ver actual es 1",get_int(lista_iter_ver_actual(iter)) == elementos[0]);
    print_test("Iterador esta al final es false", lista_iter_al_final(iter) == false);
    print_test("Iterador insertar 2 es true", lista_iter_insertar(iter, &elementos[1]) == true);
    print_test("Largo de lista es 2", lista_largo(lista) == 2);
    print_test("Iterador ver actual es 2",get_int(lista_iter_ver_actual(iter)) == elementos[1]);
    print_test("Iterador esta al final es false", lista_iter_al_final(iter) == false);
    print_test("Iterador avanzar es true", lista_iter_avanzar(iter) == true);
    print_test("Iterador ver actual es 1",get_int(lista_iter_ver_actual(iter)) == elementos[0]);
    print_test("Iterador esta al final es false", lista_iter_al_final(iter) == false);
    print_test("Iterador avanzar es true", lista_iter_avanzar(iter) == true);
    print_test("Iterador esta al final es true", lista_iter_al_final(iter) == true);
    print_test("Iterador insertar 3 es true", lista_iter_insertar(iter, &elementos[2]) == true);
    print_test("Largo de lista es 3", lista_largo(lista) == 3);
    print_test("Iterador ver actual es 3",get_int(lista_iter_ver_actual(iter)) == elementos[2]);
    
    lista_iter_t* iter_borrar = iter;
    iter = lista_iter_crear(lista);
    lista_iter_destruir(iter_borrar);
    
    print_test("El primer iterador fue destruido", true);
    print_test("Iterador esta al final es false", lista_iter_al_final(iter) == false);
    print_test("Largo de lista es 3", lista_largo(lista) == 3);
    print_test("Iterador ver actual es 2",get_int(lista_iter_ver_actual(iter)) == elementos[1]);
    print_test("Iterador borrar es 2", get_int(lista_iter_borrar(iter)) == elementos[1]);
    print_test("Largo de lista es 2", lista_largo(lista) == 2);
    print_test("Iterador ver actual es 1",get_int(lista_iter_ver_actual(iter)) == elementos[0]);
    print_test("Iterador borrar es 1", get_int(lista_iter_borrar(iter)) == elementos[0]);
    print_test("Largo de lista es 1", lista_largo(lista) == 1);
    print_test("Iterador ver actual es 3",get_int(lista_iter_ver_actual(iter)) == elementos[2]);
    print_test("Iterador borrar es 3", get_int(lista_iter_borrar(iter)) == elementos[2]);
    print_test("Largo de lista es 1", lista_largo(lista) == 0);
    print_test("Iterador esta al final es true", lista_iter_al_final(iter) == true);
    
    print_test("Iterador insertar 1 es true", lista_iter_insertar(iter, &elementos[0]) == true);
    print_test("Iterador insertar 2 es true", lista_iter_insertar(iter, &elementos[1]) == true);
    print_test("Iterador insertar 3 es true", lista_iter_insertar(iter, &elementos[2]) == true);
    print_test("Iterador avanzar es true", lista_iter_avanzar(iter) == true);
    print_test("Iterador ver actual es 2",get_int(lista_iter_ver_actual(iter)) == elementos[1]);
    print_test("Iterador borrar es 2", get_int(lista_iter_borrar(iter)) == elementos[1]);
    print_test("Iterador ver actual es 1",get_int(lista_iter_ver_actual(iter)) == elementos[0]);
    print_test("Iterador avanzar es true", lista_iter_avanzar(iter) == true);
    print_test("Iterador esta al final es true", lista_iter_al_final(iter) == true);
    print_test("Iterador borrar es NULL", lista_iter_borrar(iter) == NULL);
    
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

    print_test("La lista fue destruida", true);
    print_test("El iterador fue destruido", true);
}

void pruebas_lista_con_iterador_interno() {
    printf("INICIO DE PRUEBAS LISTA CON ITERADOR INTERNO \n");
    lista_t* lista = lista_crear();
    int elementos[] = {1,2,3,4,5};
    int cant_elem = 5;
    int total = 0;
    bool insertando_primero_ok = true;
    for (int i=0; i < cant_elem; i++){
        total += elementos[i];
        if (!lista_insertar_primero(lista, &elementos[i])){
            insertando_primero_ok = false;
        }
    }
    print_test("Lista insertar al principio primeros 5 numeros naturales es true", insertando_primero_ok == true);
    int total_lista_iterar = 0;
    lista_iterar(lista, visitar_wrapper, &total_lista_iterar);

    printf("Lista total de iterar en Lista es %d", total);
    print_test(" es true", total == total_lista_iterar);
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}


void pruebas_lista_alumno() {
    pruebas_lista_vacia();
    printf("------------------\n");
    pruebas_lista_pocos_elementos();
    printf("------------------\n");
    pruebas_lista_volumen();
    printf("------------------\n");
    pruebas_lista_vacia_con_iterador_externo();
    printf("------------------\n");
    pruebas_lista_con_pocos_elementos_con_iterador_externo();
    printf("------------------\n");
    pruebas_lista_con_iterador_interno();
}