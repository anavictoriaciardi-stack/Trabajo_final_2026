#ifndef HUESPED_H_INCLUDED
#define HUESPED_H_INCLUDED

typedef struct{
    char DNI[9];
    char NombreYApelido[30];
    long long int telefono;
    char email[30];
} stHuesped;
int altaHuesped();
int buscarPosxDNI(char DNIbus[]);
int bajaHuesped(char DNIbus[]);
int DNIexiste(char DNI[]);
int EMAILexiste(char EMAIL[]);
int modificarDatos(char dniBus[] );
void mostrarRegistro();
void mostrarHuesped(FILE *arch);
void datoHuespedMostrar(stHuesped huesped);
void listarHuespedesOrdenados();
void ordenarPorNombre(stHuesped arr[], int validos);
void mostrarArregloOrdenado(stHuesped arr[], int val, int i);
#endif // HUESPED_H_INCLUDED
