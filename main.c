#include <stdio.h>
#include <ncurses.h>
#include "functii_proiect.h"

int main(void)
{ d
    initscr();
    if(verificare_ecran(stdscr)==0)
    {
        int mx,my;
        getmaxyx(stdscr,mx,my);
        mvprintw(1,0,"Redimensioneaza ecranul maximele acuatle sunt %d %d",mx,my);
        getch();
        endwin();
        return 0;
    }
    moving_key();



    endwin();
    return 0;
}