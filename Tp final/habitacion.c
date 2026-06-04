/*
    Habitacion
    int número
    char tipo [ ](simple/doble/suite)
    int precio por noche
    char estado (libre/ocupada)

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

int altaHabitacion (){
    FILE *archivo = fopen("habitaciones", "ab+");
    stHabitacion habitacion;
    int continuar = 0;
    while (continuar == 0){
        int nro = 0;
        char extra;
        int existe = 0;
        printf("\nNumero de habitacion: ");
        if (scanf("%d", &nro) != 1){
            printf("Formato no valido\n");
            while (getchar() != '\n');
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

continuar=0;
while (continuar==0)
{
    int tipo;
    char extra;
    printf("\nTipo de habitacion: \n1-Simple \n2-Doble \n3-Suite \nIngrese el tipo: ");
    if (scanf("%d%c", &tipo, &extra) != 2 || extra != '\n')
    {
        printf("Formato no valido\n");
        scanf("%*[^\n]");
        scanf("%*c");
    }
    else
    {
        if (tipo==1)
        {
            strcpy(habitacion.tipo, "simple");
            continuar=1;
        }
        else if (tipo==2)
        {
            strcpy(habitacion.tipo, "doble");
            continuar=1;
        }
        else if (tipo==3)
        {
            strcpy(habitacion.tipo, "suite");
            continuar=1;
        }
        else
        {
            printf("\nDato ingresado no valido, intente nuevamente\n");
        }
    }
}
fwrite(&habitacion, sizeof(stHabitacion), 1, archivo);
fclose(archivo);

return 1;
}
