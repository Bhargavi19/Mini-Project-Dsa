#include<ncurses.h>
#include"project.h"
#include"graphics_funcs.h"
int b_speed;
void b_sort(int n) {
	int i, j;
	boxx temp;
	initialisearr(2,3);
	for(i = 0 ; i < 8 ; i++){
		if(i == n)
			break;
		for(j = 0; j < 8 - i - 1; j++){
			if(array[j].value > array[j+1].value){
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}
void Get_Speed(){
	int ch;
	Print_Animation(b_speed);
	keypad(stdscr, TRUE);
	noecho();
	do {
		Print_SORT(BUBBLE);
		ch = getch();
		switch(ch){
			case KEY_DOWN :
				b_speed--;
				if(b_speed < 1) b_speed = 1;
				break;

			case KEY_UP :
				b_speed++;
				if(b_speed > 20) b_speed = 20;
				break;
		}
		Print_Animation(b_speed);
	}while(ch != '\n');
	echo();
}
void Bubble_Sort(){
	clear();
	int menuitem = 0;
	b_speed = 1;
	//Print_SORT(BUBBLE);
	Get_Speed();
	int i, j; 
	boxx temp;
	//init_pair(1, COLOR_CYAN, COLOR_BLACK);
	for(i = 0 ; i < 8 ; i++){
		for(j = 0; j < 8 - i - 1; j++){
			if(array[j].value > array[j+1].value){
				swapboxes(j, j+1, b_speed);
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				printarray();
			}
		}
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
                attron(COLOR_PAIR(1));
		printarray();  
		attroff(COLOR_PAIR(1));
		menuitem = Get_Intermediate_Choice();
		if(menuitem == 0)
			continue;
		else if(menuitem == 1)
			break;
		else if(menuitem == 2){
			b_sort(i);
			i--;
		}
	}
	b_sort(-1);
	printarray();
}
