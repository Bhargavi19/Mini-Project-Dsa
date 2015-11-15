#ifndef GRAPHICS_H
#define GRAPHICS_H
#define AIR 10
typedef struct boxx {
        int length, value, color;
} boxx;
typedef struct point{
        int x, y;
}point;
int maxrows, maxcols;
boxx array[8];
point coords[8];
void initialisearr(int l, int c);
void initialisecoords();
void printbox(int ux, int uy, boxx b);
void printarray();
void movedown(int starty, int endy, int x, boxx b, int speed);
void movedownforswap(int starty, int endy, int pos1, int pos2, boxx b, int speed);
void moveupforswap(int starty, int endy, int pos1, int pos2, boxx b, int speed);
void moverightforswap(int pos1, int pos2, boxx b, int yy, int speed);
void moveleftforswap(int pos1, int pos2, boxx b, int yy, int speed);
void moveup(int starty, int endy, int x, boxx b, int speed);
void moveright(int startx, int endx, int y, boxx b, int speed);
void swapboxes(int b1pos, int b2pos, int speed) ;
void moveleft(int startx, int endx, int y, boxx b, int speed);
void Draw_Fill(int sx, int sy, int h, int v, int color);
#endif
