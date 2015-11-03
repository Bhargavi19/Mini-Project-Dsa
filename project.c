#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include"project.h"
#include"graphics_funcs.h"
#define MENUMAX 5
void drawmenu(int item)
{
	int c;
	//boxx b = {1,' ',3};
	int xco, yco;
	yco = maxrows/2 - 10;
	xco = maxcols/2 - 20;
	char mainmenu[20] = "WELCOME TO SORTING";
	char menu[MENUMAX][21] = {"Insertion Sort", 
		"Merge Sort", 
		"Selection Sort",
		"Bubble Sort",
		"Exit"};
	init_pair(1, COLOR_CYAN, COLOR_YELLOW);
	init_pair(2, COLOR_RED, COLOR_YELLOW);
	clear();
	Draw_Fill(xco-2, yco-2, 50, 20, COLOR_YELLOW);
	//box(stdscr, 0, 0);
	attron( A_UNDERLINE);
	attron( COLOR_PAIR(1));
	box(stdscr,0,0);
	attroff( COLOR_PAIR(1));
	attron( COLOR_PAIR(2));
	mvaddstr(yco, xco+15, mainmenu);
	attroff(COLOR_PAIR(2));
	attroff(A_UNDERLINE);
	attron( COLOR_PAIR(2));
	for(c = 0 ; c < MENUMAX ; c++)
	{
		if( c == item ){
			attron(A_REVERSE);
			mvaddstr(yco+2+(c*2),xco+5, menu[c]);
			attroff(A_REVERSE);
		}
		else 
			mvaddstr(yco+2+(c*2), xco+5, menu[c]);
	}
	mvaddstr(yco+2+(c*2), xco, "Use arrow keys to move -  Enter to select:");
	attroff(COLOR_PAIR(2));
	refresh();
}
void print_intermediate_menu(int no){
        int i;
        char menu[4][20] = { "Next Step-->", "SKIP TO END", "<--Previous Step" };
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        for( i = 0 ; i < 4 ; i++){
                move(coords[0].y + AIR + i + 1, 0);
                clrtoeol();
        }
        attron(COLOR_PAIR(1));
        for(i = 0 ; i < 4 ; i++){
                if(i == no){
                        attron(A_REVERSE);
                        mvprintw(coords[0].y + AIR + i + 1, 30, menu[i]);
                        attroff(A_REVERSE);
                }
                else
                        mvprintw(coords[0].y + AIR + i + 1, 30, menu[i]);
        }
        attroff(COLOR_PAIR(1));
        refresh();
}
int Get_Intermediate_Choice(){
        int ch, menuitem = 0;
        print_intermediate_menu(menuitem);
        do
        {
                ch = getch();
                switch(ch){
                        case KEY_UP :
                                menuitem--;
                                if(menuitem < 0) menuitem = 2;
                                break;

                        case KEY_DOWN :
                                menuitem++;
                                if(menuitem > 2) menuitem = 0;
                                break;
                        default:
                                break;
                }
                print_intermediate_menu(menuitem);
        }while(ch != '\n');
        return menuitem;
}
void Print_Animation(int value) {
        boxx b = { 3, value, 5};
	clear();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(A_BLINK | COLOR_PAIR(1));
	mvprintw(coords[0].y - AIR - 777777, 20, "Use up-down keys to increase or decrease speed:(Max 20) ");
        mvprintw(coords[0].y - AIR - 5, 20, "ANIMATION SPEED: ");
        printbox(40, coords[0].y-AIR -6, b);
        attroff(COLOR_PAIR(1));
        refresh();
}
void Print_SORT(int s){
        int i;
        int heady = coords[0].y - AIR - BUFFER*10;
        int headx1 = maxcols/2 - 7;
        int headx2 = maxcols/2 + 7;
        box(stdscr, 0, 0);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        for(i = headx1 ; i <=  headx2 ; i++){
                mvaddch(heady, i, '-');
                mvaddch(heady + 5, i, '-');
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2));
	if(s == INSERTION)
        mvprintw(heady + 2, maxcols/2-6, "INSERTION SORTING");
	else if( s == SELECTION)
	 mvprintw(heady + 2, maxcols/2-6,"SELECTION SORTING");
	else if(s == BUBBLE)
	mvprintw(heady + 2, maxcols/2-6, "BUBBLE SORTING");
        attroff(COLOR_PAIR(2));
}
int main() {
	initscr();
	cbreak();
	start_color();
	curs_set(0);
	int menuitem = 0, key;
	getmaxyx(stdscr, maxrows, maxcols);
	while(1){
		initialisearr(2, 3);
		initialisecoords(); 
		drawmenu(menuitem);
		keypad(stdscr, TRUE);
		noecho();
		do
		{
			key = getch();
			switch(key)
			{
				case KEY_DOWN:
					menuitem++;
					if(menuitem > MENUMAX-1) menuitem = 0;
					break;
				case KEY_UP:
					menuitem--;
					if(menuitem < 0) menuitem = MENUMAX-1;
					break;
				default:
					break;

			}
			drawmenu(menuitem);
		} while(key != '\n');
		echo();
		switch(menuitem){
			case 0: 
				Insertion_Sort();
				break;
			case 1:
				Merge_Sort();
				break;
			case 2:
				Selection_Sort();
				break;
			case 3:
				Bubble_Sort();
				break;
			case 4:
				endwin();
				return 0;
				//break;
			default :
				clear();
		}
		getch();
	}
	//getch();
	endwin();
	return 0;
}
