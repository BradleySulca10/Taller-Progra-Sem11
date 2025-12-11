#include <stdio.h>
#include <string.h>
#include "funciones.h"

/* Prototipo para limpiar el buffer si usas scanf en algun lugar (no necesario aqui) */
static void limpiarStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(void) {
    Libro biblioteca[MAX_LIBROS];
    int contador;
    int opcion;

    inicializarBiblioteca(biblioteca, &contador);

    do {
        printf("\n--- MENU BIBLIOTECA ---\n");
        printf("1. Agregar libro\n");
        printf("2. Buscar libro por ID\n");
        printf("3. Buscar libro por titulo\n");
        printf("4. Actualizar estado\n");
        printf("5. Mostrar libros\n");
        printf("6. Eliminar libro\n");
        printf("7. Salir\n");
        printf("Selecciona una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Reiniciando opcion.\n");
            limpiarStdin();
            opcion = -1;
        } else {
            limpiarStdin(); /* quitar el newline despues del scanf */
        }

        switch (opcion) {
            case 1:
                agregarLibro(biblioteca, &contador);
                break;
            case 5:
                mostrarLibros(biblioteca, contador);
                break;
            case 2: {
                char id[MAX_ID];
                printf("ID: ");
                /* usar fgets para leer linea */
                if (fgets(id, MAX_ID, stdin) == NULL) id[0] = '\0';
                id[strcspn(id, "\n")] = '\0';
                int pos = buscarLibroPorID(biblioteca, contador, id);
                if (pos >= 0) {
                    const Libro *l = &biblioteca[pos];
                    printf("Libro encontrado:\nID: %s\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                           l->id, l->titulo, l->autor, l->anio, l->estado);
                } else {
                    printf("No existe libro con ID '%s'.\n", id);
                }
                break;
            }
            case 3: {
                char titulo[MAX_TITULO];
                printf("Titulo: ");
                if (fgets(titulo, MAX_TITULO, stdin) == NULL) titulo[0] = '\0';
                titulo[strcspn(titulo, "\n")] = '\0';
                int pos = buscarLibroPorTitulo(biblioteca, contador, titulo);
                if (pos >= 0) {
                    const Libro *l = &biblioteca[pos];
                    printf("Libro encontrado:\nID: %s\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                           l->id, l->titulo, l->autor, l->anio, l->estado);
                } else {
                    printf("No existe libro con titulo parecido a '%s'.\n", titulo);
                }
                break;
            }
            case 4:
                actualizarEstado(biblioteca, contador);
                break;
            case 6:
                eliminarLibro(biblioteca, &contador);
                break;
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
