#include "tablero.h"
#include <stdlib.h>

int configuracionTableroCargar(tConfigTablero *config, const char *nomArch)
{
    srand(time(NULL));
    char buffer[TAM_BUFFER];
    char *aux;
    unsigned iterador = 0;
    int numAux;
    FILE *fp = fopen(nomArch, "rt");
    if(!fp)
        return ARCHIVO_ERROR;

    /*
     Un ejemplo del archivo de texto que describe laberinto con los siguientes valores en los
    parámetros iniciales:
    • filas: 10
    • columnas: 10
    • vidas_inicio: 3.
    • maximo_numero_fantasmas: 2
    • maximo_numero_premios: 1
    • maximo_vidas_extra: 1
    */

    while(fgets(buffer,TAM_BUFFER,fp))
    {
        aux = strrchr(buffer, '\n');
        *aux = '\0';

        while(!ES_NUMERO(*aux))
            aux--;

        while(ES_NUMERO(*(aux-1)))
            aux--;

        numAux = atoi(aux);

        /*
        #define PARAMETRO_FILA_UBICACION 0
        #define PARAMETRO_COLUMNA_UBICACION 1
        #define PARAMETRO_VIDAS_INICIO_UBICACION 2
        #define PARAMETRO_CANT_FANTASMAS_UBICACION 3
        #define PARAMETRO_CANT_PREMIOS_UBICACION 4
        #define PARAMETRO_CANT_VIDAS_EXTRA_UBICACION 5
        */
        if(iterador == PARAMETRO_FILA_UBICACION)
        {
            config->tamTablero.x = numAux;
        }
        if(iterador == PARAMETRO_COLUMNA_UBICACION)
        {
            config->tamTablero.y = numAux;
        }
        if(iterador == PARAMETRO_VIDAS_INICIO_UBICACION)
        {
            config->cantVidaInicial = numAux;
        }
        if(iterador == PARAMETRO_CANT_FANTASMAS_UBICACION)
        {
            config->cantFant = numAux;
        }
        if(iterador == PARAMETRO_CANT_PREMIOS_UBICACION)
        {
            config->cantPremio = numAux;
        }
        if(iterador == PARAMETRO_CANT_VIDAS_EXTRA_UBICACION)
        {
            config->cantVidaExtra = numAux;
        }
        iterador++;
    }

    OBTENER_NUM_ALEATORIO(0, MAX_CANT_PAREDES, config->cantParedes);
    fclose(fp);
    return  TODO_OK;

}

int configuracionTableroObtenerCantidadParedes(const tConfigTablero *config)
{
   return config->cantParedes;
}

int configuracionTableroObtenerCantidadPremios(const tConfigTablero *config)
{
   return config->cantPremio;
}

int configuracionTableroObtenerCantidadVidas(const tConfigTablero *config)
{
   return config->cantVidaExtra;
}

/////////////////////////////////////////////////////////////////////////

void tableroEstablecerEntrada(tTablero *tablero)
{
    int posColumna;
    OBTENER_NUM_ALEATORIO(1, tablero->limite.x - 2,posColumna);
    tablero->tablero[0][posColumna] = CARACTER_ENTRADA;
}

void tableroEstablecerSalida(tTablero *tablero)
{
    int posColumna;
    OBTENER_NUM_ALEATORIO(1, tablero->limite.x - 2,posColumna);
    tablero->tablero[tablero->limite.x-1][posColumna] = CARACTER_SALIDA;
}

int tableroCrear(tTablero *tablero, const tConfigTablero *config)
{
    char **i;
    char **j;
    char **fin;
    tablero->tablero = (char**)malloc(config->tamTablero.y * sizeof(char*));
    if(!tablero->tablero)
        return TABLERO_SIN_MEM;

    fin = tablero->tablero + config->tamTablero.y;
    for(i = tablero->tablero; i < fin; i++)
    {
        *i = (char*)malloc(config->tamTablero.x * sizeof(char));
        if(!*i)
        {
            for(j = i - 1; j >= tablero->tablero; j--)
                free(*j);

            free(tablero->tablero);
            return TABLERO_SIN_MEM;
        }
    }
    tablero->limite.x = config->tamTablero.x;
    tablero->limite.y = config->tamTablero.y;

    return TODO_OK;
}

void tableroDestruir(tTablero *tablero)
{
    char **i;
    char **fin = tablero->tablero + tablero->limite.y;
    for(i = tablero->tablero; i < fin; i++)
        free(*i);

    free(tablero->tablero);
}

void tableroDibujarParedes(tTablero *tablero)
{
    int i;
    for(i = 0; i < tablero->limite.y; i++)
        tablero->tablero[i][0] = CARACTER_PARED;

    for(i = 0; i < tablero->limite.y; i++)
        tablero->tablero[i][tablero->limite.x - 1] = CARACTER_PARED;

    for(i = 0; i < tablero->limite.x; i++)
        tablero->tablero[0][i] = CARACTER_PARED;

    for(i = 0; i < tablero->limite.x; i++)
        tablero->tablero[tablero->limite.y-1][i] = CARACTER_PARED;
}

void tableroInicializar(tTablero *tablero, char caracter)
{
    int i,j;
    for(i = 1; i < tablero->limite.y - 1; i++)
    {
        for(j = 1 ; j < tablero->limite.x - 1; j++)
            tablero->tablero[i][j] = caracter;
    }
}

void tableroImprimir(const tTablero *tablero, FILE* fp, Accion mostrar)
{
    int i,j;
    for(i = 0; i < tablero->limite.y; i++)
    {
        for(j = 0; j < tablero->limite.x; j++)
            mostrar(fp,&tablero->tablero[i][j]);

        puts("");
    }
}

void tableroColocarObjetosAleatorio(tTablero *tablero, tCoordenadas *coords, unsigned cantObj, char caracter)
{
    int i;
    tCoordenadas coordsAleatorias;
    for(i = 0; i < cantObj; i++)
    {
        OBTENER_NUM_ALEATORIO(1,tablero->limite.y-1, coordsAleatorias.y);
        OBTENER_NUM_ALEATORIO(1,tablero->limite.x-1, coordsAleatorias.x);
        while(!POSICION_ESTA_DISPONIBLE(tablero->tablero,coordsAleatorias.y,coordsAleatorias.x))
        {
            OBTENER_NUM_ALEATORIO(1,tablero->limite.y-1, coordsAleatorias.y);
            OBTENER_NUM_ALEATORIO(1,tablero->limite.x-1, coordsAleatorias.x);
        }

        tablero->tablero[coordsAleatorias.y][coordsAleatorias.x] = caracter;
        (coords + i)->x = coordsAleatorias.x;
        (coords + i)->y = coordsAleatorias.y;
    }
}

int tableroPosicionEstaDisponible(const tTablero *tablero, const tCoordenadas *coords)
{
    if(tablero->tablero[coords->y][coords->x] == LUGAR_VACIO)
        return 1;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////


int objetosCrear(tPosObjeto *objetos, const tConfigTablero *config)
{
    if(config->cantParedes > 0)
    {
        objetos->paredes = (tCoordenadas *)malloc(config->cantParedes * sizeof(tCoordenadas));
        if(!objetos->paredes)
            return TABLERO_SIN_MEM;
    }
    //for(i = 0; i < cantParedesRandom; i++)
    //{
    //    OBTENER_NUM_ALEATORIO(1,config->tamTablero.x-1, (objetos->paredes + i)->x);
    //    OBTENER_NUM_ALEATORIO(1,config->tamTablero.y-1, (objetos->paredes + i)->y);
    //}

    if(config->cantPremio > 0)
    {
        objetos->premio = (tCoordenadas *)malloc(config->cantPremio * sizeof(tCoordenadas));
        if(!objetos->premio)
            return TABLERO_SIN_MEM;
    }

    if(config->cantVidaExtra > 0)
    {
        objetos->vidas = (tCoordenadas *)malloc(config->cantVidaExtra * sizeof(tCoordenadas));
        if(!objetos->vidas)
            return TABLERO_SIN_MEM;
    }

    return TODO_OK;
}

void objetosDestruir(tPosObjeto *objetos)
{
    free(objetos->premio);
    free(objetos->paredes);
    free(objetos->vidas);
}

tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite)
{
    tCoordenadas coords;
    OBTENER_NUM_ALEATORIO(0, limite->y, coords.y);
    OBTENER_NUM_ALEATORIO(0, limite->x, coords.x);
    return coords;
}

tCoordenadas* objetoParedesObtenerPunteroCoordenadas(const tPosObjeto *objeto)
{
    return objeto->paredes;
}

tCoordenadas* objetoPremioObtenerPunteroCoordenadas(const tPosObjeto *objeto)
{
    return objeto->premio;
}

tCoordenadas* objetoVidasObtenerPunteroCoordenadas(const tPosObjeto *objeto)
{
    return objeto->vidas;
}



