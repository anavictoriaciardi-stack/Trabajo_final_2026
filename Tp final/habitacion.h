#ifndef HABITACION_H_INCLUDED
#define HABITACION_H_INCLUDED

typedef struct{
    int numero;
    char tipo[10];//(simple/doble/suite)
    float precioxNoche;
    char estado[8]; //(libre/ocupada)
}stHabitacion;

typedef struct {
    float simple;
    float doble;
    float suite;
} stPrecios;

int altaHabitacion ();

#endif // HABITACION_H_INCLUDED
