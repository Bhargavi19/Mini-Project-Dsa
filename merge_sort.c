#include<ncurses.h>
#include"project.h"
#include"graphics_funcs.h"
void Print_M(int size, int pos1, int pos2){
	int i, space = 0;
	int start = maxcols/2 - 60;
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	for(i = 0 ; i < 8 ; i++){
		if(i){
		if(i%size==0)
		space += 10;
		}
		if(i == pos1){
			attron(COLOR_PAIR(1));
			printbox(start + i*15 + space, maxrows/2, array[i]);
			attroff(COLOR_PAIR(1));
		}
		else if(i == pos2){
			attron(COLOR_PAIR(2));
                        printbox(start + i*15 + space, maxrows/2, array[i]);
                        attroff(COLOR_PAIR(2));
		}
		else
		printbox(start + i*15 + space, maxrows/2, array[i]);
	}
	refresh();	
	napms(2000);
}
void Print_Aux(boxx a[], int t, int size){
	int i, space = 0;
	 int start = maxcols/2 - 60;
	for(i = 0 ; i <= t ; i++){
		if(i){
                if(i%size==0)
                space += 10;
                }
		 //attron(COLOR_PAIR(2));
                 printbox(start + i*15 + space, maxrows/2 + 10, a[i]);
                 //attroff(COLOR_PAIR(2));
	}
	refresh();
}
void Merge_Sort() {
	clear();
	//Print_M(2);
	boxx aux[8];
	int i, j, k, l1, l2, u1, u2, size, n = 8;
	size = 1;
	while(size < 8){
		clear();
		l1 = 0;
		k = 0;
		while(l1+size < n){
			Print_M(size*2,-1,-1);
			l2 = l1+size;
			u1 = l2-1;
			u2 = (l2+size-1 < n) ? l2+size-1 : n-1;
			for( i = l1, j = l2; i <= u1 && j <= u2; k++){
				Print_M(size*2, i, j);
				if(array[i].value <= array[j].value){
					aux[k] = array[i++];
					}
				else{
					aux[k] = array[j++];
				}
				Print_Aux(aux, k, size*2);
			}
			//b = k;
			for(;i <= u1 ; k++){
				aux[k] = array[i++];
				Print_Aux(aux, k, size*2);
				}
			for(;j <= u2 ; k++){
				aux[k] = array[j++];
				Print_Aux(aux, k, size*2);
			}
			l1 = u2+1;
		}
		for(i = l1 ; k < n ; i++){
			aux[k++] = array[i];
			 Print_Aux(aux, k, size*2);
		}
		for(i = 0 ; i < n ;i++)
			array[i] = aux[i];
		size *= 2;
	}
	clear();
	printarray();
}
