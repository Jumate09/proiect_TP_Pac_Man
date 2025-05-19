#include "functii_proiect.h"
#include <ncurses.h>

int main(void)
{
    int i;
    initscr();

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