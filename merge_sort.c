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
#include"project.h"
#include"graphics_funcs.h"
int m_speed;
/*Function to initialise coordinates for each step of merge sort*/
void initialise(point x[], int s){
	int i;
	for(i = 0 ; i < 8 ; i++){
		if(s == 1){
			x[i].y = maxrows/4  ;
			x[i].x = (i+1)*15 ;
		}
		else if(s == 2){
			x[i].y = maxrows/4 + 5 ;
			if(i % 2 == 0)
				x[i].x = (i+1)*15 + 5;
			else
				x[i].x = (i+1)*15 - 5;
		}
		else if(s == 4){
			x[i].y = maxrows/4 + 10 ;
			if(i < 4){
				x[i].x = (i+1)*5 + 30;
			}
			else{
				x[i].x = (i+1)*5 + 60;
			}
		}
		else{
			x[i].y = maxrows/4 + 15 ;
			x[i].x = (i+1)*5 + 40;
		}
	} 
}
/*Function to print the array*/
void Print(point x[], boxx y[], int n, int pos1, int pos2){
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	int i;
	for(i = 0 ; i < n ; i++){
		if(i == pos1){
			attron(COLOR_PAIR(1));
			printbox(x[i].x, x[i].y, y[i]);
			attroff(COLOR_PAIR(1));
		}
		else if(i == pos2){
			attron(COLOR_PAIR(2));
			printbox(x[i].x, x[i].y, y[i]);
			attroff(COLOR_PAIR(2));
		}
		else
			printbox(x[i].x, x[i].y, y[i]);
	}
	refresh();
	napms(2000/m_speed);
}
/*Function which prints dashes*/
void Print_dash(int size){
	int y, i;
	if(size == 1)
		y = maxrows/4 + 3;
	else if(size == 2)
		y = maxrows/4 + 8;
	else if(size == 4)
		y = maxrows/4 + 13;
	for(i = 10 ; i < 120 ; i++) 
		mvaddch(y, i, '-'); 
}
/*Function to print menu intermediate to each step*/
void m_print_intermediate_menu(int no){
	int i;
	char menu[2][20] = { "Next Step-->", "SKIP TO END"};
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	for( i = 0 ; i < 2  ; i++){
		move(maxrows - 10 + i, 30);
		clrtoeol();
	}
	attron(COLOR_PAIR(1));
	for(i = 0 ; i < 2 ; i++){
		if(i == no){
			attron(A_REVERSE);
			mvprintw(maxrows-10 + i,  30, menu[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(maxrows-10 + i, 30, menu[i]);
	}
	attroff(COLOR_PAIR(1));
	refresh();
}
/*Function which gets choice of user in between each step of sorting*/
int m_Get_Intermediate_Choice(){
	int ch, menuitem = 0;
	m_print_intermediate_menu(menuitem);
	do
	{
		ch = getch();
		switch(ch){
			case KEY_UP :
				menuitem--;
				if(menuitem < 0) menuitem = 1;
				break;

			case KEY_DOWN :
				menuitem++;
				if(menuitem > 1) menuitem = 0;
				break;
			default:
				break;
		}
		m_print_intermediate_menu(menuitem);
	}while(ch != '\n');
	return menuitem;
}
/*Function to get speed of merge sort*/
void m_Get_Speed(){
	int ch;
	Print_Animation(m_speed);
	keypad(stdscr, TRUE);
	noecho();
	do {
		Print_SORT(MERGE);
		ch = getch();
		switch(ch){
			case KEY_DOWN :
				m_speed--;
				if(m_speed < 1) m_speed = 1;
				break;

			case KEY_UP :
				m_speed++;
				if(m_speed > 10) m_speed = 10;
				break;
		}
		Print_Animation(m_speed);
	}while(ch != '\n');
	echo();
}
/*Function to merge sort the array upto a particular step of sorting*/
void m_sort(int v){
	init();
	boxx aux[8];
	int i, j, k, u1, l1, u2, l2, size = 1, n = 8;
	while(size < 8){
		l1 = 0;
		k = 0;
		while(l1+size < n){
			l2 = l1+size;
			u1 = l2-1;
			u2 = (l2+size-1 < n) ? l2+size-1 : n-1;
			for( i = l1, j = l2; i <= u1 && j <= u2; k++){
				if(array[i].value <= array[j].value){
					aux[k] = array[i++];
				}
				else{
					aux[k] = array[j++];
				}
			}
			for(;i <= u1 ; k++){
				aux[k] = array[i++];
			}
			for(;j <= u2 ; k++){
				aux[k] = array[j++];
			}
			l1 = u2+1;
		}
		for(i = l1 ; k < n ; i++){
			aux[k++] = array[i];
		}
		for(i = 0 ; i < n ;i++)
			array[i] = aux[i];
		if(size == v)
			break;
		size *= 2;
	}
}
void Print_END(){
	int i;
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
	for(i = 0 ; i < 3 ; i++){
		move(maxrows - 10 + i, 30);
		clrtoeol(); 
	} 
	attron(A_REVERSE | COLOR_PAIR(1));
        mvprintw(coords[0].y + AIR , 50, "BACK TO MAIN MENU");
        attroff(A_REVERSE | COLOR_PAIR(1));
}
/*Function to merge sort the array and display it*/
void Merge_Sort() {
	Input_Array();
	m_speed = 1;
	clear();
	Print_SORT(MERGE);
	m_Get_Speed();
	boxx aux[8];
	point auxcoords[8];
	int i, j, k, l1, l2, u1, u2, size, n = 8, menuitem;
	size = 1;
	initialise(coords, size);
	Print(coords, array, 8, -1, -1);
	while(size < 8){
		l1 = 0;
		k = 0;
		while(l1+size < n){
			initialise(coords, size);
			initialise(auxcoords, size*2);
			l2 = l1+size;
			u1 = l2-1;
			u2 = (l2+size-1 < n) ? l2+size-1 : n-1;
			for( i = l1, j = l2; i <= u1 && j <= u2; k++){
				Print(auxcoords, aux, k, -1, -1);
				Print_dash(size);
				Print(coords, array, 8, i, j);
				if(array[i].value <= array[j].value){
					aux[k] = array[i++];
				}
				else{
					aux[k] = array[j++];
				}
				Print(auxcoords, aux, k, -1, -1);
			}
			for(;i <= u1 ; k++){
				aux[k] = array[i++];
				Print(auxcoords, aux, k, -1, -1);
			}
			for(;j <= u2 ; k++){
				aux[k] = array[j++];
				Print(auxcoords, aux, k, -1, -1);
			}
			l1 = u2+1;
		}
		for(i = l1 ; k < n ; i++){
			aux[k++] = array[i];
			Print(auxcoords, aux, k, -1, -1);
		}
		Print(coords, array, 8, -1, -1);
		Print(auxcoords, aux, 8, -1, -1);
		Print_dash(size*2);
		for(i = 0 ; i < n ;i++)
			array[i] = aux[i];
		menuitem = m_Get_Intermediate_Choice();
		if(menuitem == 0);
		else if(menuitem == 1)
			break;
		size *= 2;
	}
	while(size < 8){
		size *= 2;
		m_sort(size/2);
		initialise(coords, size);
		Print(coords, array, 8, -1, -1);
		Print_dash(size);
	}
	Print_END();
}
