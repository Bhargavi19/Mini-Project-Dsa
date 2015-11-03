#include<ncurses.h>
#include"project.h"
#include"graphics_funcs.h"
int s_speed;
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
	napms(2000);
}
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
void s_sort(int l){
	int i, small, pos, j;
	initialisearr(2,3);
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
void Selection_Sort(){
	int small, pos, i, j, menuitem = 0;
	s_speed = 1;
	clear();
	//Print_SORT(SELECTION);
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
}
