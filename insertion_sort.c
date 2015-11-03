#include<ncurses.h>
#include"graphics_funcs.h"
#include"project.h"
int i_speed;
void I_Get_Speed(){
        int ch;
        Print_Animation(i_speed);
        keypad(stdscr, TRUE);
        noecho();
        do {
                Print_SORT(INSERTION);
		ch = getch();
                switch(ch){
                        case KEY_DOWN :
                                i_speed--;
                                if(i_speed < 1) i_speed = 1;
                                break;

                        case KEY_UP :
                                i_speed++;
                                if(i_speed > 20) i_speed = 20;
                                break;
                }
                Print_Animation(i_speed);
        }while(ch != '\n');
        echo();
}
void i_sort(int l){
	int i, j, y;
	initialisearr(2, 3);
	for(i = 1; i < 8 ; i++){
		if(l == i)
		break;
                y = array[i].value;
                for(j = i-1 ; j >= 0 && y < array[j].value ; j--){
                        array[j+1] = array[j];
                }
                array[j+1].value = y;
        }
}
void Insertion_Sort(){
	clear();
	//Print_SORT(INSERTION);
	I_Get_Speed();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	int i, y, j, menuitem = 0;
	for(i = 1; i < 8 ; i++){
		moveupforswap(coords[i].y, coords[i].y - AIR, i, -1, array[i], i_speed);
		y = array[i].value;
		for(j = i-1 ; j >= 0 && y < array[j].value ; j--){
			moverightforswap(j, j+1, array[j], coords[j].y-array[j].length/2, i_speed);
			array[j+1] = array[j];
		}
		array[j+1].value = y;
		moveleftforswap(i, j+1, array[j+1], -1, i_speed);
		movedownforswap(coords[i].y - AIR, coords[i].y, j+1, -1, array[j+1], i_speed);
		menuitem = Get_Intermediate_Choice();
                if(menuitem == 0)
                        continue;
                else if(menuitem == 1)
                        break;
                else if(menuitem == 2){
                        i_sort(i);
                        i--;
                }
		//clear_area();
	}
	i_sort(-2);
	attron(COLOR_PAIR(1));
	printarray();
	attroff(COLOR_PAIR(1));
}
