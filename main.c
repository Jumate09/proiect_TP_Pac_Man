#include "functii_proiect.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int i;
    initscr();
    srand(time(NULL));

    i=strat_window();
    switch (i)
    {
        case 0:
        {
            singleplayer();
            break;
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