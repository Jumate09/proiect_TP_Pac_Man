#include "functii_proiect.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int i;
    dificultate_t dificultate;
    dificultate.prc_puncte=20;
    dificultate.prc_ziduri=96;
    dificultate.nr_fantome=2;
    initscr();
    srand(time(NULL));

    i=strat_window();
    switch (i)
    {
        case 0:
        {
            select_dificulty(&dificultate);
            singleplayer(dificultate);
            break;
        }
        case 1:
        {
            multiplayer(dificultate);
            break;
        }
        case 2:
        {
            leaderboard();
        }
        default :
        {
            break;
        }
    }

    
    //refresh();
    //getch();
    endwin();
    return 0;
    
}