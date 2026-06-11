#include <stdio.h>
#include <stdlib.h>
#include "huesped.h"
#include <string.h>

int altaHuesped()
{
    FILE *arch = fopen("archHuesped", "a+b");
    stHuesped huesped;

    int seguir = 1, control, val, enconDNI, enconEMAIL;
    long long int min = 1000000000, max = 9999999999;

    while (seguir == 1)
    {
        printf("Complete los siguientes datos:\n");
        printf("        Nombre y Apellido: ");

        while (getchar() != '\n');
        fgets(huesped.NombreYApelido, sizeof(huesped.NombreYApelido), stdin);

        do {
            val = 1;
            printf("        DNI: ");
            while (getchar() != '\n');
            fgets(huesped.DNI, sizeof(huesped.DNI), stdin);
            huesped.DNI[strcspn(huesped.DNI, "\n")] = 0;

            int len = strlen(huesped.DNI);
            if (len < 1) val = 0;

            for (int i = 0; i < len; i++) {
                if (huesped.DNI[i] < '0' || huesped.DNI[i] > '9') {
                    val = 0;
                }
            }

            if (val == 0) {
                printf("\n--DNI invalido--\n");
                printf("\nVuelva a ingresarlo correctamente\n");
            } else {
                enconDNI = DNIexiste(huesped.DNI);
                if (enconDNI) {
                    printf("\n--DNI ya existente--\n");
                    val = 0;
                }
            }
        } while (val == 0);

        do {
            printf("        Telefono: ");
            control = scanf("%lld", &huesped.telefono);

            if (control != 1 || huesped.telefono < min || huesped.telefono > max) {
                printf("\n--Telefono no valido--\n");
                printf("\nVuelva a ingresarlo correctamente\n");

                if (control != 1) {
                    while (getchar() != '\n');
                }
            }
        } while (control != 1 || huesped.telefono < min || huesped.telefono > max);

        do {
            val = 1;
            printf("        Email: ");
            while (getchar() != '\n');
            fgets(huesped.email, sizeof(huesped.email), stdin);

            if (strchr(huesped.email, '@') == NULL || strchr(huesped.email, '.') == NULL) {
                printf("\n      --Email no valido--\n");
                printf("\nVuelva a ingresarlo correctamente\n");
                val = 0;
            } else {
                enconEMAIL = EMAILexiste(huesped.email);
                if (enconEMAIL) {
                    printf("Email ya existente\n");
                    val = 0;
                }
            }
        } while (val == 0);

        fwrite(&huesped, sizeof(stHuesped), 1, arch);

        do {
            printf("\nQuiere cargar otro huesped?\n 1-SI\n0-NO\n=");
            scanf("%i", &seguir);

            if (seguir == 1) {
                printf("->NUEVO huesped: \n");
            } else if (seguir == 0) {
                printf("\n--Huesped cargado correctamente--\n");
            } else {
                printf("\n--Opcion no valida--\n");
            }

        } while (seguir != 1 && seguir != 0);
    }

    fclose(arch);
    return 0;
}

int DNIexiste(char DNI[])
{
    FILE *arch = fopen("archHuesped", "rb");
    stHuesped huesped;
    int encontrado = 0;

    if (arch == NULL) {
        return 0;
    }

    while (fread(&huesped, sizeof(stHuesped), 1, arch) > 0 && encontrado == 0) {
        if (strcmp(huesped.DNI, DNI) == 0) {
            encontrado = 1;
        }
    }

    fclose(arch);
    return encontrado;
}

int EMAILexiste(char EMAIL[])
{
    FILE *arch = fopen("archHuesped", "rb");
    stHuesped huesped;
    int encontrado = 0;

    if (arch == NULL) {
        return 0;
    }

    while (fread(&huesped, sizeof(stHuesped), 1, arch) > 0 && encontrado == 0) {
        if (strcmp(huesped.email, EMAIL) == 0) {
            encontrado = 1;
        }
    }

    fclose(arch);
    return encontrado;
}

int buscarPosxDNI(char DNIbus[])
{
    FILE *arch = fopen("archHuesped", "rb");
    stHuesped husped;
    int pos = 0;

    if (arch == NULL) {
        return -1;
    }

    while (fread(&husped, sizeof(stHuesped), 1, arch) > 0) {
        if (strcmp(husped.DNI, DNIbus) == 0) {
            fclose(arch);
            return pos;
        }
        pos++;
    }

    fclose(arch);
    return -1;
}

int bajaHuesped(char DNIbus[])
{
    FILE *arch = fopen("archHuesped", "rb");
    FILE *archA = fopen("archAux", "wb");

    stHuesped huesped;

    if (arch == NULL || archA == NULL) {
        if (arch) fclose(arch);
        if (archA) fclose(archA);
        return 0;
    }

    while (fread(&huesped, sizeof(stHuesped), 1, arch) > 0) {
        if (strcmp(huesped.DNI, DNIbus) != 0) {
            fwrite(&huesped, sizeof(stHuesped), 1, archA);
        }
    }

    fclose(arch);
    fclose(archA);

    remove("archHuesped");
    rename("archAux", "archHuesped");

    return 1;
}

int modificarDatos(char dniBus[])
{
    FILE *arch = fopen("archHuesped", "rb+");
    stHuesped huesped;
    int op, pos, val, encontrado, control;
    long long int min = 1000000000, max = 9999999999;

    pos = buscarPosxDNI(dniBus);

    if (pos == -1 || arch == NULL) {
        if (arch) fclose(arch);
        return 0;
    }

    printf("\n--Huesped Encontrado--\n");
    printf("->Que quiere modificar?\n");
    printf("        1-DNI\n");
    printf("        2-Nombre y Apellido\n");
    printf("        3-Telefono\n");
    printf("        4-Email\n");
    scanf("%i", &op);

    fseek(arch, pos * sizeof(stHuesped), SEEK_SET);
    fread(&huesped, sizeof(stHuesped), 1, arch);

    switch (op)
    {
    case 1:
        do {
            val = 1;
            printf("        DNI nuevo: ");
            while (getchar() != '\n');
            fgets(huesped.DNI, sizeof(huesped.DNI), stdin);
            huesped.DNI[strcspn(huesped.DNI, "\n")] = 0;

            int len = strlen(huesped.DNI);
            if (len < 1) val = 0;

            for (int i = 0; i < len; i++) {
                if (huesped.DNI[i] < '0' || huesped.DNI[i] > '9') {
                    val = 0;
                }
            }

            if (val == 0) {
                printf("\n--DNI invalido--\n");
            } else {
                encontrado = DNIexiste(huesped.DNI);
                if (encontrado) {
                    printf("\n--DNI ya existente--\n");
                    val = 0;
                }
            }
        } while (val == 0);
        break;

    case 2:
        printf("Ingrese el nuevo Nombre y Apellido: ");
        while (getchar() != '\n');
        fgets(huesped.NombreYApelido, sizeof(huesped.NombreYApelido), stdin);
        break;

    case 3:
        do {
            printf("        Telefono nuevo: ");
            control = scanf("%lld", &huesped.telefono);

            if (control != 1 || huesped.telefono < min || huesped.telefono > max) {
                printf("\n--Telefono no valido--\n");

                if (control != 1) {
                    while (getchar() != '\n');
                }
            }
        } while (control != 1 || huesped.telefono < min || huesped.telefono > max);
        break;

    case 4:
        do {
            val = 1;
            printf("        Email nuevo: ");
            while (getchar() != '\n');
            fgets(huesped.email, sizeof(huesped.email), stdin);

            if (strchr(huesped.email, '@') == NULL || strchr(huesped.email, '.') == NULL) {
                val = 0;
            } else {
                encontrado = EMAILexiste(huesped.email);
                if (encontrado) val = 0;
            }
        } while (val == 0);
        break;

    default:
        printf("\nOpcion invalida\n");
        break;
    }

    fseek(arch, pos * sizeof(stHuesped), SEEK_SET);
    fwrite(&huesped, sizeof(stHuesped), 1, arch);

    fclose(arch);
    return 1;
}

void mostrarRegistro()
{
    FILE *arch = fopen("archHuesped", "rb");
    if (arch == NULL) return;

    mostrarHuesped(arch);
    fclose(arch);
}

void mostrarHuesped(FILE *arch)
{
    stHuesped huesped;

    if (fread(&huesped, sizeof(stHuesped), 1, arch) > 0) {
        datoHuespedMostrar(huesped);
        mostrarHuesped(arch);
    }
}

void listarHuespedesOrdenados()
{
    FILE *arch = fopen("archHuesped", "rb");

    if (arch == NULL) return;

    int val;

    fseek(arch, 0, SEEK_END);
    val = ftell(arch) / sizeof(stHuesped);
    rewind(arch);

    stHuesped *arr = malloc(sizeof(stHuesped) * val);

    if (arr != NULL) {
        fread(arr, sizeof(stHuesped), val, arch);
        ordenarPorNombre(arr, val);
        mostrarArregloOrdenado(arr, val, 0);
        free(arr);
    }

    fclose(arch);
}

void ordenarPorNombre(stHuesped arr[], int validos)
{
    int i, j, posMenor;
    stHuesped aux;

    for (i = 0; i < validos - 1; i++) {
        posMenor = i;

        for (j = i + 1; j < validos; j++) {
            if (strcmp(arr[j].NombreYApelido, arr[posMenor].NombreYApelido) < 0) {
                posMenor = j;
            }
        }

        aux = arr[i];
        arr[i] = arr[posMenor];
        arr[posMenor] = aux;
    }
}

void mostrarArregloOrdenado(stHuesped arr[], int val, int i)
{
    if (i < val) {
        datoHuespedMostrar(arr[i]);
        mostrarArregloOrdenado(arr, val, i + 1);
    }
}

void datoHuespedMostrar(stHuesped huesped)
{
    printf("\n-----------------\n");
    printf("    Nombre y Apellido: %s\n", huesped.NombreYApelido);
    printf("    DNI: %s\n", huesped.DNI);
    printf("    Telefono: %lld\n", huesped.telefono);
    printf("    Email: %s", huesped.email);
}



