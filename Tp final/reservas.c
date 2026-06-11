#include <stdio.h>
#include <stdlib.h>
#include "reservas.h"
#include "habitacion.h"
#include "huesped.h"
#include "string.h"

int generarId(){
    FILE *arch = fopen("reservas", "rb+");
    stReserva reservas;
    int id = 1;

    if(arch == NULL){
        return 1;
    }

    fseek(arch, 0, SEEK_SET);

    while(fread(&reservas, sizeof(stReserva), 1, arch) == 1){
        id = reservas.idReserva + 1;
    }

    fclose(arch);
    return id;
}

int altaReserva(){

    FILE *archRes = fopen("reservas", "rb+");
    stReserva reserva;
    stHabitacion habitacion;

    if(archRes == NULL){
        return 0;
    }

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
                    fclose(archRes);
                    return 0;
                }
            }
            else{
                fclose(archRes);
                return 0;
            }
        }

    }while(pos == -1);

    FILE *archHab = fopen("habitaciones", "rb+");

    if(archHab == NULL){
        fclose(archRes);
        return 0;
    }

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

int bajaReserva(int id_reserva){
    FILE *archRes = fopen("reservas", "rb");
    FILE *archB = fopen("archAux", "wb");

    if(archRes == NULL || archB == NULL){
        if(archRes) fclose(archRes);
        if(archB) fclose(archB);
        return 0;
    }

    stReserva reserva;

    while(fread(&reserva, sizeof(stReserva), 1, archRes) == 1){

        if(reserva.idReserva != id_reserva){
            fwrite(&reserva, sizeof(stReserva), 1, archB);
        }
        else{

            FILE *archHab = fopen("habitaciones", "rb+");

            if(archHab != NULL){

                stHabitacion habitacion;
                int posHab = buscarxNumero(reserva.numHabitacion);

                if(posHab != -1){

                    fseek(archHab, posHab * sizeof(stHabitacion), SEEK_SET);
                    fread(&habitacion, sizeof(stHabitacion), 1, archHab);

                    strcpy(habitacion.estado, "Libre");

                    fseek(archHab, posHab * sizeof(stHabitacion), SEEK_SET);
                    fwrite(&habitacion, sizeof(stHabitacion), 1, archHab);
                }

                fclose(archHab);
            }
        }
    }

    fclose(archRes);
    fclose(archB);

    remove("reservas");
    rename("archAux", "reservas");

    return 1;
}

int buscarPosxID(int id_reserva){
    FILE *archRes = fopen("reservas", "rb");
    stReserva reserva;
    int pos = 0;

    if(archRes == NULL){
        return -1;
    }

    while(fread(&reserva, sizeof(stReserva), 1, archRes) > 0){
        if(reserva.idReserva == id_reserva){
            fclose(archRes);
            return pos;
        }
        pos++;
    }

    fclose(archRes);
    return -1;
}

int mostrarUnaReserva(int id){

    FILE *archRes = fopen("reservas", "rb");
    FILE *archHab = fopen("habitaciones", "rb");

    if(archRes == NULL || archHab == NULL){
        if(archRes) fclose(archRes);
        if(archHab) fclose(archHab);
        return -1;
    }

    stHabitacion habitacion;
    stReserva reserva;

    int pos = buscarPosxID(id);

    if(pos == -1){
        fclose(archRes);
        fclose(archHab);
        return 0;
    }

    fseek(archRes, pos * sizeof(stReserva), SEEK_SET);
    fread(&reserva, sizeof(stReserva), 1, archRes);

    int posHab = buscarxNumero(reserva.numHabitacion);

    if(posHab != -1){
        fseek(archHab, posHab * sizeof(stHabitacion), SEEK_SET);
        fread(&habitacion, sizeof(stHabitacion), 1, archHab);
    }

    printf("\n-----------------------------------\n");
    printf("ID Reserva: %i\n", reserva.idReserva);
    printf("DNI Huesped: %s\n", reserva.dniHuesped);
    printf("Habitacion: %i\n", habitacion.numero);
    printf("Tipo: %s\n", habitacion.tipo);
    printf("Precio por noche: $%.2f\n", habitacion.precioxNoche);
    printf("Cantidad de noches: %i\n", reserva.cantNoches);
    printf("TOTAL: $%.2f\n", reserva.total);

    fclose(archRes);
    fclose(archHab);

    return 1;
}

int listadoReservas(){
    FILE *archRes = fopen("reservas", "rb");
    FILE *archHab = fopen("habitaciones", "rb");

    if(archRes == NULL || archHab == NULL){
        if(archRes) fclose(archRes);
        if(archHab) fclose(archHab);
        return -1;
    }

    stHabitacion habitacion;
    stReserva reserva;

    while(fread(&reserva, sizeof(stReserva), 1, archRes) > 0){

        int posHab = buscarxNumero(reserva.numHabitacion);

        if(posHab == -1){
            continue;
        }

        fseek(archHab, posHab * sizeof(stHabitacion), SEEK_SET);
        fread(&habitacion, sizeof(stHabitacion), 1, archHab);

        printf("\n-----------------------------------\n");
        printf("ID Reserva: %i\n", reserva.idReserva);
        printf("DNI Huesped: %s\n", reserva.dniHuesped);
        printf("Habitacion: %i\n", habitacion.numero);
        printf("Tipo: %s\n", habitacion.tipo);
        printf("Precio por noche: $%.2f\n", habitacion.precioxNoche);
        printf("Cantidad de noches: %i\n", reserva.cantNoches);
        printf("TOTAL: $%.2f\n", reserva.total);
    }

    fclose(archHab);
    fclose(archRes);

    return 1;
}







