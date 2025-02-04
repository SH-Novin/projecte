#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct room{
    int row;
    int column;
    int length;
    int width;
};

void map(){
    char map[24][80];

    for(int j = 0; j < 24; j++){
        for(int i = 0; i < 80; i++){
            map[j][i] = ' ';
        }
    }
    
    srand(time(NULL));
    struct room a[8];
    int door;

    for(int i = 0; i < 8; i++){
        int valid = 0;
        while (!valid) {
            a[i].width = (rand() % 4) + 6;
            a[i].length = (rand() % 6) + 6;
            a[i].row = rand() % (24 - a[i].width - 1);
            a[i].column = rand() % (80 - a[i].length - 1);

            valid = 1;
            for (int j = 0; j < i; j++) {
                if (!(a[i].row + a[i].width < a[j].row || a[i].row > a[j].row + a[j].width || 
                      a[i].column + a[i].length < a[j].column || a[i].column > a[j].column + a[j].length)) {
                    valid = 0;
                    break;
                }
            }
        }

        for(int j = a[i].row; j < a[i].row + a[i].width; j++){
            map[j][a[i].column] = '|';
            map[j][a[i].column + a[i].length - 1] = '|';
        }

        for(int j = a[i].column; j < a[i].column + a[i].length; j++){
            map[a[i].row][j] = '_';
            map[a[i].row + a[i].width - 1][j] = '_';
        }

        door = rand() % (a[i].length - 2) + a[i].column + 1;
        map[a[i].row + a[i].width - 1][door] = '+';

        for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
            for(int j = a[i].column + 1; j < a[i].column + a[i].length - 1; j++){
                map[k][j] = '.';
            }
        }
    }
    
    for(int j = 0; j < 24; j++){
        for(int i = 0; i < 80; i++){
            printw("%c", map[j][i]);
        }
        printw("\n");
    }
    refresh();
    getch();
}

int main(){
    initscr();
    raw();
    clear();
    noecho();
    map();
}