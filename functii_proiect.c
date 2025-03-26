#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define min_x 20
#define min_y 60



int verificare_ecran(WINDOW * win)
{
    int mx,my;
    getmaxyx(win,mx,my);
    if((min_x<mx)&&(min_y<my))
    {
        return 1;
    }
    return 0;
}

void moving_key()
{
    
    cbreak();
    noecho();
    halfdelay(1);
    keypad(stdscr,TRUE);
    int ch,x=0,y=0,my,mx,ch1;
    getmaxyx(stdscr,mx,my);
    mvprintw(0,0,">>Press any key to start<<  elem max sunt %d si %d\n",mx,my);
    printw("use arrow keys to play max coordonates are %d  %d",my,mx);
    refresh();
    move(3,2);
    while(1)
    {
        ch=getch();
        if(ch!=-1)
        {
            ch1=ch;
        }
        switch(ch)
        {
            case('w'):
            {
                getyx(stdscr,x,y);
                if(x>3)
                {
                    mvprintw(x,y-1," ");
                    x--;
                    mvprintw(x,y-1,"P");
                }
                break;
            }
            case('a'):
            {
                getyx(stdscr,x,y);
                if(y>0)
                {
                    mvprintw(x,y-1," ");
                    
                    mvprintw(x,y-2,"P");
                }
                break;
            }
            case('s'):
            {
                getyx(stdscr,x,y);
                move(x,y);
                if(x<mx-1)
                {
                    mvprintw(x,y-1," ");
                    x++;
                    mvprintw(x,y-1,"P");
                }
                break;
            }
            case('d'):
            {
                getyx(stdscr,x,y);
                if(y<my-1)
                {
                    mvprintw(x,y-1," ");
                    
                    mvprintw(x,y,"P");
                }
                break;
            }
            case(-1):
            {
                switch(ch1)
                {
                    case('w'):
                    {
                        getyx(stdscr,x,y);
                        if(x>3)
                        {
                        mvprintw(x,y-1," ");
                        x--;
                        mvprintw(x,y-1,"P");
                        }
                    break;
                    }
                    case('a'):
                    {   
                        getyx(stdscr,x,y);
                        if(y>0)
                        {
                            mvprintw(x,y-1," ");
                            
                            mvprintw(x,y-2,"P");
                        }
                        break;
                    }
                    case('s'):
                    {
                        getyx(stdscr,x,y);
                        move(x,y);
                        if(x<mx-1)
                        {
                            mvprintw(x,y-1," ");
                            x++;
                            mvprintw(x,y-1,"P");
                        }
                        break;
                    }
                    case('d'):
                    {
                        getyx(stdscr,x,y);
                        if(y<my-1)
                        {
                            mvprintw(x,y-1," ");
                    
                            mvprintw(x,y,"P");
                        }       
                        break;
                    }
                }
            }  
        }
        if(ch=='q')
        {
            break;
        }
        
        
    }

    getch();
}





