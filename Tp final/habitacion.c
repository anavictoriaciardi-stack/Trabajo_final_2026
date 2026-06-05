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

float precioSimple=90000;
float precioDoble=110000;
float precioSuite=160000;

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
        if (scanf("%d", &nro) != 1 || getchar() != '\n') {
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
        if (scanf("%d", &tipo) != 1 || getchar() != '\n') {
            printf("Formato no valido\n");
            while (getchar() != '\n');
        }
        else{
            if (tipo == 1){
                strcpy(habitacion.tipo, "simple");
                habitacion.precioxNoche==precioSimple;
                continuar = 1;
            }
            else if (tipo == 2){
                strcpy(habitacion.tipo, "doble");
                habitacion.precioxNoche==precioDoble;
                continuar = 1;
            }
            else if (tipo == 3){
                strcpy(habitacion.tipo, "suite");
                habitacion.precioxNoche==precioSuite;
                continuar = 1;
            }
            else{
                printf("\nDato ingresado no valido, intente nuevamente\n");
            }
        }
    }
    /*Para simplicar el proceso, el precio se define arriba al definir el tipo
    y al usuario se le da la opcion de actualizarlo en otra funcion de modificacion*/

        printf("\nEl precio de la habitacion se define por el tipo de habitacion. Si desea cambiar el precio del tipo de habitacion,\nvuelva al menu de gestion de habitaciones y elija la opcion modificar datos y luego modificar precios.");

    /*Al crear la habitacion auotomaticamente se establece como libre*/
        strcpy(habitacion.estado, "Libre");

    fwrite(&habitacion, sizeof(stHabitacion), 1, archivo);
    fclose(archivo);
    return 1;
}

