#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ROWS 15
#define COLLUMS 30
#define MAP [ROWS][COLLUMS]
#define MAX_FANTOME 5



//==============
//generare harta
//==============

typedef int map_t[ROWS][COLLUMS];

typedef struct{
    int x;
    int y;
}coord_t;

typedef struct{
    WINDOW* screen;
    map_t map;
    coord_t player;
    coord_t fantomite[MAX_FANTOME];
    int nr_puncte;

}harta_t;

typedef struct{
    int prc_ziduri;
    int prc_puncte;
    int nr_fantome;
}dificultate_t;

int is_map_playable(map_t* loc_map)
{
    int start_row = -1, start_col = -1;
    int open_space_value = ' '; 
    int wall_value = '#';       

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLLUMS; j++)
        {
            if ((*loc_map)[i][j] == open_space_value)
            {
                start_row = i;
                start_col = j;
                break;
            }
        }
        if (start_row != -1)
        {
            break;
        }
    }

    if (start_row == -1)
    {
        return -1;
    }

    int visited[ROWS][COLLUMS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLLUMS; j++)
        {
            visited[i][j] = 0;
        }
    }

    int queue[ROWS * COLLUMS * 2];
    int head = 0, tail = 0;

    queue[tail++] = start_row;
    queue[tail++] = start_col;
    visited[start_row][start_col] = 1;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int nr,r,c,nc;
    while (head < tail)
    {
        r = queue[head++];
        c = queue[head++];

        for (int i = 0; i < 4; i++)
        {
            nr = r + dr[i];
            nc = c + dc[i];

            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLLUMS &&
                (*loc_map)[nr][nc] == open_space_value && !visited[nr][nc])
            {
                visited[nr][nc] = 1;
                queue[tail++] = nr;
                queue[tail++] = nc;
            }
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLLUMS; j++)
        {
            if ((*loc_map)[i][j] == open_space_value && !visited[i][j])
            {
                return 0;
            }
        }
    }

    return 1;
}
void generare_harta(map_t* loc_map,dificultate_t dif)
{

    int random;
    do
    {

    for (int i=0 ;i<ROWS ; i++)
    {
        for (int j=0 ;j<COLLUMS ;j++)
        {
            (*loc_map)[i][j]='#';
        }
    }
    for (int i=1 ;i<ROWS-1 ; i++)
    {
        for (int j=1 ;j<COLLUMS-1 ;j++)
        {
            if((rand()%100)>dif.prc_ziduri)
            {
                (*loc_map)[i][j]=' ';
                random=rand()%3;
                if(random<0)
                {
                    random=-random;
                }
                if(i>ROWS/2)
                {
                    if(j<=COLLUMS/2)
                    {
                        for(int jj=j;jj<(COLLUMS-random-1);jj++)
                        {
                            (*loc_map)[i][jj]=' ';
                        }
                    }
                    else
                    {
                        for(int ii=i;ii>1+(random);ii--)
                        {
                            (*loc_map)[ii][j]=' ';
                        }
                    }
                }
                else
                {
                    if(j>COLLUMS/2)
                    {                       
                        for(int jj=j;jj>1+(random);jj--)
                        {
                            (*loc_map)[i][jj]=' ';
                        }
                    }
                    else
                    {
                        for(int ii=i;ii<(ROWS-random-1);ii++)
                        {
                            (*loc_map)[ii][j]=' ';
                        }
                    }
                }
            }
        }
    }
    
    }while(is_map_playable(loc_map)!=1);
    for(int i=1;i<ROWS-1;i++)
    {
        for(int j=1;j<COLLUMS-1;j++)
        {
            if((*loc_map)[i][j]==' ')
            {
                if((rand()%100)<dif.prc_puncte)
                {
                    (*loc_map)[i][j]='0';
                }
            }
        }
    }
}

void print_map(harta_t harta)
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLLUMS;j++)
        {
            mvwprintw(harta.screen,i,j,"%c",harta.map[i][j]);
        }
    }
}


//=========
//movingkey
//=========
void draw_player(harta_t harta,dificultate_t dif)
{
    werase(harta.screen);
    print_map(harta);
    wrefresh(harta.screen);
    mvwprintw(harta.screen, harta.player.x, harta.player.y, "P");
    for(int i=0;i<dif.nr_fantome;i++)
        mvwprintw(harta.screen,harta.fantomite[i].x,harta.fantomite[i].y,"&");
    wrefresh(harta.screen);
}
void cauta_start(harta_t* harta_loc,dificultate_t dif)
{
    (*harta_loc).player.x=-1;
    for(int i=1;i<ROWS-1;i++)
    {
        for(int j=0;j<COLLUMS-1;j++)
        {
            if((*harta_loc).map[i][j]==' ')
            {
                (*harta_loc).player.x=i;
                (*harta_loc).player.y=j;
                break;
            }
        }
        if((*harta_loc).player.x!=-1)
        {
            break;
        }
    }
    for(int i=0;i<dif.nr_fantome;i++)
    {
        (*harta_loc).fantomite[i].x=-1;
        for(int x=ROWS-2;x>0;x--)
        {
            for(int y=COLLUMS-2;y>0;y--)
            {
                if((*harta_loc).map[x][y]==' ')
                {
                    (*harta_loc).map[x][y]='@';
                    (*harta_loc).fantomite[i].x=x;
                    (*harta_loc).fantomite[i].y=y;
                    break;
                }
            }
            if((*harta_loc).fantomite[i].x!=-1)
            {
                break;
            }
        }
    }

}
int verificare_coliziune(harta_t* harta_loc,dificultate_t dif)
{
    if((*harta_loc).map[(*harta_loc).player.x][(*harta_loc).player.y]=='#')
    {
        return 0;
    }
    for(int i=0;i<dif.nr_fantome;i++)
    {
        if((harta_loc->player.x==harta_loc->fantomite[i].x)&&(harta_loc->player.y==harta_loc->fantomite[i].y))
        {
            return 0;
        }
    }
    if((*harta_loc).map[(*harta_loc).player.x][(*harta_loc).player.y]=='@')
    {
        return -2;
    }
    if((*harta_loc).map[(*harta_loc).player.x][(*harta_loc).player.y]=='0')
    {
        return -1;
    }
    return 1;
}
void move_fantoma(harta_t* harta_loc,int i)
{
    int ch = rand()%4;
    printf("%d ",ch);
    if(ch<0)
    {
        ch=-ch;
    }
    switch (ch)
    {
        case 0: if (harta_loc->fantomite[i].x > 1) harta_loc->fantomite[i].x--; break;
        case 1: if (harta_loc->fantomite[i].y > 1) harta_loc->fantomite[i].y--; break;
        case 2: if (harta_loc->fantomite[i].x < ROWS-2) harta_loc->fantomite[i].x++; break;
        case 3: if (harta_loc->fantomite[i].y < COLLUMS-2) harta_loc->fantomite[i].y++; break;
    }
    
}
void singleplayer()
{
    cbreak();
    noecho();
    halfdelay(5);
    dificultate_t dificultate;
    dificultate.prc_puncte=20;
    dificultate.prc_ziduri=96;
    dificultate.nr_fantome=2;
    harta_t harta_loc;
    harta_loc.nr_puncte=0;
    generare_harta(&harta_loc.map,dificultate);
    harta_loc.screen=newwin(ROWS,COLLUMS,0,0);
    print_map(harta_loc);
    cauta_start(&harta_loc,dificultate);
    printf("%d %d",harta_loc.player.x ,harta_loc.player.y);
    draw_player(harta_loc,dificultate);
    int ch = 0, ch1 = 0,N=0;
    cbreak();
    nodelay(harta_loc.screen, FALSE);
    ch=getch();
    halfdelay(3);

    while (1)   
    {
        ch = getch();
        if (ch != -1)
            ch1 = ch;
        if (ch == 'q')
            break;
        
        switch ((ch != -1) ? ch : ch1)
        {
            case 'w': if (harta_loc.player.x > 1) harta_loc.player.x--; break;
            case 'a': if (harta_loc.player.y > 1) harta_loc.player.y--; break;
            case 's': if (harta_loc.player.x < ROWS-2) harta_loc.player.x++; break;
            case 'd': if (harta_loc.player.y < COLLUMS-2) harta_loc.player.y++; break;
        }
        switch(verificare_coliziune(&harta_loc,dificultate))
        {
            case 0:
            {
                werase(harta_loc.screen);
                mvwprintw(harta_loc.screen,1,1,"joc terminat");
                mvwprintw(harta_loc.screen,2,1,"ati acumulat %d puncte",harta_loc.nr_puncte);
                wrefresh(harta_loc.screen);
                nocbreak();
                cbreak();
                getch();
                delwin(harta_loc.screen);
                endwin();
                exit(0);
                break;
            }
            case -1:
            {
                harta_loc.nr_puncte++;
                harta_loc.map[harta_loc.player.x][harta_loc.player.y]=' ';
                break;
            }
            case -2:
            {
                harta_loc.nr_puncte=harta_loc.nr_puncte+3;
                harta_loc.map[harta_loc.player.x][harta_loc.player.y]=' ';
                break;
            }
            default :
            {
                break;
            }
        }
        draw_player(harta_loc,dificultate);
        if(N==1)
        {
            N=0;
        }
        else
        {
            N=1;
            for(int i=0;i<dificultate.nr_fantome;i++)
            {
                move_fantoma(&harta_loc,i);
            }
        }
    }
    delwin(harta_loc.screen);
}





//ecran de inceput
char *alegere_screen1[]={"SINGLEPLAYER","MULTIPLAYER","LEADERBOARD","EXIT"};


int verificare_ecran(WINDOW* win)
{
    int x,y;
    getmaxyx(win,x,y);
    if((x>=ROWS)&&(y>=COLLUMS))
    {
        return 1;
    }
    return 0;
}
void refresh_w(WINDOW* win)
{
    wrefresh(stdscr);
    wrefresh(win);
}


void select_option(int i,WINDOW* loc_win)
{
    werase(loc_win);

    mvwprintw(loc_win,1,1,"Press *q* to exit");
    mvwprintw(loc_win,2,1,"Press *r* to enter");
    mvwprintw(loc_win,3,1,alegere_screen1[0]);
    mvwprintw(loc_win,4,1,alegere_screen1[1]);
    mvwprintw(loc_win,5,1,alegere_screen1[2]);

    box(loc_win,0,0);

    wattron(loc_win,A_REVERSE);
    mvwprintw(loc_win,i+3,1,alegere_screen1[i]);
    wattroff(loc_win,A_REVERSE);

}


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
    WINDOW* screen1=newwin(ROWS,COLLUMS,0,0);
    int ch,i=0;

    select_option(0,screen1);
    refresh_w(screen1);
    while(1)
    {
        ch=getch();
        if(ch=='r')
        {
            return i;
        }
        if(ch=='q')
        {
            return -1;
        }
        if(ch==KEY_DOWN)
        {
            if(i!=2)
            {
                select_option(++i,screen1);
                refresh_w(screen1);
            }
        }
        if(ch==KEY_UP)
        {
            if(i!=0)
            {
                select_option(--i,screen1);
                refresh_w(screen1);
            }
        }
    }
}


