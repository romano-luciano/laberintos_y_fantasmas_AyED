#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "macros.h"

typedef void (*Accion)(void *elem, void *extra);

typedef struct
{
    unsigned x;
    unsigned y;
}tCoordenadas;

typedef struct
{
    char **tablero;
    tCoordenadas limite;
}tTablero;

typedef struct
{
    tCoordenadas jugador;
    tCoordenadas entrada;
    tCoordenadas *premio;
    tCoordenadas *paredes;
    tCoordenadas *vidas;
}tPosObjeto;

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

//////////////////////////////////////////////////////////////////
///
int tableroCrear(tTablero *tablero, const tConfigTablero *config);
void tableroDestruir(tTablero *tablero);
void tableroDibujarParedes(tTablero *tablero);
//void tableroInicializar(tTablero *tablero, const tConfigTablero *config, tPosObjeto *objetosPosiciones);
void tableroInicializar(tTablero *tablero, char caracter);
void tableroImprimir(const tTablero *tablero, FILE *fp, Accion mostrar);
int tableroPosicionEstaDisponible(const tTablero *tablero, const tCoordenadas *coords);
void tableroColocarObjetosAleatorio(tTablero *tablero, tCoordenadas *coords, unsigned cantObj, char caracter);
void tableroEstablecerEntrada(tTablero *tablero);
void tableroEstablecerSalida(tTablero *tablero);

//////////////////////////////////////////////////////////////////
///
int objetosCrear(tPosObjeto *objetos, const tConfigTablero *config);
void objetosDestruir(tPosObjeto *objetos);
tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite);
tCoordenadas* objetoParedesObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoPremioObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoVidasObtenerPunteroCoordenadas(const tPosObjeto *objeto);

#endif // TABLERO_H_INCLUDED
