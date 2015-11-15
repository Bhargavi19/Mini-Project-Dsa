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
#include"graphics_funcs.h"
/*Function to initialise "array" */
void initialisearr(int l, int c){
	int a[] = {4, 7, 5, 8, 1, 3, 2, 6};
	int i;
	for(i = 0 ; i < 8 ; i++){
		array[i].length = l;
		array[i].color = c;
		array[i].value = a[i];		
	}
}
/*Function to initialize coordinates of each box*/
void initialisecoords(){
	int i,u;
	u = (maxcols-10)/8;
	for(i = 0 ; i < 8 ; i++){
		coords[i].x = 10+i*u;
		coords[i].y = maxrows/2;
	}
}
/*Function to clear area around the boxes where sorting takes place*/
void clear_area(){
	int i;
	for(i = coords[0].y - AIR -1; i <= coords[0].y + AIR + 1; i++){
		move(i, 0);
		clrtoeol();
	}
}
/*Function to print the desired box at a desired location*/
void printbox(int ux, int uy, boxx b){
	mvvline(uy, ux, 0, b.length);
	mvvline(uy, ux+b.length, 0, b.length);
	mvhline(uy, ux, 0, b.length);
	mvhline(uy+b.length, ux, 0, b.length);
	mvaddch(uy, ux, ACS_ULCORNER);
	mvaddch(uy, ux+b.length, ACS_URCORNER);
	mvaddch(uy+b.length, ux, ACS_LLCORNER);
	mvaddch(uy+b.length, ux+b.length, ACS_LRCORNER);
	if(b.value == ' ')
		mvaddch(uy+b.length/2, ux+b.length/2, b.value);
	else
		mvprintw(uy+b.length/2, ux+b.length/2, "%d", b.value);
}
/*Function to fill a particular area with color*/
void Draw_Fill(int sx, int sy, int h, int v, int color){
	int i, j;
	boxx b = {1,' ',0};
	init_pair(1, color, color);
	attron(COLOR_PAIR(1));
	for(i = 0; i < h ; i++){
		for(j = 0; j< v ; j++)
			printbox(sx+i, sy + j, b);
	}
	attroff(COLOR_PAIR(1));
}
/*Function to simply print the array of boxes*/
void printarray(){
	int i;
	for(i = 0 ; i < 8 ; i++){
		printbox(coords[i].x-array[i].length/2, coords[i].y-array[i].length/2, array[i]);
	}
}
/*Function to move a particular box downwards while swapping*/
void movedownforswap(int starty, int endy, int pos1, int pos2, boxx b, int speed){
	int i,j;
	for(i = starty; i <= endy ; i++){
		clear_area();
		for(j = 0 ; j < 8 ; j++){
			if(j == pos1)
				printbox(coords[pos1].x-array[j].length/2, i-array[j].length/2, b);
			else if(j != pos2)
				printbox(coords[j].x-array[j].length/2,coords[j].y-array[j].length/2, array[j]);
		}
		napms(1000/speed);
		refresh();
	}
}
/*Function to move a particular box upwards while swapping*/
void moveupforswap(int starty, int endy, int pos1, int pos2, boxx b, int speed){
	int i,j;
	for(i = starty ; i >= endy ; i--){
		clear_area();
		for(j = 0 ; j < 8 ; j++){
			if(j == pos1)
				printbox(coords[pos1].x-array[j].length/2, i-array[j].length/2, b);
			else if(j != pos2)
				printbox(coords[j].x-array[j].length/2,coords[j].y-array[j].length/2, array[j]);
		}
		napms(1000/speed);
		refresh();
	}
}
/*Function to move a box right while swapping*/
void moverightforswap(int pos1, int pos2, boxx b, int yy, int speed){
	int i, j;
	if(yy == -1)
		yy = coords[pos1].y + AIR - array[pos1].length/2;
	for(i = coords[pos1].x; i <= coords[pos2].x ; i++){
		clear_area();
		for(j = 0 ; j < 8 ; j++){
			if(j == pos1)
				printbox(i-array[j].length/2, yy, b);
			else if(j != pos2)
				printbox(coords[j].x-array[j].length/2, coords[j].y-array[j].length/2, array[j]);
		}
		napms(1000/speed);
		refresh();
	}
}
/*Function to move a box left while swapping*/
void moveleftforswap(int pos1, int pos2, boxx b, int yy, int speed){
	int i,j;
	if(yy == -1)
		yy =  coords[pos1].y - AIR - array[pos1].length/2;
	for(i = coords[pos1].x; i >= coords[pos2].x ; i--){
		clear_area();
		for(j = 0 ; j < 8 ; j++){
			if(j == pos1)
				printbox(i-array[pos1].length/2, yy, b);
			else if (j != pos2) 
				printbox(coords[j].x-array[j].length/2, coords[j].y-array[j].length/2, array[j]);
		}
		napms(1000/speed);
		refresh();
	}
}
/*Function to swap 2 boxes at given locations*/
void swapboxes(int b1pos, int b2pos, int speed) {
	movedownforswap(coords[b1pos].y, coords[b1pos].y + AIR , b1pos, -1, array[b1pos], speed);
	moverightforswap(b1pos, b2pos, array[b1pos], -1, speed);
	moveupforswap(coords[b2pos].y + AIR, coords[b2pos].y, b2pos,b1pos , array[b1pos], speed);
	moveupforswap(coords[b2pos].y, coords[b2pos].y - AIR, b2pos, b1pos, array[b2pos], speed);
	moveleftforswap(b2pos, b1pos, array[b2pos], -1, speed);	
	movedownforswap(coords[b1pos].y - AIR, coords[b1pos].y, b1pos, b2pos, array[b2pos], speed);
}
