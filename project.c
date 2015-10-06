#include<stdio.h>
#include<graphics.h>
int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	int i=0,x=10,y,c;
	char str[3]="0";
	setbkcolor(BROWN);
	setcolor(12); 
	rectangle(22,50,600,425);
	rectangle(23,51,601,426);
	setcolor(YELLOW);
	while(i!=100){
		x=random()%450;
		y=random()%450;
		c=random()%13;
		putpixel(x,y,c);
		i++;
	}
	delay(1000);
	outtextxy(100,140,"WELCOME TO SORTING");
	outtextxy(130,160,"1.MERGE SORT");
	outtextxy(130,180,"Enter your Choice");
	getch();
	closegraph();
	return 0;
}
