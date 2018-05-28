#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/


// /* ******************************************************************
//  *                   PRUEBAS UNITARIAS ALUMNO
//  * *****************************************************************/


void pruebas_cola_vacia() {
    printf("INICIO DE PRUEBAS CON LISTA VACIA \n");
}


void pruebas_cola_pocos_elementos() {
    printf("INICIO DE PRUEBAS LISTA POCOS ELEMENTOS \n");
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
