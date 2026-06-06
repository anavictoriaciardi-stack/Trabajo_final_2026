/*
    Huésped
    Int DNI
    char nombreyApellido [ ]
    int teléfono
    char email []

    alta: registrar huesped
    baja: eliminar huesped
    modificacion: editar datos
    consulta: buscar por DNI
    listado: todos o por apellido
*/
#include <stdio.h>
#include <stdlib.h>
#include "huesped.h"
#include <string.h>

int altaHuesped();
int altaHuesped()
{
    FILE *arch=fopen("archHuesped", "ab");
    stHuesped huesped;

    int seguir=1, control, val;
    long long int min=1000000000, max=9999999999;
    while (seguir==1)
    {
        printf("Complete los siguientes datos:\n");
        printf("        Nombre y Apellido: ");
        fflush(stdin);
        gets(huesped.NombreYApelido);

        do{
            val=1;
            printf("        DNI: ");
            fflush(stdin);
            gets(huesped.DNI);
            for(int i=0; i<8; i++){
                if(huesped.DNI[i]<'0' || huesped.DNI[i]>'9'){
                    val=0;
                }
            }
            if (val==0){
                printf("\n--DNI invalido--\n");
                printf("\nVuela a ingresarlo correctamente\n");
            }

        }while(val==0);

        do {
                printf("        Telefono: ");
                control= scanf("%lld", &huesped.telefono);
                if (control!=1 || huesped.telefono<min || huesped.telefono>max){
                    printf("\n--Telefono no valido--\n");
                    printf("\nVuela a ingresarlo correctamente\n");
                        if (control!=1){
                            while(getchar()!='\n');
                        }
                }
        }while(control!=1 || huesped.telefono<min || huesped.telefono>max);

        do{
            printf("        Email: ");
            fflush(stdin);
            gets(huesped.email);

            if (strchr(huesped.email,'@')==NULL || strchr(huesped.email,'.')==NULL ){
                printf("\n      --Email no valido--\n");
                printf("\nVuela a ingresarlo correctamente\n (tiene que contener @ y .)\n");
            }
        } while(strchr(huesped.email,'@')==NULL || strchr(huesped.email,'.')==NULL );



        fwrite(&huesped, sizeof(stHuesped), 1, arch);
        do{
            printf("\nQuier cargar otro husped?\n 1-SI\n0-NO\n=");
            scanf("%i", &seguir);
            if(seguir==1){
                printf("->Ingrese los datos del NUEVO huesped: \n");
            } else if(seguir==0){
                printf("\n--Huesped cargado correctamente--\n");
                }
            else {
                printf("\n--Opcion no valida--\n");
            }
        }while(seguir!=1 && seguir!=0);
    }
    fclose(arch);
    return 0;
}





















