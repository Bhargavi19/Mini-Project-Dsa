/*****************************************************************************
 * Copyright (C) Bhargavi Neti bhargavineti@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include"project.h"
#include"graphics_funcs.h"
#define MENUMAX 5
/*Function to display main menu*/
void drawmenu(int item)
{
	int c;
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
void init(){
	int i;
	for(i = 0;i < 8 ;i++)
		array[i].value = newarr[i];
}
/*Function toinput the array to be sorted*/
void Input_Array(){
	char ch;
	int i, j, num = 10;
	init_pair(1, COLOR_CYAN, COLOR_YELLOW);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	clear();
	attron( COLOR_PAIR(1));
	box(stdscr, 0, 0);
	attroff( COLOR_PAIR(1));
	initialisearr(2, 3);
	initialisecoords();
	printarray();
	mvprintw(coords[0].y + 3, 30, "Wish to edit the array?");
	mvscanw(coords[0].y + 3, 60, "%c", &ch);
	if(ch == 'y'){
		for(i = 0 ; i < 8 ; i++){
			for(j = 0 ; j < 8 ; j++){
				if(j == i){
					attron(COLOR_PAIR(2));
					mvscanw(coords[j].y, coords[j].x, "%d", &num);
					attroff(COLOR_PAIR(2));
					array[j].value = newarr[j] = num;
					printbox(coords[j].x-array[j].length/2, coords[j].y-array[j].length/2, array[j]);
				}
				else
					printbox(coords[j].x-array[j].length/2, coords[j].y-array[j].length/2, array[j]);
			}
		}		
	}
	else
		for(i = 0 ; i < 8 ; i++)
			newarr[i] = array[i].value;
}
/*Function to display the common menu in between steps of sorting*/
void print_intermediate_menu(int no){
	int i;
	char menu[4][20] = { "Next Step-->", "SKIP TO END", "<--Previous Step" };
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	for( i = 0 ; i < 4 ; i++){
		move(coords[0].y + AIR + i + 1, 30);
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
/*Function to get choice for the intermediate menu*/
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
/*Function to print the animation speed box*/
void Print_Animation(int value) {
	boxx b = { 3, value, 5};
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(A_BLINK | COLOR_PAIR(1));
	mvprintw(coords[0].y - AIR - 7, 20, "Use up-down keys to increase or decrease speed: ");
	mvprintw(coords[0].y - AIR - 5, 20, "ANIMATION SPEED: ");
	printbox(40, coords[0].y-AIR -6, b);
	attroff(COLOR_PAIR(1));
	refresh();
}
/*Function to diplay sort heading*/
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
	else if(s == BUBBLE)
		mvprintw(heady + 2, maxcols/2-6, "BUBBLE SORTING");
	else if(s == MERGE)
		mvprintw(heady + 2, maxcols/2-6, "MERGE SORTING");
	else
		mvprintw(heady + 2, maxcols/2-6, "SELECTION SORTING");
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
			default :
				clear();
		}
		getch();
	}
	endwin();
	return 0;
}
