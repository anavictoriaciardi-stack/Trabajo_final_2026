#ifndef RESERVAS_H_INCLUDED
#define RESERVAS_H_INCLUDED

typedef struct{
    int idReserva;
    char dniHuesped[9];
    int numHabitacion;
    int cantNoches;
    float total;
} stReserva;
int generarId();
int altaReserva();

#endif // RESERVAS_H_INCLUDED
