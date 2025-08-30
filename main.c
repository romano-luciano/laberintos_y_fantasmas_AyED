#include "tablero.h"

void mostrarCharEnPantalla(void *fp, void *elem);

int main()
{
    tConfigTablero config;
    tTablero tablero;
    tPosObjeto objetos;

    configuracionTableroCargar(&config,"configs.txt");
    tableroCrear(&tablero,&config);
    tableroInicializar(&tablero, ' ');
    tableroDibujarParedes(&tablero);
    tableroEstablecerEntrada(&tablero);
    tableroEstablecerSalida(&tablero);

    objetosCrear(&objetos,&config);
    tableroColocarObjetosAleatorio(&tablero, objetoParedesObtenerPunteroCoordenadas(&objetos),
                                   configuracionTableroObtenerCantidadParedes(&config), CARACTER_PARED);
    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos),
                                   configuracionTableroObtenerCantidadPremios(&config), CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos),
                                   configuracionTableroObtenerCantidadVidas(&config), CARACTER_VIDA);

    tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);
    tableroDestruir(&tablero);
    objetosDestruir(&objetos);
    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
