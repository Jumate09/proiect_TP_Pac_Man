#ifndef __functii_proiect__
#define __functii_proiect__

#include <ncurses.h>

typedef struct{
    int x;
    int y;
}coord_t;

int strat_window();

void singleplayer();

void multiplayer();

typedef int map_t[30][60];
typedef struct{
    int prc_ziduri;
    int prc_puncte;
    int nr_fantome;
}dificultate_t;


#endif