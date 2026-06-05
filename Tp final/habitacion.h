#ifndef HABITACION_H_INCLUDED
#define HABITACION_H_INCLUDED

typedef struct{
    int numero;
    char tipo[10];//(simple/doble/suite)
    float precioxNoche;
    char estado[8]; //(libre/ocupada)
}stHabitacion;

int altaHabitacion ();

#endif // HABITACION_H_INCLUDED
