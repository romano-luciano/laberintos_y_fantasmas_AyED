#include "jugador.h"

int jugadorCrear(tJugador *jugador, unsigned vidasInicial)
{
    jugador->vMovimientos = (char*)malloc(CAP_INICIAL_VECTOR_MOVIMIENTOS * sizeof(tCoordenadas));
    if(!jugador->vMovimientos)
        return TABLERO_SIN_MEM;
    jugador->capMaxMovimientos = CAP_INICIAL_VECTOR_MOVIMIENTOS;
    return TODO_OK;
}

void jugadorInicializar(tJugador *jugador, const tCoordenadas *posInicial)
{
    jugador->cantMovimientos = 0;
    jugador->posicionActual.x = posInicial->x;
    jugador->posicionActual.y = posInicial->y;
    jugador->puntaje = 0;
}
