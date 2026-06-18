#include <stdio.h>
#include <stdlib.h>
#include "huesped.h"
#include "habitacion.h"
#include "reservas.h"
#include "pila.h"

void menuReservas();
void menuHuesped();
void menuHabitacion();
int main()
{
    int opcion1=1, control;
    printf("----------HOTEL 'LAS SOBREVIVIENTES'----------");
    printf("\n **|Bienvenido al sistema de toma de reservas del hotel 'las sobrevivientes'. A continuacion podra elegir que acciones realizar.|**");
    while (opcion1!=0)
    {
        printf("\n1- Gestionar Huespedes \n2- Gestionar Habitaciones \n3- Gestionar Reservas \n0- salir del sistema de gestion \nOpcion:");
        control=scanf("%i", &opcion1);
        if(control != 1)
    {
        printf("\nError. Debe ingresar un numero.\n");

        while(getchar() != '\n');

        continue;
    }
        switch (opcion1)
        {
        case 1:
            menuHuesped();
            break;
        case 2:
            menuHabitacion();
            break;
        case 3:
            menuReservas();
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

void menuReservas(){

    int opcion, control;
    Pila pilaeliminados;
    inicpila(&pilaeliminados);

    do{
        printf("\n--- GESTION DE RESERVAS ---\n");
        printf("1- Alta de reserva\n");
        printf("2- Baja de reserva\n");
        printf("3- Buscar reserva\n");
        printf("4- Mostrar reservas\n");
        printf("5- Eliminados del dia\n");
        printf("0- Volver\n");
        printf("Opcion: ");
        control=scanf("%d", &opcion);
         if(control != 1)
    {
        printf("\nError. Debe ingresar un numero.\n");

        while(getchar() != '\n');

        continue;
    }

        switch(opcion){

            case 1:
                printf("\n-----Crear una Reserva-----\n");
                altaReserva();
                printf("\n");
                break;

            case 2:
                printf("\n-----Dar de baja una Reserva-----\n");
                    int numm, verificar=1;
                    while (verificar!=0){
                            printf("\nID de reserva que quiere eliminar: \n");
                            if (scanf("%d", &numm) != 1 || getchar() != '\n'){
                                printf("Formato no valido\n");
                                while (getchar() != '\n'); //limpio el buffer
                            }
                            else {
                                bajaReserva(numm,&pilaeliminados);
                                verificar=0;
                            }
                    }

                    printf("\n");
                break;

            case 3:
                printf("\n-----Buscar una reserva-----\n");
                    int id, verificar1=1, res;
                    while (verificar1!=0){
                            printf("\nID de reserva que quiere buscar: \n");
                            if (scanf("%d", &id) != 1 || getchar() != '\n'){
                                printf("Formato no valido\n");
                                while (getchar() != '\n'); //limpio el buffer
                            }
                            else {
                                res= mostrarUnaReserva(id);
                                if (res==-1){
                                    printf("error del archivo");
                                }
                                else{
                                    verificar1=0;
                                }
                            }
                    }

                    printf("\n");
                break;

            case 4:
                printf("\n-----Mostrar Listado de Reservas por Orden de Carga-----\n");
                    listadoReservas();
                    printf("\n");

                break;
            case 5:
                printf("\n-----Mostrar eliminados del dia-----\n");
                //Se guarda solo en tiempo de ejecucion porque es informacion que despues no se necesita
                    mostrar(&pilaeliminados);
                    printf("\n");
                break;
            case 0:
                break;

            default:
                printf("Opcion invalida\n");
        }

    }while(opcion != 0);
}


void menuHuesped(){
int opcion=1, val, control;
char dniBuscar[9];
            while(opcion!=0)
            {
                printf("\n---------------------------------------------------------------------------------------------------\n");
                printf("\n GESTION DE HUSPEDES\n");
                printf("    1-Registrar huesped\n");
                printf("    2-Eliminar husped\n");
                printf("    3-Editar datos del huesped\n");
                printf("    4-Listados de hueped\n");
                printf("    5-Lista ordenada\n");
                printf("    0-Volver al menu principal\n");
                printf("Opcion: ");
                control= scanf("%i", &opcion);
                 if(control != 1)
    {
        printf("\nError. Debe ingresar un numero.\n");

        while(getchar() != '\n');

        continue;
    }
                switch(opcion)
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
                case 4:
                    printf("\n---LISTA DE HUESPED--\n");
                    mostrarRegistro();
                    break;
                case 5:
                    printf("\n--LISTA ORDENADA--\n");
                    listarHuespedesOrdenados();
                    break;
                case 0:
                    break;
                default:
                    printf("\n Opcion Invalida\n");
                    break;
                }
            }


}

void menuHabitacion(){

printf("\n---------------------------------------------------------------------------------------------------\n");
            int opcion1hb=1, control;
            printf("\n GESTION DE HABITACIONES\n");
            printf("\n aca las opciones para que gestione las habitaciones del hotel: \n");
            while (opcion1hb!=0)
            {
                printf("\n1-Dar de alta una habitacion \n2-Dar de baja una habitacion \n3-Modificar precio de las habitaciones \n4-Busqueda Especifica \n5-Ver listado \n 0- Volver al menu principal \n Opcion: ");
                control=scanf("%i",&opcion1hb);
                 if(control != 1)
    {
        printf("\nError. Debe ingresar un numero.\n");

        while(getchar() != '\n');

        continue;
    }
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
                    int num, corroborar=1;
                    while (corroborar!=0){
                            printf("\nNumero de habitacion que quiere eliminar: \n");
                            if (scanf("%d", &num) != 1 || getchar() != '\n'){
                                printf("Formato no valido\n");
                                while (getchar() != '\n'); //limpio el buffer
                            }
                            else {
                            bajaHabitacion(num);
                            corroborar=0;
                            }
                    }

                    printf("\n");
                    break;
                case 3:
                    printf("\n-----Modificar Precios de la Habitacion-----\n");
                    modificarPrecios();
                    printf("\n");
                    break;
                case 4:
                    printf("-----Busqueda especifica de Habitacion-----\n");
                    int numero;
                    printf("\n Que habitacion busca? ");
                    if (scanf("%d", &numero) != 1 || getchar() != '\n'){
                                printf("Formato no valido\n");
                                while (getchar() != '\n'); //limpio el buffer
                            }
                    else {
                        buscarHabitacionxnum(numero);
                    }

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
                    printf("\n Opcion Invalida\n");
                    break;
                }
            }

}
