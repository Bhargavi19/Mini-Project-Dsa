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
int s_speed;
/*Function to print array with boxes at passed locations in different colors*/
void printarray_forselection(int pos1, int pos2){
	int i;
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	for(i = 0 ; i < 8 ; i++){
		if(i == pos1){
			attron(COLOR_PAIR(1));
			array[pos1].color = COLOR_RED;
			printbox(coords[i].x-array[i].length/2, coords[i].y-array[i].length/2, array[i]);
			array[pos1].color = COLOR_YELLOW;
			attroff(COLOR_PAIR(1));
		}
		else if(i == pos2){
			attron(COLOR_PAIR(2));
			array[pos2].color = COLOR_GREEN;
			printbox(coords[i].x-array[i].length/2, coords[i].y-array[i].length/2, array[i]);
			array[pos2].color = COLOR_YELLOW;
			attroff(COLOR_PAIR(2));
		}
		else
			printbox(coords[i].x-array[i].length/2, coords[i].y-array[i].length/2, array[i]);
		refresh();
	}
	napms(2000/s_speed * 2);
}
/*Function to get speed of selection sort*/
void s_Get_Speed(){
	int ch;

	Print_Animation(s_speed);
	keypad(stdscr, TRUE);
	noecho();
	do {
		Print_SORT(SELECTION);
		ch = getch();
		switch(ch){
			case KEY_DOWN :
				s_speed--;
				if(s_speed < 1) s_speed = 1;
				break;

			case KEY_UP :
				s_speed++;
				if(s_speed > 20) s_speed = 20;
				break;
		}
		Print_Animation(s_speed);
	}while(ch != '\n');
	echo();
}
/*Function to sort the array upto the passed sorting step*/
void s_sort(int l){
	int i, small, pos, j;
	init();
	for(i = 0 ; i < 8 ; i++)
	{
		if(i == l)
			break;
		small = array[i].value;
		pos = i;
		for(j = i+1 ; j < 8 ; j++){
			if(array[j].value < small){
				small = array[j].value;
				pos = j;
			}
		}
		array[pos].value = array[i].value;
		array[i].value = small;
	}
}
/*Function to sort array using selection sort and display*/
void Selection_Sort(){
	Input_Array();
	int small, pos, i, j, menuitem = 0;
	s_speed = 1;
	clear();
	Print_SORT(SELECTION);
	s_Get_Speed();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	for(i = 0 ; i < 8 ; i++)
	{
		small = array[i].value;
		pos = i;
		for(j = i+1 ; j < 8 ; j++){
			printarray_forselection(i, j);
			if(array[j].value < small){
				small = array[j].value;
				pos = j;
			}
		}
		printarray_forselection(i, pos);
		swapboxes(i, pos, s_speed);
		array[pos].value = array[i].value;	
		array[i].value = small;
		attron(COLOR_PAIR(1));
		printarray();
		attron(COLOR_PAIR(2));
		menuitem = Get_Intermediate_Choice();
		if(menuitem == 0)
			continue;
		else if(menuitem == 1)
			break;
		else if(menuitem == 2){
			s_sort(i);
			i--;
		}
	}
	s_sort(-1);
	printarray();
	clear_intmenu();
}
