#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>

#define MAX_LIBROS 10
#define MAX_TITULO 100
#define MAX_AUTOR 50
#define MAX_ID 20
#define MAX_ESTADO 15

typedef struct {
    char id[MAX_ID];
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int anio;
    char estado[MAX_ESTADO];
} Libro;

void inicializarBiblioteca(Libro biblioteca[], int *contador);
void agregarLibro(Libro biblioteca[], int *contador);
void mostrarLibros(const Libro biblioteca[], int contador);
int buscarLibroPorID(const Libro biblioteca[], int contador, const char *idBuscado);
int buscarLibroPorTitulo(const Libro biblioteca[], int contador, const char *tituloBuscado);
void actualizarEstado(Libro biblioteca[], int contador);
void eliminarLibro(Libro biblioteca[], int *contador);

#endif 
