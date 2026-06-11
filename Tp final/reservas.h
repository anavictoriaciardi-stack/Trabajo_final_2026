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
int bajaReserva(int id_reserva);
int buscarPosxID(int id_reserva);
int mostrarUnaReserva(int id);
int listadoReservas();

#endif // RESERVAS_H_INCLUDED
