#ifndef __functii_proiect__
#define __functii_proiect__

#include <ncurses.h>

typedef struct{
    int x;
    int y;
}coord_t;
typedef struct{
    int prc_ziduri;
    int prc_puncte;
    int nr_fantome;
}dificultate_t;

int strat_window();

void singleplayer(dificultate_t );

void multiplayer(dificultate_t );

void leaderboard();

void select_dificulty(dificultate_t* );


typedef int map_t[30][60];



#endif