#include <stdio.h>
#include <stdlib.h>
#include "reservas.h"
#include "habitacion.h"
int generarId(){
FILE *arch=fopen("reservas", "ab");
stReserva reservas;
int id = 1;

    if(arch != NULL){
        while(fread(&reservas, sizeof(stReserva), 1, arch) > 0){
            id++;
        }
        fclose(arch);
    }

    return id;
}

int altaReserva(){

    FILE *archRes = fopen("reservas", "ab");
    stReserva reserva;
    stHabitacion habitacion;

    int pos, existeDNI, opcion, confirmar;

    printf("DNI del huesped: ");
    scanf("%s", reserva.dniHuesped);

    existeDNI = DNIexiste(reserva.dniHuesped);

    if(!existeDNI){

        printf("\n--No existe un huesped con ese DNI--\n");

        do{
            printf("Desea registrarlo?\n");
            printf("1-SI\n");
            printf("0-NO\n=");
            scanf("%i", &opcion);

            if(opcion != 0 && opcion != 1){
                printf("\n--Opcion invalida--\n");
            }

        }while(opcion != 0 && opcion != 1);

        if(opcion == 1){

            altaHuesped();

            printf("\nIngrese nuevamente el DNI del huesped: ");
            scanf("%s", reserva.dniHuesped);

            if(!DNIexiste(reserva.dniHuesped)){
                printf("\n--DNI inexistente--\n");
                fclose(archRes);
                return 0;
            }

        }else{

            printf("\n--Reserva cancelada--\n");
            fclose(archRes);
            return 0;
        }
    }
    do{

    printf("Numero de habitacion: ");
    scanf("%d", &reserva.numHabitacion);

    pos = buscarxNumero(reserva.numHabitacion);

    if(pos == -1){

        printf("\n--Habitacion inexistente--\n");

        do{
            printf("Desea registrarla?\n");
            printf("1-SI\n");
            printf("0-NO\n=");
            scanf("%d", &opcion);

            if(opcion != 0 && opcion != 1){
                printf("\n--Opcion invalida--\n");
            }

        }while(opcion != 0 && opcion != 1);

        if(opcion == 1){

            altaHabitacion();

            printf("\nIngrese nuevamente el numero de habitacion: ");
            scanf("%d", &reserva.numHabitacion);

            pos = buscarxNumero(reserva.numHabitacion);

            if(pos == -1){

                printf("\n--La habitacion no fue registrada--\n");

                fclose(archRes);
                return 0;
            }
        }
        else{

            printf("\n--Reserva cancelada--\n");

            fclose(archRes);
            return 0;
        }
    }

}while(pos == -1);


    FILE *archHab = fopen("habitaciones", "rb+");

    fseek(archHab, pos * sizeof(stHabitacion), SEEK_SET);
    fread(&habitacion, sizeof(stHabitacion), 1, archHab);

    while(strcmp(habitacion.estado, "Libre") != 0){

        printf("\n--La habitacion esta ocupada--\n");

        do{

            printf("Ingrese otra habitacion: ");
            scanf("%i", &reserva.numHabitacion);

            pos = buscarxNumero(reserva.numHabitacion);

            if(pos == -1){
                printf("\n--Habitacion inexistente--\n");
            }

        }while(pos == -1);

        fseek(archHab, pos * sizeof(stHabitacion), SEEK_SET);
        fread(&habitacion, sizeof(stHabitacion), 1, archHab);
    }
    do{

        printf("Cantidad de noches: ");
        scanf("%d", &reserva.cantNoches);

        if(reserva.cantNoches <= 0){
            printf("\n--Cantidad invalida--\n");
        }

    }while(reserva.cantNoches <= 0);
    reserva.idReserva = generarId();
    reserva.total = habitacion.precioxNoche * reserva.cantNoches;

    printf("\n----- DATOS DE LA RESERVA -----\n");

    printf("ID Reserva: %i\n", reserva.idReserva);
    printf("DNI Huesped: %s\n", reserva.dniHuesped);
    printf("Habitacion: %i\n", habitacion.numero);
    printf("Tipo: %s\n", habitacion.tipo);
    printf("Precio por noche: $%.2f\n", habitacion.precioxNoche);
    printf("Cantidad de noches: %i\n", reserva.cantNoches);
    printf("TOTAL: $%.2f\n", reserva.total);

    do{

        printf("\nConfirmar reserva?\n");
        printf("1-SI\n");
        printf("0-NO\n=");
        scanf("%i", &confirmar);

        if(confirmar != 0 && confirmar != 1){
            printf("\n--Opcion invalida--\n");
        }

    }while(confirmar != 0 && confirmar != 1);

    if(confirmar == 0){

        printf("\n--Reserva cancelada--\n");

        fclose(archRes);
        fclose(archHab);

        return 0;
    }
    fwrite(&reserva, sizeof(stReserva), 1, archRes);
    fclose(archRes);

    strcpy(habitacion.estado, "Ocupada");
    fseek(archHab, pos * sizeof(stHabitacion), SEEK_SET);
    fwrite(&habitacion, sizeof(stHabitacion), 1, archHab);

    fclose(archHab);

    printf("\n--Reserva realizada correctamente--\n");
    printf("ID Reserva: %i\n", reserva.idReserva);
    printf("Total: $%.2f\n", reserva.total);

    return 1;
}












