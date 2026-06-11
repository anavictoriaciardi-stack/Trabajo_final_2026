#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "habitacion.h"

int altaHabitacion(){
    FILE *archHab = fopen("habitaciones", "r+b");

    if (archHab == NULL) {
        archHab = fopen("habitaciones", "w+b");
        if (archHab == NULL) {
            printf("Error al crear archivo\n");
            return 0;
        }
    }

    stHabitacion habitacion;

    int continuar = 0;

    while (continuar == 0){
        int nro = 0;
        int existe = 0;

        printf("\nNumero de habitacion: ");

        if (scanf("%d", &nro) != 1){
            printf("Formato no valido\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');

            if (nro <= 0){
                printf("Numero no valido\n");
            } else {
                rewind(archHab);

                while (fread(&habitacion, sizeof(stHabitacion), 1, archHab) == 1){
                    if (habitacion.numero == nro){
                        existe = 1;
                        break;
                    }
                }

                if (existe == 1){
                    printf("Esa habitacion ya fue cargada\n");
                } else {
                    habitacion.numero = nro;
                    continuar = 1;
                }
            }
        }
    }

    continuar = 0;

    while (continuar == 0){
        int tipo;

        printf("\nTipo de habitacion: \n1-Simple \n2-Doble \n3-Suite \nIngrese el tipo: ");

        if (scanf("%d", &tipo) != 1){
            printf("Formato no valido\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');

            stPrecios auxPrecios;
            FILE *archiPrecios = fopen("precios", "rb");

            if (archiPrecios == NULL){
                auxPrecios.simple = 90000;
                auxPrecios.doble = 110000;
                auxPrecios.suite = 160000;

                archiPrecios = fopen("precios", "wb");
                if (archiPrecios != NULL){
                    fwrite(&auxPrecios, sizeof(stPrecios), 1, archiPrecios);
                    fclose(archiPrecios);
                }
            } else {
                fread(&auxPrecios, sizeof(stPrecios), 1, archiPrecios);
                fclose(archiPrecios);
            }

            if (tipo == 1){
                strcpy(habitacion.tipo, "simple");
                habitacion.precioxNoche = auxPrecios.simple;
                continuar = 1;
            }
            else if (tipo == 2){
                strcpy(habitacion.tipo, "doble");
                habitacion.precioxNoche = auxPrecios.doble;
                continuar = 1;
            }
            else if (tipo == 3){
                strcpy(habitacion.tipo, "suite");
                habitacion.precioxNoche = auxPrecios.suite;
                continuar = 1;
            }
            else{
                printf("Dato invalido\n");
            }
        }
    }

    strcpy(habitacion.estado, "Libre");

    if (fwrite(&habitacion, sizeof(stHabitacion), 1, archHab) != 1){
        printf("Error al guardar la habitacion\n");
        fclose(archHab);
        return 0;
    }

    fclose(archHab);
    return 1;
}

int listadoCompleto(){
    ordenarArchivoHabitaciones();

    FILE *archHab = fopen("habitaciones", "rb");

    if (archHab == NULL){
        printf("No hay habitaciones cargadas\n");
        return 0;
    }

    stHabitacion habitacion;

    while (fread(&habitacion, sizeof(stHabitacion), 1, archHab) == 1){
        printf("\n------------------------------------------------");
        printf("\nNumero de habitacion: %i", habitacion.numero);
        printf("\nTipo de habitacion: %s", habitacion.tipo);
        printf("\nPrecio por noche: $%.2f", habitacion.precioxNoche);
        printf("\nEstado: %s", habitacion.estado);
    }

    fclose(archHab);
    return 1;
}

int bajaHabitacion(int num){
    FILE *archHab = fopen("habitaciones", "rb");
    FILE *aux = fopen("auxiliar", "wb");

    if (archHab == NULL || aux == NULL){
        printf("Error al abrir archivos\n");
        return 0;
    }

    stHabitacion habitacion;

    int pos = buscarxNumero(num);

    if (pos == -1){
        printf("Habitacion no encontrada\n");
        fclose(archHab);
        fclose(aux);
        remove("auxiliar");
        return 0;
    }

    fseek(archHab, pos * sizeof(stHabitacion), SEEK_SET);

    if (fread(&habitacion, sizeof(stHabitacion), 1, archHab) != 1){
        fclose(archHab);
        fclose(aux);
        remove("auxiliar");
        return 0;
    }

    if (strcmp(habitacion.estado, "Ocupado") == 0){
        printf("No se puede eliminar una habitacion ocupada\n");
        fclose(archHab);
        fclose(aux);
        remove("auxiliar");
        return 0;
    }

    rewind(archHab);

    int i = 0;

    while (fread(&habitacion, sizeof(stHabitacion), 1, archHab) == 1){
        if (i != pos){
            fwrite(&habitacion, sizeof(stHabitacion), 1, aux);
        }
        i++;
    }

    fclose(archHab);
    fclose(aux);

    remove("habitaciones");
    rename("auxiliar", "habitaciones");

    return 1;
}

int buscarxNumero(int nroBuscado){
    FILE *archHab = fopen("habitaciones", "rb");

    stHabitacion habitacion;
    int pos = 0;
    int encontrada = -1;

    if (archHab != NULL){
        while (fread(&habitacion, sizeof(stHabitacion), 1, archHab) == 1){
            if (habitacion.numero == nroBuscado){
                encontrada = pos;
                break;
            }
            pos++;
        }
        fclose(archHab);
    }

    return encontrada;
}

int buscarHabitacionxnum(int num){
    FILE *archHab = fopen("habitaciones", "rb");

    if (archHab == NULL){
        return 0;
    }

    stHabitacion habitacion;

    int pos = buscarxNumero(num);

    if (pos == -1){
        printf("Habitacion no encontrada\n");
        fclose(archHab);
        return 0;
    }

    fseek(archHab, pos * sizeof(stHabitacion), SEEK_SET);

    if (fread(&habitacion, sizeof(stHabitacion), 1, archHab) != 1){
        fclose(archHab);
        return 0;
    }

    printf("\n------------------------------------------------");
    printf("\nNumero de habitacion: %i", habitacion.numero);
    printf("\nTipo de habitacion: %s", habitacion.tipo);
    printf("\nPrecio por noche: $%.2f", habitacion.precioxNoche);
    printf("\nEstado: %s\n", habitacion.estado);

    fclose(archHab);
    return 1;
}

int modificarPrecios(){
    FILE *archiPrecios = fopen("precios", "rb+");

    if (archiPrecios == NULL){
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    stPrecios precios;

    if (fread(&precios, sizeof(stPrecios), 1, archiPrecios) != 1){
        fclose(archiPrecios);
        return 0;
    }

    int opcion;

    printf("\nPrecio a cambiar:");
    printf("\n1-Simple");
    printf("\n2-Doble");
    printf("\n3-Suite");
    printf("\nOpcion: ");

    if (scanf("%d", &opcion) != 1){
        fclose(archiPrecios);
        return 0;
    }

    if (opcion == 1){
        do{
            printf("Nuevo costo simple: ");
            scanf("%d", &precios.simple);
        } while (precios.simple <= 0);
    }
    else if (opcion == 2){
        do{
            printf("Nuevo costo doble: ");
            scanf("%d", &precios.doble);
        } while (precios.doble <= 0);
    }
    else if (opcion == 3){
        do{
            printf("Nuevo costo suite: ");
            scanf("%d", &precios.suite);
        } while (precios.suite <= 0);
    }
    else{
        fclose(archiPrecios);
        return 0;
    }

    fseek(archiPrecios, 0, SEEK_SET);

    if (fwrite(&precios, sizeof(stPrecios), 1, archiPrecios) != 1){
        fclose(archiPrecios);
        return 0;
    }

    fclose(archiPrecios);
    return 1;
}

void ordenarArchivoHabitaciones(){
    FILE *archHab = fopen("habitaciones", "rb+");

    if (archHab == NULL){
        return;
    }

    fseek(archHab, 0, SEEK_END);
    int cant = ftell(archHab) / sizeof(stHabitacion);

    if (cant <= 0){
        fclose(archHab);
        return;
    }

    stHabitacion *habitaciones = malloc(cant * sizeof(stHabitacion));

    if (habitaciones == NULL){
        fclose(archHab);
        return;
    }

    rewind(archHab);

    if (fread(habitaciones, sizeof(stHabitacion), cant, archHab) != cant){
        free(habitaciones);
        fclose(archHab);
        return;
    }

    for (int i = 1; i < cant; i++){
        stHabitacion aux = habitaciones[i];
        int j = i - 1;

        while (j >= 0 && habitaciones[j].numero > aux.numero){
            habitaciones[j + 1] = habitaciones[j];
            j--;
        }

        habitaciones[j + 1] = aux;
    }

    rewind(archHab);

    if (fwrite(habitaciones, sizeof(stHabitacion), cant, archHab) != cant){
        free(habitaciones);
        fclose(archHab);
        return;
    }

    free(habitaciones);
    fclose(archHab);
}
