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
#include "string.h"
#include "habitacion.h"

int altaHabitacion(){
    FILE *archivo = fopen("habitaciones", "ab+");
    stHabitacion habitacion;

    /* Defino e inicializo 'continuar' para los diferentes while
    En primera instancia defino el numero de habitacion, corroborra que sea solo un numero
    y que si ya hay habitacion con ese numero que no se pueda cargar*/

    int continuar = 0;
    while (continuar == 0){
        int nro = 0;
        int existe = 0;
        printf("\nNumero de habitacion: ");
        if (scanf("%d", &nro) != 1 || getchar() != '\n'){
            printf("Formato no valido\n");
            while (getchar() != '\n');
            //uso getchar() para corroborrar que sea solo numeros y limpiar el buffer
        }
        else{
            if (nro < 0){
                printf("Numero no valido\n");
            }
            else{
                fseek(archivo, 0, SEEK_SET);
                while (fread(&habitacion, sizeof(stHabitacion), 1, archivo) > 0){
                    if (habitacion.numero == nro){
                        existe = 1;
                        break;
                    }
                }
                if (existe == 1){
                    printf("Esa habitacion ya fue cargada\n");
                }
                else{
                    habitacion.numero = nro;
                    continuar = 1;
                }
            }
        }
    }

    /*Vuelvo continuar a 0 para seguir con el tipo y no tener que inicializar mas variables con la misma funcion
    En este caso, el usuario tiene que ingresar una de la opciones (int) para establecer de que tipo es la habitacion*/

    continuar = 0;
    while (continuar == 0){
        int tipo;
        printf("\nTipo de habitacion: \n1-Simple \n2-Doble \n3-Suite \nIngrese el tipo: ");
        if (scanf("%d", &tipo) != 1 || getchar() != '\n'){
            printf("Formato no valido\n");
            while (getchar() != '\n');
        }
        else{
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
            }
            else{
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
                printf("\nDato ingresado no valido, intente nuevamente\n");
            }
        }
    }
    /*Para simplicar el proceso, el precio se define arriba al definir el tipo
    y al usuario se le da la opcion de actualizarlo en otra funcion de modificacion*/

    printf("\nEl precio de la habitacion se define por el tipo de habitacion.\n Si desea cambiar el precio del tipo de habitacion,\nvuelva al menu de gestion de habitaciones y elija la opcion modificar datos y luego modificar precios.");

    /*Al crear la habitacion auotomaticamente se establece como libre*/

    strcpy(habitacion.estado, "Libre");

    fwrite(&habitacion, sizeof(stHabitacion), 1, archivo);
    fclose(archivo);
    return 1;
}
int listadoCompleto (){
    FILE *archivo = fopen("habitaciones", "rb");
    stHabitacion habitacion;
    while (fread(&habitacion, sizeof(stHabitacion), 1, archivo) > 0){
        printf("\n------------------------------------------------");
        printf("\nNumero de habitacion: %i", habitacion.numero);
        printf("\nTipo de habitacion: %s", habitacion.tipo);
        printf("\nPrecio por noche: $%.2f", habitacion.precioxNoche);
        printf("\nEstado: %s", habitacion.estado);
    }
    fclose(archivo);
}
int bajaHabitacion(int num){
    FILE *archivo = fopen("habitaciones", "rb");
    FILE *aux = fopen("auxiliar", "wb"); //creo un auxiliar para copiar los datos

    stHabitacion habitacion;
    int i = 0;
    int pos=0;
    pos= buscarxNumero(num);
    if (pos==-1){
        printf("Habitacion no encontrada");
        fclose(archivo);
        fclose(aux);

        remove("auxiliar");

        return 0;
    }
    else {
        while (fread(&habitacion, sizeof(stHabitacion), 1, archivo) > 0){

        if (i != pos){
            fwrite(&habitacion, sizeof(stHabitacion), 1, aux);
        }

        i++;
    }
    }


    fclose(archivo);
    fclose(aux);

    remove("habitaciones");
    rename("auxiliar", "habitaciones"); //renombro para seguir usando la gestion

    return 1;
}
int buscarxNumero(int nroBuscado){
    FILE *archivo = fopen("habitaciones", "rb");
    stHabitacion habitacion;
    int pos = 0;
    int encontrada = -1;

    if (archivo != NULL){
        while (fread(&habitacion, sizeof(stHabitacion), 1, archivo) > 0){
            if (habitacion.numero == nroBuscado){
                encontrada = pos;
                break;
            }
            pos++;
        }
        fclose(archivo);
    }

    return encontrada;
}
int buscarHabitacionxnum(int num){
    FILE *archivo = fopen("habitaciones", "rb");

    if(archivo == NULL){
        return 0;
    }

    stHabitacion habitacion;
    int pos = buscarxNumero(num);

    if(pos == -1){
        printf("Habitacion no encontrada\n");
        fclose(archivo);
        return 0;
    }

    fseek(archivo, pos * sizeof(stHabitacion), SEEK_SET);
    fread(&habitacion, sizeof(stHabitacion), 1, archivo);

    printf("\n------------------------------------------------");
    printf("\nNumero de habitacion: %i", habitacion.numero);
    printf("\nTipo de habitacion: %s", habitacion.tipo);
    printf("\nPrecio por noche: $%.2f", habitacion.precioxNoche);
    printf("\nEstado: %s\n", habitacion.estado);

    fclose(archivo);

    return 1;
}
int modificarPrecios(){
    FILE *archiPrecios = fopen("precios", "rb+");
    if(archiPrecios == NULL){
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    stPrecios precios;
    fread(&precios, sizeof(stPrecios), 1, archiPrecios);
    int opcion;
    printf("\nPrecio a cambiar:\n1-Simple \n2-Doble \n3-suite");
    scanf("%d", &opcion);

    if(opcion == 1){
        printf("Nuevo costo de la habitacion: ");
        scanf("%d", &precios.simple);
    }
    else if(opcion == 2){
        printf("Nuevo costo de la habitacion: ");
        scanf("%d", &precios.doble);
    }
    else if(opcion == 3){
        printf("Nuevo costo de la habitacion: ");
        scanf("%d", &precios.suite);
    }
    else{
        printf("Opcion no valida\n");
        fclose(archiPrecios);
        return 0;
    }

    fseek(archiPrecios, 0, SEEK_SET);
    fwrite(&precios, sizeof(stPrecios), 1, archiPrecios);

    fclose(archiPrecios);

    return 1;
}
