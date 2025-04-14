#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct{
    int x;
    int y;
}coord_t;
char *alegere_screen1[]={"SINGLEPLAYER","MULTIPLAYER","LEADERBOARD","EXIT"};

int verificare_ecran(WINDOW* win)
{
    int x,y;
    getmaxyx(win,x,y);
    if((x>=30)&&(y>=60))
    {
        printf("%d %d",x,y);
        return 1;
    }
    //printf("%d %d",x,y);
    return 0;
}
void refresh_w(WINDOW* win)
{
    wrefresh(stdscr);
    wrefresh(win);
}


WINDOW* select_option(int i)
{
    WINDOW* loc_win=newwin(30,60,0,0);

    mvwprintw(loc_win,1,15,"Press *q* to exit and r to enter");
    mvwprintw(loc_win,3,23,alegere_screen1[0]);
    mvwprintw(loc_win,4,23,alegere_screen1[1]);
    mvwprintw(loc_win,5,23,alegere_screen1[2]);

    box(loc_win,0,0);

    wattron(loc_win,A_REVERSE);
    mvwprintw(loc_win,i+3,23,alegere_screen1[i]);
    wattroff(loc_win,A_REVERSE);
    return loc_win;
}
//==============
//generare harta
//==============




//=========
//movingkey
//=========
void draw_player(WINDOW* win, int x, int y)
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, x, y, "P");
    wrefresh(win);
}
void singleplayer()
{
    cbreak();
    noecho();
    halfdelay(1);
    WINDOW* screen2;
    screen2=newwin(30,60,0,0);
    box(screen2,0,0);
    coord_t coord = {2, 2};
    draw_player(screen2, coord.x, coord.y);

    int ch = 0, ch1 = 0;
    while (1)   
    {
        ch = getch();
        if (ch != -1)
            ch1 = ch;
        if (ch == 'q')
            break;

        switch ((ch != -1) ? ch : ch1)
        {
            case 'w': if (coord.x > 2) coord.x--; break;
            case 'a': if (coord.y > 2) coord.y--; break;
            case 's': if (coord.x < 28) coord.x++; break;
            case 'd': if (coord.y < 58) coord.y++; break;
        }

        draw_player(screen2, coord.x, coord.y);
    }
    delwin(screen2);
}





//ecran de inceput
int strat_window()
{
    noecho();
    curs_set(FALSE);
    keypad(stdscr,TRUE);

    if(verificare_ecran(stdscr)==0)
    {
        mvwprintw(stdscr,0,0,"ECRAN PREA MIC");
        wrefresh(stdscr);
        getch();
        endwin();
        exit(-1);
    }
    WINDOW* screen1=newwin(30,60,0,0);
    int ch,i=0;

    box(screen1,0,0);
    screen1=select_option(0);
    refresh_w(screen1);
    while((ch!='q')&&(ch!='r'))
    {
        ch=getch();
        if(ch=='r')
        {
            break;
        }
        switch(ch)
        {
            case KEY_DOWN:
            {
                if(i<2)
                {
                    i++;
                    screen1=select_option(i);
                    refresh_w(screen1);
                }
                break;
            }
            case KEY_UP:
            {
                if(i>0)
                {
                    i--;
                    screen1=select_option(i);
                    refresh_w(screen1);

                }
                break;
            }
            case 'r':
            {
                for(int i=0;i<31;i++)
                {
                    for(int j=0;j<61;j++)
                    {
                        mvwprintw(screen1,i,j," ");
                    }
                }
                wrefresh(screen1);
                delwin(screen1);
                getch();
                return i;
                break;
            }
            case 'q':
            {
                delwin(screen1);
                endwin();
                exit(-1);
                break;
            }
        }
    }
    return i;
}


