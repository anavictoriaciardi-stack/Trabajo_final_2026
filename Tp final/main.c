#include <stdio.h>
#include <stdlib.h>
#include "huesped.h"
#include "habitacion.h"
#include "reservas.h"

int main()
{
     printf("Entre al main\n");
    int opcion1=1, opHuesped, val;
    char dniBuscar[8];
    printf("----------HOTEL 'LAS SOBREVIVIENTES'----------");
    printf("\n **|Bienvenido al sistema de gestion del hotel 'las sobrevivientes'. A continuacion podra elegir que acciones realizar.|**");
    while (opcion1!=0)
    {
        printf("\n1- Gestionar Huespedes \n2- Gestionar Habitaciones \n3- Gestionar Reservas \n0- salir del sistema de gestion \nOpcion:");
        scanf("%i", &opcion1);
        switch (opcion1)
        {
        case 1:
            opHuesped=1;
            while(opHuesped!=0)
            {
                printf("\n---------------------------------------------------------------------------------------------------\n");
                printf("\n GESTION DE HUSPEDES\n");
                printf("    1-Registrar huesped\n");
                printf("    2-Eliminar husped\n");
                printf("    3-Editar datos del huesped\n");
                printf("    4-Buscar huesped\n");
                printf("    5-Listados de hueped\n");
                printf("    0-Volver al menu principal\n");
                printf("Opcion: ");
                scanf("%i", &opHuesped);

                switch(opHuesped)
                {
                case 1:
                    altaHuesped();
                    break;
                case 2:
                    do{
                        val=1;
                        printf("Ingrese el DNI del huesped (8 caracteres): \n");
                        fflush(stdin);
                        gets(dniBuscar);
                        for(int i=0; i<8; i++){
                            if(dniBuscar[i]<'0' || dniBuscar[i]>'9'){
                                val=0;
                            }
                        }
                        if (val==0){
                            printf("\n--DNI invalido--\n");
                            printf("\nVuela a ingresarlo correctamente\n");
                        }

                     }while(val==0);
                     if (bajaHuesped(dniBuscar)){
                        printf("\n--HUESPED ELMINADO--\n");
                     }
                    break;
                case 3:
                    printf("\n---MODIFICAR POR DNI--\n");
                     do{
                        val=1;
                        printf("Ingrese el DNI del huesped (8 caracteres) a modificar: \n");
                        fflush(stdin);
                        gets(dniBuscar);
                        for(int i=0; i<8; i++){
                            if(dniBuscar[i]<'0' || dniBuscar[i]>'9'){
                                val=0;
                            }
                        }
                        if (val==0){
                            printf("\n--DNI invalido--\n");
                            printf("\nVuela a ingresarlo correctamente\n");
                        }

                     }while(val==0);
                    modificarDatos(dniBuscar);

                    break;
                case 0:
                    break;
                default:
                    printf("\n Opcion Invalida\n");
                    break;
                }
            }

            break;
        case 2:
            printf("\n---------------------------------------------------------------------------------------------------\n");
            int opcion1hb=1;
            printf("\n GESTION DE HABITACIONES\n");
            printf("\n aca las opciones para que gestione las habitaciones del hotel: \n");
            while (opcion1hb!=0)
            {
                printf("\n  1-Dar de alta una habitacion \n 2-Dar de baja una habitacion \n 3-Modificar datos de una habitacion \n  4-Busqueda Especifica \n    5-Ver listado \n    0- Volver al menu principal \n Opcion: ");
                scanf("%i",&opcion1hb);
                switch(opcion1hb)
                {
                case 1:
                    printf("\n-----Dar de alta una habitacion-----\n");
                    printf("\nCargue los datos de la nueva habitacion: \n");
                    altaHabitacion();
                    printf("\n");
                    break;
                case 2:
                    printf("\n-----Dar de baja una habitacion-----\n");
                    int num;
                    printf("\nNumero de habitacion que quiere eliminar: \n");
                    scanf("%i", &num);
                    bajaHabitacion(num);
                    printf("\n");
                    break;
                case 3:
                    break;
                case 4:
                    printf("-----Busqueda especifica de Habitacion-----\n");
                    int numero;
                    printf("\n Que habitacion busca? ");
                    scanf("%i", &numero);
                    buscarHabitacionxnum(numero);
                    printf("\n");
                    break;
                case 5:
                    printf("-----Ver listado Completo-----\n");
                    listadoCompleto();
                    printf("\n");
                    break;
                case 0:
                    break;
                default:

                    break;
                }
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
    }

    return 0;
}
