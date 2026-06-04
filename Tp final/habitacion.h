#ifndef HABITACION_H_INCLUDED
#define HABITACION_H_INCLUDED

typedef struct{
    int numero;
    char tipo[10];//(simple/doble/suite)
    int precioxNoche;
    char estado; //(libre/ocupada)
}stHabitacion;

int altaHabitacion ();

#endif // HABITACION_H_INCLUDED
