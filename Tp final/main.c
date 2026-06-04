#include <stdio.h>
#include <stdlib.h>
#include "huesped.h"
#include "habitacion.h"
#include "reservas.h"

int main()
{
    int opcion1;
    printf("----------HOTEL 'LAS SOBREVIVIENTES'----------");
    printf("\n **|Bienvenido al sistema de gestion del hotel 'las sobrevivientes'. A continuacion podra elegir que acciones realizar.|**");
    printf("\n1- Gestionar Huespedes \n2- Gestionar Habitaciones \n3- Gestionar Reservas \n0- salir del sistema de gestion");
    scanf("%i", &opcion1);
    switch (opcion1){
    case 1:
        printf("\n---------------------------------------------------------------------------------------------------\n");
        printf("\n GESTION DE HUSPEDES\n");
        break;
    case 2:
        printf("\n---------------------------------------------------------------------------------------------------\n");
        int opcion1hb;
        printf("\n GESTION DE HABITACIONES\n");
        printf("\n aca las opciones para que gestione las habitaciones del hotel: \n");
        printf("\n1-Dar de alta una habitacion \n2-Dar de baja una habitacion \n3-Modificar datos de una habitacion \n4-Busqueda Especifica \n5-Ver listado \n0- Volver al menu principal");
        scanf("%i",&opcion1hb);
        switch(opcion1hb){
        case 1:
            printf("\n-----Dar de alta una habitacion-----\n");
            printf("\ncargue los datos de la nueva habitacion: \n");
            altaHabitacion();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            break;
        default:

            break;
        }


        break;
    case 3:
        printf("\n---------------------------------------------------------------------------------------------------\n");
        printf("\n GESTION DE RESERVAS\n");
        break;
    case 0:
        printf("Salio del sistema de gestion del hotel. Muchas gracias por utilizarlo.");
        break;
    default:
        printf("Error. Ingreso mal un dato. Vuelvalo a intentar");
        break;
    }
    return 0;
}
