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
//movingkey
WINDOW* moving_key(int x,int y)
{
    WINDOW* loc_win=newwin(30,60,1,1);
    box(loc_win,0,0);
    mvwprintw(loc_win,x,y,"P");
    return loc_win;
}
void singleplayer()
{
    cbreak();
    noecho();
    halfdelay(1);
    WINDOW* screen2;
    screen2=newwin(30,60,0,0);
    box(screen2,0,0);
    coord_t coord;

    int ch=0,ch1=0;
    wmove(screen2,2,2);
    while(1)
    {
        ch=getch();
        if(ch!=-1)
        {
            ch1=ch;
        }
        if(ch=='q')
        {
            break;
        }
        switch(ch)
        {
            case('w'):
            {
                getyx(screen2,coord.x,coord.y);
                if(coord.x>2)
                {
                    screen2=moving_key(coord.x-1,coord.y-1);

                    refresh_w(screen2);
                }

                break;
            }
            case('a'):
            {
                getyx(screen2,coord.x,coord.y);
                if(coord.y>2)
                {
                    screen2=moving_key(coord.x,coord.y-3);

                    refresh_w(screen2);
                }
                break;
            }
            case('s'):
            {
                getyx(screen2,coord.x,coord.y);
                if(coord.x<29)
                {
                    screen2=moving_key(coord.x+1,coord.y-1);
                    refresh_w(screen2);
                }

                break;
            }
            case('d'):
            {
                getyx(screen2,coord.x,coord.y);
                if(coord.y<59)
                {
                    screen2=moving_key(coord.x,coord.y+2);
                    refresh_w(screen2);
                }
                break;
            }
            case(-1):
            {
                switch(ch1)
                {
                    case('w'):
                    {
                        getyx(screen2,coord.x,coord.y);
                        if(coord.x>2)
                        {
                            screen2=moving_key(coord.x-1,coord.y-1);
                            refresh_w(screen2);
                        }

                        break;
                    }
                    case('a'):
                    {
                        getyx(screen2,coord.x,coord.y);
                        if(coord.y>2)
                        {
                            screen2=moving_key(coord.x,coord.y-3);
                            refresh_w(screen2);
                        }
                        break;
                    }
                    case('s'):
                    {
                        getyx(screen2,coord.x,coord.y);
                        if(coord.x<29)
                        {
                            screen2=moving_key(coord.x+1,coord.y-1);
                            refresh_w(screen2);
                        }

                        break;
                    }
                    case('d'):
                    {
                        getyx(screen2,coord.x,coord.y);
                        if(coord.y<59)
                        {
                            screen2=moving_key(coord.x,coord.y+1);
                            refresh_w(screen2);
                        }
                        break;
                    }
                }  
            }
        }               
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
    while((ch!='q')||(ch!='r'))
    {
        if(ch=='r')
        {
            break;
        }
        ch=getch();
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
                if(i==3)
                {
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
            case 'q':
            {
                delwin(screen1);

                endwin();
                exit(-1);
                break;
            }
            case 'r':
            {
            break;
            }
        }
    }

    delwin(screen1);
    return i;
}


