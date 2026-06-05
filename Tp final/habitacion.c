/*
    Habitacion (en habitacion.h)
    int número
    char tipo [ ](simple/doble/suite)
    int precio por noche
    char estado (libre/ocupada)

    cosas que tengo que hacer:
    alta: agregar habitacion
    baja: eliminar habitacion
    modificacion: cambiar precio/ tipo
    consulta: buscar por numero
    listado: todos o por tipo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "habitacion.h"

int altaHabitacion(){
    FILE *archivo = fopen("habitaciones", "ab+");

    if (archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    stHabitacion habitacion;
    int continuar = 0;

    while (continuar == 0){
        int nro;
        int existe = 0;

        printf("\nNumero de habitacion: ");

        if (scanf("%d", &nro) != 1){
            printf("Formato no valido\n");
            while(getchar() != '\n');
        }
        else{
            char c = getchar();

            if(c != '\n' && c != EOF){
                printf("Formato no valido\n");
                while(getchar() != '\n');
            }
            else if(nro <= 0){
                printf("Numero no valido\n");
            }
            else{
                rewind(archivo);

                while(fread(&habitacion,sizeof(stHabitacion),1,archivo) > 0){
                    if(habitacion.numero == nro){
                        existe = 1;
                        break;
                    }
                }

                if(existe){
                    printf("Esa habitacion ya fue cargada\n");
                }
                else{
                    habitacion.numero = nro;
                    continuar = 1;
                }
            }
        }
    }

    continuar = 0;

    while (continuar == 0){
        int tipo;

        printf("\nTipo de habitacion:");
        printf("\n1-Simple");
        printf("\n2-Doble");
        printf("\n3-Suite");
        printf("\nIngrese el tipo: ");

        if(scanf("%d",&tipo) != 1){
            printf("Formato no valido\n");
            while(getchar() != '\n');
        }
        else{
            char c = getchar();
            if(c != '\n' && c != EOF){
                printf("Formato no valido\n");
                while(getchar() != '\n');
            }
            else{
                stPrecios auxPrecios;
                FILE *archiPrecios = fopen("precios","rb");
                if(archiPrecios == NULL){
                    auxPrecios.simple = 90000;
                    auxPrecios.doble = 110000;
                    auxPrecios.suite = 160000;

                    archiPrecios = fopen("precios","wb");

                    if(archiPrecios != NULL){
                        fwrite(&auxPrecios,sizeof(stPrecios),1,archiPrecios);
                        fclose(archiPrecios);
                    }
                }
                else{

                    fread(&auxPrecios,sizeof(stPrecios),1,archiPrecios);
                    fclose(archiPrecios);

                    if(auxPrecios.simple <= 0 ||
                       auxPrecios.doble <= 0 ||
                       auxPrecios.suite <= 0){

                        auxPrecios.simple = 90000;
                        auxPrecios.doble = 110000;
                        auxPrecios.suite = 160000;
                    }
                }

                if(tipo == 1){
                    strcpy(habitacion.tipo,"simple");
                    habitacion.precioxNoche = auxPrecios.simple;
                    continuar = 1;
                }
                else if(tipo == 2){
                    strcpy(habitacion.tipo,"doble");
                    habitacion.precioxNoche = auxPrecios.doble;
                    continuar = 1;
                }
                else if(tipo == 3){
                    strcpy(habitacion.tipo,"suite");
                    habitacion.precioxNoche = auxPrecios.suite;
                    continuar = 1;
                }
                else{
                    printf("Tipo no valido\n");
                }
            }
        }
    }

    strcpy(habitacion.estado,"Libre");

    printf("\nPrecio asignado: %.2f\n", habitacion.precioxNoche);

    fseek(archivo,0,SEEK_END);
    fwrite(&habitacion,sizeof(stHabitacion),1,archivo);

    fclose(archivo);

    return 1;
}

int listadoCompleto(){
    FILE *archivo = fopen("habitaciones","rb");
    if(archivo == NULL){
        printf("\nNo hay habitaciones cargadas.\n");
        return 0;
    }
    stHabitacion habitacion;
    while(fread(&habitacion,sizeof(stHabitacion),1,archivo) > 0){
        printf("\n------------------------------------------------");
        printf("\nNumero de habitacion: %d", habitacion.numero);
        printf("\nTipo de habitacion: %s", habitacion.tipo);
        printf("\nPrecio por noche: $%.2f", habitacion.precioxNoche);
        printf("\nEstado: %s", habitacion.estado);
    }



    fclose(archivo);

    return 1;
}



