#ifndef __functii_proiect__
#define __functii_proiect__

#include <ncurses.h>

typedef struct{
    int x;
    int y;
}coord_t;

int strat_window();
int verificare_ecran(WINDOW*);
void refresh_w(WINDOW*);
void singleplayer();
void draw_player(WINDOW*,int,int);

#endif