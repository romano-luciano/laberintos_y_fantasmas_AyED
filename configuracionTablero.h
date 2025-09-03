#ifndef CONFIGURACIONTABLERO_H_INCLUDED
#define CONFIGURACIONTABLERO_H_INCLUDED
#include "macros.h"
#include "coordenadas.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
    /*
     • filas: número de filas del tablero
    • columnas: número de columnas del tablero
    • vidas_inicio: número de vidas.
    • maximo_numero_fantasmas: número de fantasmas
    • maximo_numero_premios: número de premios
    • maximo_vidas_extra: número de vidas maximo_vidas_extra
    */
    tCoordenadas tamTablero;
    unsigned cantVidaInicial;
    unsigned cantFant;
    unsigned cantPremio;
    unsigned cantVidaExtra;
    unsigned cantParedes; // no cuenta las paredes en los bordes del tablero
}tConfigTablero;

int configuracionTableroCargar(tConfigTablero *config, const char *nomArch);
int configuracionTableroObtenerCantidadVidas(const tConfigTablero *config);
int configuracionTableroObtenerCantidadPremios(const tConfigTablero *config);
int configuracionTableroObtenerCantidadParedes(const tConfigTablero *config);

#endif // CONFIGURACIONTABLERO_H_INCLUDED
