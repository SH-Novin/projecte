#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


struct room{
    int row;
    int column;
    int lenght;
    int width;
    int door_row;
    int door_column;
    int door_left_row;
    int door_left_column;
    int door_right_row;
    int door_right_column;
};

void map(){
    
    curs_set(0);
    refresh();
    char map[24][80];

    for(int j = 0; j < 24; j++){
        for(int i = 0; i < 80; i++){
            map[j][i] = ' ';
        }
    }
    
    srand(time(NULL));
    int count_door = 0;
    struct room a[8];
    int door;

    for(int i = 0; i < 8; i++){
        if(i == 0){
            a[i].width = ((rand() % 4) + 6);
            a[i].lenght = ((rand() % 6 )+ 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = rand() % (16 - a[i].lenght);
            
            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 1){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = (rand() % (18 - a[i].lenght) + 20);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 2){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = (rand() % (18 - a[i].lenght) + 40);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;
            
            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 3){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = (rand() % (18 - a[i].lenght) + 60);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 4){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = rand() % (18 - a[i].lenght);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 5){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = (rand() % (18 - a[i].lenght) + 20);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;
            
            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 6){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = (rand() % (18 - a[i].lenght) + 40);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;
            
            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
        else if(i == 7){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = (rand() % (18 - a[i].lenght) + 60);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row][j] = '-';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[a[i].row + a[i].width - 1][j] = '-';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[k][j] = '.';
                }
            }
        }
    }




    for(int j = 0; j < 1; j++){
        if(a[0].door_column == a[4].door_column){
            for(int i = a[0].door_row + 1; i < a[4].door_row; i++)
                map[i][a[0].door_column] = '#';
        }
        else if(a[0].door_column > a[4].door_column){
            for(int i = a[0].door_row + 1; i <= ((a[4].door_row + a[0].door_row) / 2); i++)
                map[i][a[0].door_column] = '#';
            for(int i = a[4].door_column; i < a[0].door_column; i++)
                map[((a[4].door_row + a[0].door_row) / 2)][i] = '#';
            for(int i = ((a[4].door_row + a[0].door_row) / 2); i < a[4].door_row; i++)
                map[i][a[4].door_column] = '#';
        }
        else{
            for(int i = a[0].door_row + 1; i <= ((a[4].door_row + a[0].door_row) / 2); i++)
                map[i][a[0].door_column] = '#';
            for(int i = a[0].door_column; i < a[4].door_column; i++)
                map[((a[0].door_row + a[4].door_row) / 2)][i] = '#';
            for(int i = ((a[4].door_row + a[0].door_row) / 2); i < a[4].door_row; i++)
                map[i][a[4].door_column] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[1].door_column == a[5].door_column){
            for(int i = a[1].door_row + 1; i < a[5].door_row; i++)
                map[i][a[1].door_column] = '#';
        }
        else if(a[1].door_column > a[5].door_column){
            for(int i = a[1].door_row + 1; i <= ((a[5].door_row + a[1].door_row) / 2); i++)
                map[i][a[1].door_column] = '#';
            for(int i = a[5].door_column; i < a[1].door_column; i++)
                map[((a[5].door_row + a[1].door_row) / 2)][i] = '#';
            for(int i = ((a[5].door_row + a[1].door_row) / 2); i < a[5].door_row; i++)
                map[i][a[5].door_column] = '#';
        }
        else{
            for(int i = a[1].door_row + 1; i <= ((a[5].door_row + a[1].door_row) / 2); i++)
                map[i][a[1].door_column] = '#';
            for(int i = a[1].door_column; i < a[5].door_column; i++)
                map[((a[1].door_row + a[5].door_row) / 2)][i] = '#';
            for(int i = ((a[5].door_row + a[1].door_row) / 2); i < a[5].door_row; i++)
                map[i][a[5].door_column] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[2].door_column == a[6].door_column){
            for(int i = a[2].door_row + 1; i < a[6].door_row; i++)
                map[i][a[2].door_column] = '#';
        }
        else if(a[2].door_column > a[6].door_column){
            for(int i = a[2].door_row + 1; i <= ((a[6].door_row + a[2].door_row) / 2); i++)
                map[i][a[2].door_column] = '#';
            for(int i = a[6].door_column; i < a[2].door_column; i++)
                map[((a[6].door_row + a[2].door_row) / 2)][i] = '#';
            for(int i = ((a[6].door_row + a[2].door_row) / 2); i < a[6].door_row; i++)
                map[i][a[6].door_column] = '#';
        }
        else{
            for(int i = a[2].door_row + 1; i <= ((a[6].door_row + a[2].door_row) / 2); i++)
                map[i][a[2].door_column] = '#';
            for(int i = a[2].door_column; i < a[6].door_column; i++)
                map[((a[2].door_row + a[6].door_row) / 2)][i] = '#';
            for(int i = ((a[6].door_row + a[2].door_row) / 2); i < a[6].door_row; i++)
                map[i][a[6].door_column] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[3].door_column == a[7].door_column){
            for(int i = a[3].door_row + 1; i < a[7].door_row; i++)
                map[i][a[3].door_column] = '#';
        }
        else if(a[3].door_column > a[7].door_column){
            for(int i = a[3].door_row + 1; i <= ((a[7].door_row + a[3].door_row) / 2); i++)
                map[i][a[3].door_column] = '#';
            for(int i = a[7].door_column; i < a[3].door_column; i++)
                map[((a[7].door_row + a[3].door_row) / 2)][i] = '#';
            for(int i = ((a[7].door_row + a[3].door_row) / 2); i < a[7].door_row; i++)
                map[i][a[7].door_column] = '#';
        }
        else{
            for(int i = a[3].door_row + 1; i <= ((a[7].door_row + a[3].door_row) / 2); i++)
                map[i][a[3].door_column] = '#';
            for(int i = a[3].door_column; i < a[7].door_column; i++)
                map[((a[3].door_row + a[7].door_row) / 2)][i] = '#';
            for(int i = ((a[7].door_row + a[3].door_row) / 2); i < a[7].door_row; i++)
                map[i][a[7].door_column] = '#';
        }
    }




    
    for(int j = 0; j < 1; j++){
        if(a[0].door_right_row == a[1].door_left_row){
            for(int i = a[0].door_right_column + 1; i < a[1].door_left_column; i++){
                map[a[0].door_right_row][i] = '#';
            }
        }
        else if(a[0].door_right_row < a[1].door_left_row){
            for(int i = a[0].door_right_column + 1; i <= ((a[0].door_right_column + a[1].door_left_column) / 2); i++)
                map[a[0].door_right_row][i] = '#';
            for(int i = a[0].door_right_row; i <= a[1].door_left_row; i++)
                map[i][((a[0].door_right_column + a[1].door_left_column) / 2)] = '#';
            for(int i = ((a[0].door_right_column + a[1].door_left_column) / 2); i < a[1].door_left_column; i++)
                map[a[1].door_left_row][i] = '#';
        }
        else if(a[0].door_right_row > a[1].door_left_row){
            for(int i = a[0].door_right_column + 1; i <= ((a[0].door_right_column + a[1].door_left_column) / 2); i++)
                map[a[0].door_right_row][i] = '#';
            for(int i = a[1].door_left_row; i <= a[0].door_right_row; i++)
                map[i][((a[0].door_right_column + a[1].door_left_column) / 2)] = '#';
            for(int i = ((a[0].door_right_column + a[1].door_left_column) / 2); i < a[1].door_left_column; i++)
                map[a[1].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[1].door_right_row == a[2].door_left_row){
            for(int i = a[1].door_right_column + 1; i < a[2].door_left_column; i++){
                map[a[1].door_right_row][i] = '#';
            }
        }
        else if(a[1].door_right_row < a[2].door_left_row){
            for(int i = a[1].door_right_column + 1; i <= ((a[1].door_right_column + a[2].door_left_column) / 2); i++)
                map[a[1].door_right_row][i] = '#';
            for(int i = a[1].door_right_row; i <= a[2].door_left_row; i++)
                map[i][((a[1].door_right_column + a[2].door_left_column) / 2)] = '#';
            for(int i = ((a[1].door_right_column + a[2].door_left_column) / 2); i < a[2].door_left_column; i++)
                map[a[2].door_left_row][i] = '#';
        }
        else{
            for(int i = a[1].door_right_column + 1; i <= ((a[1].door_right_column + a[2].door_left_column) / 2); i++)
                map[a[1].door_right_row][i] = '#';
            for(int i = a[2].door_left_row; i <= a[1].door_right_row; i++)
                map[i][((a[1].door_right_column + a[2].door_left_column) / 2)] = '#';
            for(int i = ((a[1].door_right_column + a[2].door_left_column) / 2); i < a[2].door_left_column; i++)
                map[a[2].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[2].door_right_row == a[3].door_left_row){
            for(int i = a[2].door_right_column + 1; i < a[3].door_left_column; i++){
                map[a[2].door_right_row][i] = '#';
            }
        }
        else if(a[2].door_right_row < a[3].door_left_row){
            for(int i = a[2].door_right_column + 1; i <= ((a[2].door_right_column + a[3].door_left_column) / 2); i++)
                map[a[2].door_right_row][i] = '#';
            for(int i = a[2].door_right_row; i <= a[3].door_left_row; i++)
                map[i][((a[2].door_right_column + a[3].door_left_column) / 2)] = '#';
            for(int i = ((a[2].door_right_column + a[3].door_left_column) / 2); i < a[3].door_left_column; i++)
                map[a[3].door_left_row][i] = '#';
        }
        else{
            for(int i = a[2].door_right_column + 1; i <= ((a[2].door_right_column + a[3].door_left_column) / 2); i++)
                map[a[2].door_right_row][i] = '#';
            for(int i = a[3].door_left_row; i <= a[2].door_right_row; i++)
                map[i][((a[2].door_right_column + a[3].door_left_column) / 2)] = '#';
            for(int i = ((a[2].door_right_column + a[3].door_left_column) / 2); i < a[3].door_left_column; i++)
                map[a[3].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[4].door_right_row == a[5].door_left_row){
            for(int i = a[4].door_right_column + 1; i < a[5].door_left_column; i++){
                map[a[4].door_right_row][i] = '#';
            }
        }
        else if(a[4].door_right_row < a[5].door_left_row){
            for(int i = a[4].door_right_column + 1; i <= ((a[4].door_right_column + a[5].door_left_column) / 2); i++)
                map[a[4].door_right_row][i] = '#';
            for(int i = a[4].door_right_row; i <= a[5].door_left_row; i++)
                map[i][((a[4].door_right_column + a[5].door_left_column) / 2)] = '#';
            for(int i = ((a[4].door_right_column + a[5].door_left_column) / 2); i < a[5].door_left_column; i++)
                map[a[5].door_left_row][i] = '#';
        }
        else{
            for(int i = a[4].door_right_column + 1; i <= ((a[4].door_right_column + a[5].door_left_column) / 2); i++)
                map[a[4].door_right_row][i] = '#';
            for(int i = a[5].door_left_row; i <= a[4].door_right_row; i++)
                map[i][((a[4].door_right_column + a[5].door_left_column) / 2)] = '#';
            for(int i = ((a[4].door_right_column + a[5].door_left_column) / 2); i < a[5].door_left_column; i++)
                map[a[5].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[5].door_right_row == a[6].door_left_row){
            for(int i = a[5].door_right_column + 1; i < a[6].door_left_column; i++){
                map[a[5].door_right_row][i] = '#';
            }
        }
        else if(a[5].door_right_row < a[6].door_left_row){
            for(int i = a[5].door_right_column + 1; i <= ((a[5].door_right_column + a[6].door_left_column) / 2); i++)
                map[a[5].door_right_row][i] = '#';
            for(int i = a[5].door_right_row; i <= a[6].door_left_row; i++)
                map[i][((a[5].door_right_column + a[6].door_left_column) / 2)] = '#';
            for(int i = ((a[5].door_right_column + a[6].door_left_column) / 2); i < a[6].door_left_column; i++)
                map[a[6].door_left_row][i] = '#';
        }
        else{
            for(int i = a[5].door_right_column + 1; i <= ((a[5].door_right_column + a[6].door_left_column) / 2); i++)
                map[a[5].door_right_row][i] = '#';
            for(int i = a[6].door_left_row; i <= a[5].door_right_row; i++)
                map[i][((a[5].door_right_column + a[6].door_left_column) / 2)] = '#';
            for(int i = ((a[5].door_right_column + a[6].door_left_column) / 2); i < a[6].door_left_column; i++)
                map[a[6].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[6].door_right_row == a[7].door_left_row){
            for(int i = a[6].door_right_column + 1; i < a[7].door_left_column; i++){
                map[a[6].door_right_row][i] = '#';
            }
        }
        else if(a[6].door_right_row < a[7].door_left_row){
            for(int i = a[6].door_right_column + 1; i <= ((a[6].door_right_column + a[7].door_left_column) / 2); i++)
                map[a[6].door_right_row][i] = '#';
            for(int i = a[6].door_right_row; i <= a[7].door_left_row; i++)
                map[i][((a[6].door_right_column + a[7].door_left_column) / 2)] = '#';
            for(int i = ((a[6].door_right_column + a[7].door_left_column) / 2); i < a[7].door_left_column; i++)
                map[a[7].door_left_row][i] = '#';
        }
        else{
            for(int i = a[6].door_right_column + 1; i <= ((a[6].door_right_column + a[7].door_left_column) / 2); i++)
                map[a[6].door_right_row][i] = '#';
            for(int i = a[7].door_left_row; i <= a[6].door_right_row; i++)
                map[i][((a[6].door_right_column + a[7].door_left_column) / 2)] = '#';
            for(int i = ((a[6].door_right_column + a[7].door_left_column) / 2); i < a[7].door_left_column; i++)
                map[a[7].door_left_row][i] = '#';
        }
    }
    
    map[a[0].row + 2][a[0].column + 2] = '$';

    refresh();
    for(int j = 0; j < 24; j++){
        for(int i = 0; i < 80; i++){
            move(j, i);
            printw("%c", map[j][i]);
        }
    }
    refresh();
}

move_map(){

}

int main(){
    initscr();
    raw();
    clear();
    noecho();
    map();
    
    refresh();

}
