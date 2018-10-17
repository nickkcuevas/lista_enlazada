CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
FILE_OUTPUT = pruebas
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 


build: lista.c lista.h pila.c pila.h testing.c testing.h pruebas_alumno.c main.c
	$(CC) $(CFLAGS) lista.c pila.c testing.c pruebas_alumno.c main.c -o pruebas

valgrind: build
	valgrind $(VFLAGS) ./pruebas

run: build valgrind
	./pruebas

