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
    }


    endwin();
    return 0;
}