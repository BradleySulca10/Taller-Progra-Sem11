#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

/* Helper: lee linea con fgets y remueve el newline final si existe */
static void leerLinea(char *buffer, int tam) {
    if (fgets(buffer, tam, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0'; /* quitar '\n' */
}

/* Helper: comparacion case-insensitive simple */
static int compararCaseInsensitive(const char *a, const char *b) {
    while (*a && *b) {
        char ca = (char) tolower((unsigned char)*a);
        char cb = (char) tolower((unsigned char)*b);
        if (ca != cb) return (ca < cb) ? -1 : 1;
        a++; b++;
    }
    if (*a) return 1;
    if (*b) return -1;
    return 0;
}

void inicializarBiblioteca(Libro biblioteca[], int *contador) {
    (void) biblioteca; /* no usado ahora pero queda por claridad */
    *contador = 0;
}

int buscarLibroPorID(const Libro biblioteca[], int contador, const char *idBuscado) {
    for (int i = 0; i < contador; ++i) {
        if (strcmp(biblioteca[i].id, idBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarLibroPorTitulo(const Libro biblioteca[], int contador, const char *tituloBuscado) {
    for (int i = 0; i < contador; ++i) {
        if (compararCaseInsensitive(biblioteca[i].titulo, tituloBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

void agregarLibro(Libro biblioteca[], int *contador) {
    if (*contador >= MAX_LIBROS) {
        printf("ERROR: No se pueden agregar mas libros (max %d).\n", MAX_LIBROS);
        return;
    }

    char buffer[MAX_TITULO + 10];
    Libro nuevo;

    printf("ID (alfanumerico, max %d): ", MAX_ID - 1);
    leerLinea(nuevo.id, MAX_ID);
    if (strlen(nuevo.id) == 0) {
        printf("ID invalido.\n");
        return;
    }
    if (buscarLibroPorID(biblioteca, *contador, nuevo.id) != -1) {
        printf("ERROR: ID ya existe.\n");
        return;
    }

    printf("Titulo: ");
    leerLinea(nuevo.titulo, MAX_TITULO);
    if (strlen(nuevo.titulo) == 0) {
        printf("Titulo invalido.\n");
        return;
    }

    printf("Autor: ");
    leerLinea(nuevo.autor, MAX_AUTOR);
    if (strlen(nuevo.autor) == 0) {
        printf("Autor invalido.\n");
        return;
    }

    printf("Anio de publicacion: ");
    leerLinea(buffer, sizeof(buffer));
    char *endptr;
    long anio = strtol(buffer, &endptr, 10);
    if (endptr == buffer || anio < 0 || anio > 3000) {
        printf("Anio invalido.\n");
        return;
    }
    nuevo.anio = (int) anio;

    strncpy(nuevo.estado, "Disponible", MAX_ESTADO);
    nuevo.estado[MAX_ESTADO-1] = '\0';

    biblioteca[*contador] = nuevo;
    (*contador)++;
    printf("Libro agregado correctamente.\n");
}

void mostrarLibros(const Libro biblioteca[], int contador) {
    if (contador == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n%-4s | %-19s | %-40s | %-20s | %-10s\n", "Pos", "ID", "Titulo", "Autor", "Anio/Estado");
    printf("----+---------------------+------------------------------------------+----------------------+----------------\n");
    for (int i = 0; i < contador; ++i) {
        printf("%-4d | %-19s | %-40s | %-20s | %4d / %s\n",
               i + 1,
               biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               biblioteca[i].anio,
               biblioteca[i].estado);
    }
}

void actualizarEstado(Libro biblioteca[], int contador) {
    if (contador == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    char id[MAX_ID];
    printf("ID del libro para cambiar estado: ");
    leerLinea(id, MAX_ID);

    int pos = buscarLibroPorID(biblioteca, contador, id);
    if (pos == -1) {
        printf("No se encontro libro con ID '%s'.\n", id);
        return;
    }

    if (compararCaseInsensitive(biblioteca[pos].estado, "Disponible") == 0) {
        strncpy(biblioteca[pos].estado, "Prestado", MAX_ESTADO);
    } else {
        strncpy(biblioteca[pos].estado, "Disponible", MAX_ESTADO);
    }
    biblioteca[pos].estado[MAX_ESTADO-1] = '\0';
    printf("Estado actualizado: %s -> %s\n", id, biblioteca[pos].estado);
}

void eliminarLibro(Libro biblioteca[], int *contador) {
    if (*contador == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    char id[MAX_ID];
    printf("ID del libro a eliminar: ");
    leerLinea(id, MAX_ID);

    int pos = buscarLibroPorID(biblioteca, *contador, id);
    if (pos == -1) {
        printf("No se encontro libro con ID '%s'.\n", id);
        return;
    }

    /* mover todos los siguientes una posicion hacia atras */
    for (int i = pos; i < (*contador) - 1; ++i) {
        biblioteca[i] = biblioteca[i + 1];
    }
    (*contador)--;
    printf("Libro con ID '%s' eliminado.\n", id);
}
