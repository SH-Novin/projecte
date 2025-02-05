#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include<locale.h>

int floor = 0;
char select_gun = 'm';
int number_dagger = 0, number_arrow = 0, number_wand = 0;
char number_sword[12] = "0";
char map[4][24][80];
char UserName[25], EMail[30], Password[25], RemWord[25];
int character_row, character_column;
int pillar_row, pillar_column;
int flag_corridor_map[4][24][80], map_door[floor][4][24][80];
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
//Define

//Struct

//Functions
void Hello();


int menu_start(){

    keypad(stdscr, TRUE);
    raw();
    curs_set(0);

    int select = 0;
    char *start_items[3] = {"SIGN UP", "LOGIN", "GUEST"};
    WINDOW *menu = newwin(7, 20, 8, 30);
    keypad(menu, TRUE);
    wclear(menu);
    box(menu, 0,  0);
    

    for (int i = 0; i < 3; i++)
    {
        if (i == 0){
            wattron(menu, COLOR_PAIR(1));
            wattron(menu, A_BOLD);
            mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
            wattroff(menu, A_BOLD);
            wattroff(menu, COLOR_PAIR(1));
        }
        
        else if (i == 1)
            mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);

        else if (i == 2)
            mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);

        move(1, 1);          
        clrtoeol();            
        mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
        refresh();
    }

    wrefresh(menu);
    while (1)
    {
        wrefresh(menu);
        int c = wgetch(menu);
        if (c == KEY_UP)
        {
            wrefresh(menu);
            if (select == 0){
                select = 2;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            else{
                --select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 3; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }
                else{
                    if (i == 0)
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);

                    if (i == 1)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);

                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                }
            }
        }

        else if (c == KEY_DOWN){
            if (select == 2){
                select = 0;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }
            else{
                ++select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 3; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }

                else{
                    if (i == 0)
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                    if (i == 1)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                }
            }
        }

        else if (c == '\n'){
            wrefresh(menu);
            delwin(menu);
            return select;
        }
        wrefresh(menu);
    }
}


int username() {
    clear();
    refresh();
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    char *sign_up_items[5] = {"UserName:", "E-Mail:", "Password:", "Word Reminder:", "creat random passowrd (press 'r')"};
    WINDOW *sign = newwin(11, 40, 7, 20);
    keypad(sign, TRUE);
    wclear(sign);
    box(sign, 0, 0);
    int index = 0;
    noecho();
    for (int i = 0; i < 5; i++){

        if (i == 0){
            wattron(sign, COLOR_PAIR(2));
            wattron(sign, A_BOLD);
            mvwprintw(sign, 1, 2, "%s", sign_up_items[i]);
            wattroff(sign, A_BOLD);
            wattroff(sign, COLOR_PAIR(2));
            wrefresh(sign);
        }
        
        else if (i == 1){
            mvwprintw(sign, 3, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 2){
            mvwprintw(sign, 5, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if(i == 3){
            mvwprintw(sign, 7, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 4){
            mvwprintw(sign, 9, 4, "%s", sign_up_items[i]);
            refresh();
        }
    }
    while(1) {
        wmove(sign, 1, 18 + index);
        int c = mvwgetch(sign, 1, 18 + index);
        if(c == KEY_BACKSPACE)
            if(index > 0) {
                mvwprintw(sign, 1, (18 + index), "%c", ' ');
                --index;
                continue;
            }
            else {
                continue;
            }
        
        
        if(c == '\n'){
            // if(exist){
            //     attron(COLOR_PAIR(3));
            //     mvprintw(1, 1, "%s", "USERNAME CURRENTLY EXISTS !");
            //     napms(850);
            //     attroff(COLOR_PAIR(3));
            //     refresh();
            //     continue;
            // }
            UserName[index] = '\0';

            if(UserName[0] == '\0') {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "USERNAME IS EMPTY !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else {
                //save in file
                return 0;
            }
        }
        else {
            if(index > 11) {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "The maximum USERNAME lenght is 12!");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else {
                UserName[index] = c;
                ++index;
                mvwprintw(sign, 1, (18 + index), "%c", c);
            }
        }
    }
}

int email() {
    int index = 0;
    noecho();
    clear();
    refresh();
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    char *sign_up_items[5] = {"UserName:", "E-Mail:", "Password:", "Word Reminder:", "creat random passowrd (press 'r')"};
    WINDOW *sign = newwin(11, 40, 7, 20);
    keypad(sign, TRUE);
    wclear(sign);
    box(sign, 0, 0);
    for (int i = 0; i < 5; i++){

        if (i == 1){
            wattron(sign, COLOR_PAIR(2));
            wattron(sign, A_BOLD);
            mvwprintw(sign, 3, 2, "%s", sign_up_items[i]);
            wattroff(sign, A_BOLD);
            wattroff(sign, COLOR_PAIR(2));
            wrefresh(sign);
        }
        
        else if (i == 0){
            mvwprintw(sign, 1, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 2){
            mvwprintw(sign, 5, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if(i == 3){
            mvwprintw(sign, 7, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 4){
            mvwprintw(sign, 9, 4, "%s", sign_up_items[i]);
            refresh();
        }
    }

    while(1) {
        wmove(sign, 3, 18 + index);
        int c = mvwgetch(sign, 3, 18 + index);
        if(c == KEY_BACKSPACE){
            if(index > 0) {
                mvwprintw(sign, 3, (18 + index), "%c", ' ');
                --index;
                continue;
            } 
            else {
                continue;
            }
        }
        
        if(c == '\n'){
            EMail[index] = '\0';
            int countats = 0, countdot = 0, banner = 0;
            for(int i = 0; i < strlen(EMail); i++){
                if(EMail[i] == '@')
                    countats = i;
                else if(EMail[i] == '.')
                    countdot = i;
                else if('a' <= EMail[i] && EMail[i] <= 'z')
                    banner = 1;
            }
            
            if(strlen(EMail) < 5) {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "THE LENGHT OF THE MINIMUM ALLOWED E-MAIL IS 5 !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else if((0 >= countats) || (countats >= (countdot - 1)) || (countdot >= (strlen(EMail) - 1)) || (banner == 0)){
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "THE E-MAIL HAS NOT ENTERED THE CORRECT FORMAT !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }          
            else{
                for (int i = 0; i < 5; i++){
                    if (i == 2){
                        wattron(sign, COLOR_PAIR(2));
                        wattron(sign, A_BOLD);
                        mvwprintw(sign, 5, 2, "%s", sign_up_items[i]);
                        wattroff(sign, A_BOLD);
                        wattroff(sign, COLOR_PAIR(2));
                        wrefresh(sign);
                    }        
                    else if (i == 0){
                        mvwprintw(sign, 1, 2, "%s", sign_up_items[i]);
                        refresh();
                    }
                    else if (i == 1){
                        mvwprintw(sign, 3, 2, "%s", sign_up_items[i]);
                        refresh();
                    }
                    else if(i == 3){
                        mvwprintw(sign, 7, 2, "%s", sign_up_items[i]);
                        refresh();
                    }
                    else if (i == 4){
                        mvwprintw(sign, 9, 4, "%s", sign_up_items[i]);
                        refresh();
                    }
                }
                //save in file
                return 0;
            }
        }

        else {
            if(index > 11) {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "The maximum E-MAIL lenght is 14 !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else {
                EMail[index] = c;
                ++index;
                mvwprintw(sign, 3, (18 + index), "%c", c);
            }
        }
    }    
}

int password() {
    clear();
    refresh();
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    char *sign_up_items[5] = {"UserName:", "E-Mail:", "Password:", "Word Reminder:", "creat random passowrd (press 'r')"};
    WINDOW *sign = newwin(11, 40, 7, 20);
    keypad(sign, TRUE);
    wclear(sign);
    box(sign, 0, 0);
    int index = 0;
    noecho();
    for (int i = 0; i < 5; i++){
        if (i == 2){
            wattron(sign, COLOR_PAIR(2));
            wattron(sign, A_BOLD);
            mvwprintw(sign, 5, 2, "%s", sign_up_items[i]);
            wattroff(sign, A_BOLD);
            wattroff(sign, COLOR_PAIR(2));
            wrefresh(sign);
        }        
        else if (i == 0){
            mvwprintw(sign, 1, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 1){
            mvwprintw(sign, 3, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if(i == 3){
            mvwprintw(sign, 7, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 4){
            mvwprintw(sign, 9, 4, "%s", sign_up_items[i]);
            refresh();
        }
    }
    while(1) {
        wmove(sign, 5, 18 + index);
        int c = mvwgetch(sign, 5, 18 + index);
        if(c == KEY_BACKSPACE)
            if(index > 0) {
                mvwprintw(sign, 5, (18 + index), "%c", ' ');
                --index;
                continue;
            }
            else {
                continue;
            } 
            
        
        
        if(c == '\n'){
            int uppercase = 0, lowercase = 0, digit = 0;
            Password[index] = '\0';
            for(int i = 0; i < strlen(Password); i++){
                if('A' <= Password[i] && Password[i] <= 'Z')
                    uppercase = 1;
                else if('a' <= Password[i] && Password[i] <= 'z')
                    lowercase = 1;
                else if('0' <= Password[i] && Password[i] <= '9')
                    digit = 1;
            }

            if(strlen(Password) < 7){
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "THE LENGHT OF THE MINIMUM ALLOWED PASSWORD IS 7 !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else if(uppercase == 0){
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "THE PASSWORD REQUIRES AT LEAST ONE UPPERCASE LETTER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else if(lowercase == 0){
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "THE PASSWORD REQUIRES AT LEAST ONE LOWERCASE LETTER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else if(digit == 0){
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "THE PASSWORD REQUIRES AT LEAST ONE DIGIT LETTER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            
            //save in file
            return 0;
        }

        else {
            if(index > 11) {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "The maximum PASSWORD lenght is 12!");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else {
                Password[index] = c;
                ++index;
                mvwprintw(sign, 5, (18 + index), "%c", '*');
            }
        }
    }
}

int rand_password(){
    char upper, lower;
    int digit, randchar;
    srand(time(NULL));
    int lenght = (rand() % 12);
    for(int i = 0; i <= lenght; i++){
        randchar = (rand() % 3);

        if(randchar == 0){
            upper = (rand() % 26);
            Password[i] = ('A' + upper);
            Password[i + 1] = '\0';
        }
        else if(randchar == 1){
            lower = (rand() % 26);
            Password[i] = ('a' + lower);
            Password[i + 1] = '\0';
        }
        if(randchar == 2){
            digit = (rand() % 10);
            Password[i] = ('0' + digit);
            Password[i + 1] = '\0';
        }
    }
    attron(COLOR_PAIR(3));
    mvprintw(1, 1, "Your PASSWORD is : %s", Password);
    refresh();
    napms(8000);
    attroff(COLOR_PAIR(3));
    move(1, 1);
    clrtoeol();
    refresh();
    return 0;
}

int remind(){
    clear();
    refresh();
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    char *sign_up_items[5] = {"UserName:", "E-Mail:", "Password:", "Word Reminder:", "creat random passowrd (press 'r')"};
    WINDOW *sign = newwin(11, 40, 7, 20);
    keypad(sign, TRUE);
    wclear(sign);
    box(sign, 0, 0);
    int index = 0;
    noecho();
    for (int i = 0; i < 5; i++){

        if (i == 3){
            wattron(sign, COLOR_PAIR(2));
            wattron(sign, A_BOLD);
            mvwprintw(sign, 7, 2, "%s", sign_up_items[i]);
            wattroff(sign, A_BOLD);
            wattroff(sign, COLOR_PAIR(2));
            wrefresh(sign);
        }
        
        else if (i == 1){
            mvwprintw(sign, 3, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 2){
            mvwprintw(sign, 5, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if(i == 4){
            mvwprintw(sign, 9, 4, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 0){
            mvwprintw(sign, 1, 2, "%s", sign_up_items[i]);
            refresh();
        }
    }
    while(1) {
        wmove(sign, 7, 18 + index);
        int c = mvwgetch(sign, 7, 18 + index);
        if(c == KEY_BACKSPACE)
            if(index > 0) {
                mvwprintw(sign, 7, (18 + index), "%c", ' ');
                --index;
                continue;
            }
            else {
                continue;
            }
        
        
        if(c == '\n'){
            // if(exist){
            //     attron(COLOR_PAIR(3));
            //     mvprintw(1, 1, "%s", "USERNAME CURRENTLY EXISTS !");
            //     napms(850);
            //     attroff(COLOR_PAIR(3));
            //     refresh();
            //     continue;
            // }
            RemWord[index] = '\0';

            if(RemWord[0] == '\0') {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "REMINDWORD IS EMPTY !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else {
                //save in file
                return 0;
            }
        }
        else {
            if(index > 11) {
                attron(COLOR_PAIR(3));
                mvprintw(1, 1, "%s", "The maximum REMINDWORD lenght is 12!");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(3));
                move(1, 1);
                clrtoeol();
                refresh();
                continue;
            }
            else {
                RemWord[index] = c;
                ++index;
                mvwprintw(sign, 7, (18 + index), "%c", c);
            }
        }
    }
} 

 
int sign_up(){
    clear();
    refresh();
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    char *sign_up_items[5] = {"UserName:", "E-Mail:", "Password:", "Word Reminder:", "creat random passowrd (press 'r')"};
    WINDOW *sign = newwin(11, 40, 7, 20);
    keypad(sign, TRUE);
    wclear(sign);
    box(sign, 0, 0);
    for (int i = 0; i < 5; i++){

        if (i == 0){
            wattron(sign, COLOR_PAIR(2));
            wattron(sign, A_BOLD);
            mvwprintw(sign, 1, 2, "%s", sign_up_items[i]);
            wattroff(sign, A_BOLD);
            wattroff(sign, COLOR_PAIR(2));
            wrefresh(sign);
        }
        
        else if (i == 2){
            mvwprintw(sign, 5, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 1){
            mvwprintw(sign, 3, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if(i == 3){
            mvwprintw(sign, 7, 2, "%s", sign_up_items[i]);
            refresh();
        }
        else if (i == 4){
            mvwprintw(sign, 9, 4, "%s", sign_up_items[i]);
            refresh();
        }
    }

    wrefresh(sign);
    curs_set(0);
    username();
    email();
    int cd = getchar();
    if(cd == 'r'){
        rand_password();
    }
    else{
        password();
    }
    remind();          
    
    return TRUE;
    
}


int login(){

    clear();
    refresh();
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    char *log_items[3] = {"UserName:", "Password:", "Forget PASSWORD (press 'f')"};
    WINDOW *log = newwin(5, 40, 11, 20);
    keypad(log, TRUE);
    wclear(log);
    box(log, 0, 0);
    for (int i = 0; i < 2; i++){
        if (i == 0){
            wattron(log, COLOR_PAIR(2));
            wattron(log, A_BOLD);
            mvwprintw(log, 1, 2, "%s", log_items[i]);
            wattroff(log, A_BOLD);
            wattroff(log, COLOR_PAIR(2));
            wrefresh(log);
        }
        
        else if (i == 1){
            mvwprintw(log, 3, 2, "%s", log_items[i]);
            refresh();
        }

        else if (i == 2){
            mvwprintw(log, 5, 6, "%s", log_items[i]);
            refresh();
        }
    }
    wrefresh(log);
    //username_login();
    wmove(log, 3, 18);
    int c = mvwgetch(log, 3, 18);
    if(c == 'f'){
     //   remind_log();
    }
    //password_log();
}

// username_login()
// {
//     clear();
//     refresh();
//     keypad(stdscr, TRUE);
//     raw();
//     curs_set(0);
//     char *log_items[3] = {"UserName:", "Password:", "Forget PASSWORD (press 'f')"};
//     WINDOW *log = newwin(5, 40, 11, 20);
//     keypad(log, TRUE);
//     wclear(log);
//     box(log, 0, 0);
//     int index = 0;
//     for (int i = 0; i < 2; i++){
//         if (i == 0){
//             wattron(log, COLOR_PAIR(2));
//             wattron(log, A_BOLD);
//             mvwprintw(log, 1, 2, "%s", log_items[i]);
//             wattroff(log, A_BOLD);
//             wattroff(log, COLOR_PAIR(2));
//             wrefresh(log);
//         }
        
//         else if (i == 1){
//             mvwprintw(log, 3, 2, "%s", log_items[i]);
//             refresh();
//         }

//         else if (i == 2){
//             mvwprintw(log, 5, 6, "%s", log_items[i]);
//             refresh();
//         }
//     }
//     while(1) {
//         wmove(log, 1, 18 + index);
//         int c = mvwgetch(log, 1, 18 + index);
//         if(c == KEY_BACKSPACE)
//             if(index > 0) {
//                 mvwprintw(log, 1, (18 + index), "%c", ' ');
//                 --index;
//                 continue;
//             }
//             else {
//                 continue;
//             }
        
        
//         if(c == '\n'){
//             UserName[index] = '\0';
//             // if(not exist){
//             //     attron(COLOR_PAIR(3));
//             //     mvprintw(1, 1, "%s", "USERNAME NOT EXISTS !");
//             //     napms(850);
//             //     attroff(COLOR_PAIR(3));
//             //     refresh();
//             //     continue;
//             // }

//             // else {
//             //     //save in file
//             //     return 0;
//             // }
//         }
//         else {
//             if(index > 11) {
//                 attron(COLOR_PAIR(3));
//                 mvprintw(1, 1, "%s", "The maximum USERNAME lenght is 12!");
//                 refresh();
//                 napms(850);
//                 attroff(COLOR_PAIR(3));
//                 move(1, 1);
//                 clrtoeol();
//                 refresh();
//                 continue;
//             }
//             else {
//                 UserName[index] = c;
//                 ++index;
//                 mvwprintw(log, 1, (18 + index), "%c", c);
//             }
//         }
//     }
// }

// remind_log(){
//     //show remind word
// }

// password_log(){
//     clear();
//     refresh();
//     keypad(stdscr, TRUE);
//     raw();
//     curs_set(0);
//     char *log_items[3] = {"UserName:", "Password:", "Forget PASSWORD (press 'f')"};
//     WINDOW *log = newwin(5, 40, 11, 20);
//     keypad(log, TRUE);
//     wclear(log);
//     box(log, 0, 0);
//     int index = 0;
//     noecho();
//     for (int i = 0; i < 3; i++){
//         if (i == 1){
//             wattron(log, COLOR_PAIR(2));
//             wattron(log, A_BOLD);
//             mvwprintw(log, 3, 2, "%s", log_items[i]);
//             wattroff(log, A_BOLD);
//             wattroff(log, COLOR_PAIR(2));
//             wrefresh(log);
//         }        
//         else if (i == 0){
//             mvwprintw(log, 1, 2, "%s", log_items[i]);
//             refresh();
//         }
//         else if (i == 2){
//             mvwprintw(log, 5, 6, "%s", log_items[i]);
//             refresh();
//         }
//     }
//     while(1) {
//         wmove(log, 3, 18 + index);
//         int c = mvwgetch(log, 3, 18 + index);
//         if(c == KEY_BACKSPACE)
//             if(index > 0) {
//                 mvwprintw(log, 3, (18 + index), "%c", ' ');
//                 --index;
//                 continue;
//             }
//             else {
//                 continue;
//             } 
            
        
        
//         if(c == '\n'){
//             int uppercase = 0, lowercase = 0, digit = 0;
//             Password[index] = '\0';

//             // if(false){
//             // }            
//             //save in file
//             return 0;
//         }

//         else {
//             if(index > 11) {
//                 attron(COLOR_PAIR(3));
//                 mvprintw(1, 1, "%s", "The maximum PASSWORD lenght is 12!");
//                 refresh();
//                 napms(850);
//                 attroff(COLOR_PAIR(3));
//                 move(1, 1);
//                 clrtoeol();
//                 refresh();
//                 continue;
//             }
//             else {
//                 Password[index] = c;
//                 ++index;
//                 mvwprintw(log, 3, (18 + index), "%c", '*');
//             }
//         }
//     }
// }

int pre_game(){

    keypad(stdscr, TRUE);
    raw();
    curs_set(0);

    int select = 0;
    char *start_items[5] = {"NEW GAME", "OLD GAME", "SCORE BORD", "PROFILE", "SETTINGS"};
    WINDOW *menu = newwin(11, 20, 6, 30);
    keypad(menu, TRUE);
    wclear(menu);
    box(menu, 0,  0);
    

    for (int i = 0; i < 5; i++)
    {
        if (i == 0){
            wattron(menu, COLOR_PAIR(1));
            wattron(menu, A_BOLD);
            mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
            wattroff(menu, A_BOLD);
            wattroff(menu, COLOR_PAIR(1));
        }
        
        else if (i == 1)
            mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
        else if (i == 2)
            mvwprintw(menu, 2 * i + 1, 6, "%s", start_items[i]);
        else if (i == 3)
            mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
        else if (i == 4)
            mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
        move(1, 1);          
        clrtoeol();            
        mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
        refresh();
    }

    wrefresh(menu);
    while (1)
    {
        wrefresh(menu);
        int c = wgetch(menu);
        if (c == KEY_UP)
        {
            wrefresh(menu);
            if (select == 0){
                select = 4;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            else{
                --select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 5; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 6, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 3){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 4){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }
                else{
                    if (i == 0)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);

                    if (i == 1)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);

                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 6, "%s", start_items[i]);

                    if (i == 3)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        
                    if (i == 4)
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                }
            }
        }

        else if (c == KEY_DOWN){
            if (select == 4){
                select = 0;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }
            else{
                ++select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 5; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 6, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 3){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }

                    else if (i == 4){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }

                else{
                    if (i == 0)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                    if (i == 1)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 6, "%s", start_items[i]);
                    if (i == 3)
                        mvwprintw(menu, 2 * i + 1, 8, "%s", start_items[i]);
                    if (i == 4)
                        mvwprintw(menu, 2 * i + 1, 7, "%s", start_items[i]);
                }
            }
        }

        else if (c == '\n'){
            wrefresh(menu);
            delwin(menu);
            return select;
        }
        wrefresh(menu);
    }

}

int settings(){
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);
    int select = 0, select_color = 0, select_hard = 0;
    char *start_items[3] = {"SIGN UP", "LOGIN", "GUEST"};
    char *color_items[3] = {"GREEN", "RED", "BLUE"};
    char *hard_items[3] = {"EASY", "MEDIUM", "HARD"};
    WINDOW *menu = newwin(7, 20, 8, 30);
    keypad(menu, TRUE);
    wclear(menu);
    box(menu, 0,  0);
    
    for (int i = 0; i < 3; i++)
    {
        if (i == 0){
            wattron(menu, COLOR_PAIR(1));
            wattron(menu, A_BOLD);
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
            wattroff(menu, A_BOLD);
            wattroff(menu, COLOR_PAIR(1));
        }
        
        else if (i == 1)
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);

        else if (i == 2)
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);

        move(1, 1);          
        clrtoeol();            
        mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
        refresh();
    }

    wrefresh(menu);
    while (1)
    {
        wrefresh(menu);
        int c = wgetch(menu);
        if (c == KEY_UP)
        {
            wrefresh(menu);
            if (select == 0){
                select = 2;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            else{
                --select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 3; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }
                else{
                    if (i == 0){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    if (i == 1){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    if (i == 2){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                    }
                }
            }
        }

        else if (c == KEY_DOWN){
            if (select == 2){
                select = 0;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }
            else{
                ++select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }
            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 3; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }

                else{
                    if (i == 0){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }
                    if (i == 1){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }
                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                }
            }
        }

        else if(c == 'n'){
            if(select == 0) {
                if(select_color == 2)
                    select_color = 0;
                else
                    ++select_color;
            }
            else if(select == 1){
                if(select_hard == 2)
                    select_hard = 0;
                else
                    ++select_hard;
            }            
            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 3; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }

                else{
                    if (i == 0){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }
                    if (i == 1){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }
                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                }
            }
        }

        else if(c == 'b'){
            if(select == 0) {
                if(select_color == 0)
                    select_color = 2;
                else
                    --select_color;
            }
            else if(select == 1){
                if(select_hard == 0)
                    select_hard = 2;
                else
                    --select_hard;
            }
            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 3; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                    }
                }

                else{
                    if (i == 0){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_color == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_color == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_color == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", color_items[select_color]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }
                    if (i == 1){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        if(select_hard == 0) {
                            wattron(menu, COLOR_PAIR(3));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(3));
                        }
                        else if(select_hard == 1) {
                            wattron(menu, COLOR_PAIR(4));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(4));
                        }
                        else if(select_hard == 2){
                            wattron(menu, COLOR_PAIR(5));
                            mvwprintw(menu, 2 * i + 1, 9, "%s", hard_items[select_hard]);
                            wattroff(menu, COLOR_PAIR(5));
                        }
                    }
                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                }
            }
        }

        else if (c == '\n'){
            wrefresh(menu);
            delwin(menu);
            return select;
        }
        wrefresh(menu);
    }
}

int profile() {
    keypad(stdscr, TRUE);
    raw();
    curs_set(0);

    int select = 0;
    char *start_items[5] = {"USERNAME", "SCORE", "GOLD", "N OF GAMES", "EXPERIENCE"};
    WINDOW *menu = newwin(11, 20, 6, 30);
    keypad(menu, TRUE);
    wclear(menu);
    box(menu, 0,  0);
    

    for (int i = 0; i < 5; i++)
    {
        if (i == 0){
            wattron(menu, COLOR_PAIR(4));
            wattron(menu, A_BOLD);
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
            wattroff(menu, A_BOLD);
            wattroff(menu, COLOR_PAIR(4));
        }
        
        else if (i == 1)
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
        else if (i == 2)
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
        else if (i == 3)
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
        else if (i == 4)
            mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
        move(1, 1);          
        clrtoeol();            
        mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
        refresh();
    }

    wrefresh(menu);
    while (1)
    {
        wrefresh(menu);
        int c = wgetch(menu);
        if (c == KEY_UP)
        {
            wrefresh(menu);
            if (select == 0){
                select = 4;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            else{
                --select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 5; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 3){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 4){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }
                }
                else{
                    if (i == 0)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);

                    if (i == 1)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);

                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);

                    if (i == 3)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        
                    if (i == 4)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                }
            }
        }

        else if (c == KEY_DOWN){
            if (select == 4){
                select = 0;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }
            else{
                ++select;
                move(1, 1);          
                clrtoeol();            
                mvprintw(1, 1, "YOU'RE SELECTED: %s", start_items[select]);
                refresh();
            }

            wclear(menu);
            box(menu, 0,  0);
            for (int i = 0; i < 5; i++){
                if (i == select){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 1){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 2){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 3){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }

                    else if (i == 4){
                        wattron(menu, COLOR_PAIR(4));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(4));
                    }
                }

                else{
                    if (i == 0)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                    if (i == 1)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                    if (i == 2)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                    if (i == 3)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                    if (i == 4)
                        mvwprintw(menu, 2 * i + 1, 2, "%s", start_items[i]);
                }
            }
        }

        else if (c == '\n'){
            wrefresh(menu);
            delwin(menu);
            return select;
        }
        wrefresh(menu);
    }

}
// int x(){
//     int select = pre_game();
//         if(select == 0)
//             new_game();
//         if(select == 1)
//             old_game();
//         if(select == 2)
//             score();
//         if(select == 3)
//             profile();
//         if(select == 4)
//             settings();
// }

void map_create(){
    curs_set(0);

    for(int j = 0; j < 24; j++){
        for(int i = 0; i < 80; i++){
            map[floor][j][i] = ' ';
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
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 1){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = (rand() % (18 - a[i].lenght) + 20);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 2){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = (rand() % (18 - a[i].lenght) + 40);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;
            
            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 3){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = rand() % (10 - a[i].width);
            a[i].column = (rand() % (18 - a[i].lenght) + 60);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row + a[i].width - 1][door] = '+';
            a[i].door_row = a[i].row + a[i].width - 1;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 4){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = rand() % (18 - a[i].lenght);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 5){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = (rand() % (18 - a[i].lenght) + 20);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;
            
            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 6){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = (rand() % (18 - a[i].lenght) + 40);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column + a[i].lenght - 1] = '+';
            a[i].door_right_row = door;
            a[i].door_right_column = a[i].column + a[i].lenght - 1;
            
            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
        else if(i == 7){
            a[i].width = (rand() % 4 + 6);
            a[i].lenght = (rand() % 6 + 6);
            a[i].row = (rand() % (10 - a[i].width) + 12);
            a[i].column = (rand() % (18 - a[i].lenght) + 60);

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column] = '|';
            }

            for(int j = a[i].row; j < a[i].row + a[i].width; j++){
                map[floor][j][a[i].column + a[i].lenght - 1] = '|';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row][j] = '*';
            }

            for(int j = a[i].column; j < a[i].column + a[i].lenght; j++){
                map[floor][a[i].row + a[i].width - 1][j] = '*';
            } 

            door = rand() % (a[i].lenght - 2) + a[i].column + 1;
            map[floor][a[i].row][door] = '+';
            a[i].door_row = a[i].row;
            a[i].door_column = door;

            door = rand() % (a[i].width - 2) + a[i].row + 1;
            map[floor][door][a[i].column] = '+';
            a[i].door_left_row = door;
            a[i].door_left_column = a[i].column;

            for(int k = a[i].row + 1; k < a[i].row + a[i].width - 1; k++){
                for(int j = a[i].column + 1; j < a[i].column + a[i].lenght - 1; j++){
                    map[floor][k][j] = '.';
                }
            }

            if((rand() % 2) == 1){
                pillar_row = rand() % (a[i].width - 2) + a[i].row + 1;
                pillar_column = rand() % (a[i].lenght - 2) + a[i].column + 1;
                map[floor][pillar_row][pillar_column] = 'O';
            }
        }
    }




    for(int j = 0; j < 1; j++){
        if(a[0].door_column == a[4].door_column){
            for(int i = a[0].door_row + 1; i < a[4].door_row; i++)
                map[floor][i][a[0].door_column] = '#';
        }
        else if(a[0].door_column > a[4].door_column){
            for(int i = a[0].door_row + 1; i <= ((a[4].door_row + a[0].door_row) / 2); i++)
                map[floor][i][a[0].door_column] = '#';
            for(int i = a[4].door_column; i < a[0].door_column; i++)
                map[floor][((a[4].door_row + a[0].door_row) / 2)][i] = '#';
            for(int i = ((a[4].door_row + a[0].door_row) / 2); i < a[4].door_row; i++)
                map[floor][i][a[4].door_column] = '#';
        }
        else{
            for(int i = a[0].door_row + 1; i <= ((a[4].door_row + a[0].door_row) / 2); i++)
                map[floor][i][a[0].door_column] = '#';
            for(int i = a[0].door_column; i < a[4].door_column; i++)
                map[floor][((a[0].door_row + a[4].door_row) / 2)][i] = '#';
            for(int i = ((a[4].door_row + a[0].door_row) / 2); i < a[4].door_row; i++)
                map[floor][i][a[4].door_column] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[1].door_column == a[5].door_column){
            for(int i = a[1].door_row + 1; i < a[5].door_row; i++)
                map[floor][i][a[1].door_column] = '#';
        }
        else if(a[1].door_column > a[5].door_column){
            for(int i = a[1].door_row + 1; i <= ((a[5].door_row + a[1].door_row) / 2); i++)
                map[floor][i][a[1].door_column] = '#';
            for(int i = a[5].door_column; i < a[1].door_column; i++)
                map[floor][((a[5].door_row + a[1].door_row) / 2)][i] = '#';
            for(int i = ((a[5].door_row + a[1].door_row) / 2); i < a[5].door_row; i++)
                map[floor][i][a[5].door_column] = '#';
        }
        else{
            for(int i = a[1].door_row + 1; i <= ((a[5].door_row + a[1].door_row) / 2); i++)
                map[floor][i][a[1].door_column] = '#';
            for(int i = a[1].door_column; i < a[5].door_column; i++)
                map[floor][((a[1].door_row + a[5].door_row) / 2)][i] = '#';
            for(int i = ((a[5].door_row + a[1].door_row) / 2); i < a[5].door_row; i++)
                map[floor][i][a[5].door_column] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[2].door_column == a[6].door_column){
            for(int i = a[2].door_row + 1; i < a[6].door_row; i++)
                map[floor][i][a[2].door_column] = '#';
        }
        else if(a[2].door_column > a[6].door_column){
            for(int i = a[2].door_row + 1; i <= ((a[6].door_row + a[2].door_row) / 2); i++)
                map[floor][i][a[2].door_column] = '#';
            for(int i = a[6].door_column; i < a[2].door_column; i++)
                map[floor][((a[6].door_row + a[2].door_row) / 2)][i] = '#';
            for(int i = ((a[6].door_row + a[2].door_row) / 2); i < a[6].door_row; i++)
                map[floor][i][a[6].door_column] = '#';
        }
        else{
            for(int i = a[2].door_row + 1; i <= ((a[6].door_row + a[2].door_row) / 2); i++)
                map[floor][i][a[2].door_column] = '#';
            for(int i = a[2].door_column; i < a[6].door_column; i++)
                map[floor][((a[2].door_row + a[6].door_row) / 2)][i] = '#';
            for(int i = ((a[6].door_row + a[2].door_row) / 2); i < a[6].door_row; i++)
                map[floor][i][a[6].door_column] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[3].door_column == a[7].door_column){
            for(int i = a[3].door_row + 1; i < a[7].door_row; i++)
                map[floor][i][a[3].door_column] = '#';
        }
        else if(a[3].door_column > a[7].door_column){
            for(int i = a[3].door_row + 1; i <= ((a[7].door_row + a[3].door_row) / 2); i++)
                map[floor][i][a[3].door_column] = '#';
            for(int i = a[7].door_column; i < a[3].door_column; i++)
                map[floor][((a[7].door_row + a[3].door_row) / 2)][i] = '#';
            for(int i = ((a[7].door_row + a[3].door_row) / 2); i < a[7].door_row; i++)
                map[floor][i][a[7].door_column] = '#';
        }
        else{
            for(int i = a[3].door_row + 1; i <= ((a[7].door_row + a[3].door_row) / 2); i++)
                map[floor][i][a[3].door_column] = '#';
            for(int i = a[3].door_column; i < a[7].door_column; i++)
                map[floor][((a[3].door_row + a[7].door_row) / 2)][i] = '#';
            for(int i = ((a[7].door_row + a[3].door_row) / 2); i < a[7].door_row; i++)
                map[floor][i][a[7].door_column] = '#';
        }
    }




    
    for(int j = 0; j < 1; j++){
        if(a[0].door_right_row == a[1].door_left_row){
            for(int i = a[0].door_right_column + 1; i < a[1].door_left_column; i++){
                map[floor][a[0].door_right_row][i] = '#';
            }
        }
        else if(a[0].door_right_row < a[1].door_left_row){
            for(int i = a[0].door_right_column + 1; i <= ((a[0].door_right_column + a[1].door_left_column) / 2); i++)
                map[floor][a[0].door_right_row][i] = '#';
            for(int i = a[0].door_right_row; i <= a[1].door_left_row; i++)
                map[floor][i][((a[0].door_right_column + a[1].door_left_column) / 2)] = '#';
            for(int i = ((a[0].door_right_column + a[1].door_left_column) / 2); i < a[1].door_left_column; i++)
                map[floor][a[1].door_left_row][i] = '#';
        }
        else if(a[0].door_right_row > a[1].door_left_row){
            for(int i = a[0].door_right_column + 1; i <= ((a[0].door_right_column + a[1].door_left_column) / 2); i++)
                map[floor][a[0].door_right_row][i] = '#';
            for(int i = a[1].door_left_row; i <= a[0].door_right_row; i++)
                map[floor][i][((a[0].door_right_column + a[1].door_left_column) / 2)] = '#';
            for(int i = ((a[0].door_right_column + a[1].door_left_column) / 2); i < a[1].door_left_column; i++)
                map[floor][a[1].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[1].door_right_row == a[2].door_left_row){
            for(int i = a[1].door_right_column + 1; i < a[2].door_left_column; i++){
                map[floor][a[1].door_right_row][i] = '#';
            }
        }
        else if(a[1].door_right_row < a[2].door_left_row){
            for(int i = a[1].door_right_column + 1; i <= ((a[1].door_right_column + a[2].door_left_column) / 2); i++)
                map[floor][a[1].door_right_row][i] = '#';
            for(int i = a[1].door_right_row; i <= a[2].door_left_row; i++)
                map[floor][i][((a[1].door_right_column + a[2].door_left_column) / 2)] = '#';
            for(int i = ((a[1].door_right_column + a[2].door_left_column) / 2); i < a[2].door_left_column; i++)
                map[floor][a[2].door_left_row][i] = '#';
        }
        else{
            for(int i = a[1].door_right_column + 1; i <= ((a[1].door_right_column + a[2].door_left_column) / 2); i++)
                map[floor][a[1].door_right_row][i] = '#';
            for(int i = a[2].door_left_row; i <= a[1].door_right_row; i++)
                map[floor][i][((a[1].door_right_column + a[2].door_left_column) / 2)] = '#';
            for(int i = ((a[1].door_right_column + a[2].door_left_column) / 2); i < a[2].door_left_column; i++)
                map[floor][a[2].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[2].door_right_row == a[3].door_left_row){
            for(int i = a[2].door_right_column + 1; i < a[3].door_left_column; i++){
                map[floor][a[2].door_right_row][i] = '#';
            }
        }
        else if(a[2].door_right_row < a[3].door_left_row){
            for(int i = a[2].door_right_column + 1; i <= ((a[2].door_right_column + a[3].door_left_column) / 2); i++)
                map[floor][a[2].door_right_row][i] = '#';
            for(int i = a[2].door_right_row; i <= a[3].door_left_row; i++)
                map[floor][i][((a[2].door_right_column + a[3].door_left_column) / 2)] = '#';
            for(int i = ((a[2].door_right_column + a[3].door_left_column) / 2); i < a[3].door_left_column; i++)
                map[floor][a[3].door_left_row][i] = '#';
        }
        else{
            for(int i = a[2].door_right_column + 1; i <= ((a[2].door_right_column + a[3].door_left_column) / 2); i++)
                map[floor][a[2].door_right_row][i] = '#';
            for(int i = a[3].door_left_row; i <= a[2].door_right_row; i++)
                map[floor][i][((a[2].door_right_column + a[3].door_left_column) / 2)] = '#';
            for(int i = ((a[2].door_right_column + a[3].door_left_column) / 2); i < a[3].door_left_column; i++)
                map[floor][a[3].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[4].door_right_row == a[5].door_left_row){
            for(int i = a[4].door_right_column + 1; i < a[5].door_left_column; i++){
                map[floor][a[4].door_right_row][i] = '#';
            }
        }
        else if(a[4].door_right_row < a[5].door_left_row){
            for(int i = a[4].door_right_column + 1; i <= ((a[4].door_right_column + a[5].door_left_column) / 2); i++)
                map[floor][a[4].door_right_row][i] = '#';
            for(int i = a[4].door_right_row; i <= a[5].door_left_row; i++)
                map[floor][i][((a[4].door_right_column + a[5].door_left_column) / 2)] = '#';
            for(int i = ((a[4].door_right_column + a[5].door_left_column) / 2); i < a[5].door_left_column; i++)
                map[floor][a[5].door_left_row][i] = '#';
        }
        else{
            for(int i = a[4].door_right_column + 1; i <= ((a[4].door_right_column + a[5].door_left_column) / 2); i++)
                map[floor][a[4].door_right_row][i] = '#';
            for(int i = a[5].door_left_row; i <= a[4].door_right_row; i++)
                map[floor][i][((a[4].door_right_column + a[5].door_left_column) / 2)] = '#';
            for(int i = ((a[4].door_right_column + a[5].door_left_column) / 2); i < a[5].door_left_column; i++)
                map[floor][a[5].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[5].door_right_row == a[6].door_left_row){
            for(int i = a[5].door_right_column + 1; i < a[6].door_left_column; i++){
                map[floor][a[5].door_right_row][i] = '#';
            }
        }
        else if(a[5].door_right_row < a[6].door_left_row){
            for(int i = a[5].door_right_column + 1; i <= ((a[5].door_right_column + a[6].door_left_column) / 2); i++)
                map[floor][a[5].door_right_row][i] = '#';
            for(int i = a[5].door_right_row; i <= a[6].door_left_row; i++)
                map[floor][i][((a[5].door_right_column + a[6].door_left_column) / 2)] = '#';
            for(int i = ((a[5].door_right_column + a[6].door_left_column) / 2); i < a[6].door_left_column; i++)
                map[floor][a[6].door_left_row][i] = '#';
        }
        else{
            for(int i = a[5].door_right_column + 1; i <= ((a[5].door_right_column + a[6].door_left_column) / 2); i++)
                map[floor][a[5].door_right_row][i] = '#';
            for(int i = a[6].door_left_row; i <= a[5].door_right_row; i++)
                map[floor][i][((a[5].door_right_column + a[6].door_left_column) / 2)] = '#';
            for(int i = ((a[5].door_right_column + a[6].door_left_column) / 2); i < a[6].door_left_column; i++)
                map[floor][a[6].door_left_row][i] = '#';
        }
    }

    for(int j = 0; j < 1; j++){
        if(a[6].door_right_row == a[7].door_left_row){
            for(int i = a[6].door_right_column + 1; i < a[7].door_left_column; i++){
                map[floor][a[6].door_right_row][i] = '#';
            }
        }
        else if(a[6].door_right_row < a[7].door_left_row){
            for(int i = a[6].door_right_column + 1; i <= ((a[6].door_right_column + a[7].door_left_column) / 2); i++)
                map[floor][a[6].door_right_row][i] = '#';
            for(int i = a[6].door_right_row; i <= a[7].door_left_row; i++)
                map[floor][i][((a[6].door_right_column + a[7].door_left_column) / 2)] = '#';
            for(int i = ((a[6].door_right_column + a[7].door_left_column) / 2); i < a[7].door_left_column; i++)
                map[floor][a[7].door_left_row][i] = '#';
        }
        else{
            for(int i = a[6].door_right_column + 1; i <= ((a[6].door_right_column + a[7].door_left_column) / 2); i++)
                map[floor][a[6].door_right_row][i] = '#';
            for(int i = a[7].door_left_row; i <= a[6].door_right_row; i++)
                map[floor][i][((a[6].door_right_column + a[7].door_left_column) / 2)] = '#';
            for(int i = ((a[6].door_right_column + a[7].door_left_column) / 2); i < a[7].door_left_column; i++)
                map[floor][a[7].door_left_row][i] = '#';
        }
    }

    map[floor][a[0].row + 2][a[0].column + 2] = '$';
    character_row = a[0].row + 2, character_column = a[0].column + 2;

    refresh();
}

move_map(){
    initscr();
    noecho();
    curs_set(0);
    map_create();

    while(1){
        nodelay(stdscr, TRUE); 
        timeout(0);
        int c = getch();

        if(c == 'M'){
            
        }

        else if(c == 'i'){
            char *weapon_items[6] = {"GUN", "Mace", "Dagger", "Magic Wand", "Normal Arrow", "Sword"};
        
            WINDOW *menu = newwin(13, 30, 5, 25);
            keypad(menu, TRUE);
            wclear(menu);
            box(menu, 0,  0);
            while(1){
                wclear(menu);
                for(int i = 0; i < 6; i++){
                    if (i == 0){
                        wattron(menu, COLOR_PAIR(1));
                        wattron(menu, A_BOLD);
                        mvwprintw(menu, 2 * i + 1, 2, "%s", weapon_items[i]);
                        mvwprintw(menu, 2 * i + 1, 7, "NUMBER");
                        mvwprintw(menu, 2 * i + 1, 15, "DAMAGE");
                        mvprintw(menu, 2 * i + 1, 23, "SELECTED");
                        wattroff(menu, A_BOLD);
                        wattroff(menu, COLOR_PAIR(1));
                        wrefresh(menu);
                    }
                    else if (i == 1){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", weapon_items[i]);
                        mvwprintw(menu, 2 * i + 1, 9, "extreme");
                        mvwprintw(menu, 2 * i + 1, 18, "5");
                        if(select_gun == 'm'){
                            wattron(menu, COLOR_PAIR(2));
                            mvwprintw(menu, 2 * i + 1, 23, "Picked");
                            wattroff(menu, COLOR_PAIR(2));
                        }
                        wrefresh(menu);
                    }
                    else if (i == 2){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", weapon_items[i]);
                        mvwprintw(menu, 2 * i + 1, 10, "%s", number_dagger);
                        mvwprintw(menu, 2 * i + 1, 17, "12");
                        if(select_gun == 'd'){
                            wattron(menu, COLOR_PAIR(2));
                            mvwprintw(menu, 2 * i + 1, 23, "Picked");
                            wattroff(menu, COLOR_PAIR(2));
                        }
                        wrefresh(menu);
                    }
                    else if (i == 3){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", weapon_items[i]);
                        mvwprintw(menu, 2 * i + 1, 13, "%d", number_wand);
                        mvwprintw(menu, 2 * i + 1, 18, "15");
                        if(select_gun == 'w'){
                            wattron(menu, COLOR_PAIR(2));
                            mvwprintw(menu, 2 * i + 1, 24, "Picked");
                            wattroff(menu, COLOR_PAIR(2));
                        }
                        wrefresh(menu);
                    }
                    else if (i == 4){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", weapon_items[i]);
                        mvwprintw(menu, 2 * i + 1, 14, "%d", number_arrow);
                        mvwprintw(menu, 2 * i + 1, 19, "5");
                        if(select_gun == 'a'){
                            wattron(menu, COLOR_PAIR(2));
                            mvwprintw(menu, 2 * i + 1, 24, "Picked");
                            wattroff(menu, COLOR_PAIR(2));
                        }
                        wrefresh(menu);
                    }
                    else if (i == 5){
                        mvwprintw(menu, 2 * i + 1, 2, "%s", weapon_items[i]);
                        mvwprintw(menu, 2 * i + 1, 10, "%s", number_sword);
                        mvwprintw(menu, 2 * i + 1, 19, "12");
                        if(select_gun == 's'){
                            wattron(menu, COLOR_PAIR(2));
                            mvwprintw(menu, 2 * i + 1, 23, "Picked");
                            wattroff(menu, COLOR_PAIR(2));
                        }
                        wrefresh(menu);
                    }
                }

                wrefresh(menu);
                int z = getch();
                
                if(z == 'm'){
                    WINDOW *message = newwin(2, 40, 1, 1);
                    if(select_gun == 'm'){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THE GUN HAS ALREADY BEEN SELECTED !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else if(select_gun != 'x'){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "PUT YOUR GUN IN BACKPACK !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else{
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THE GUN WAS SUCCESSFULLY SELECTED !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        select_gun = 'd';
                        continue;
                    }
                    delwin(message);
                }

                if(z == 'd'){
                    WINDOW *message = newwin(2, 40, 1, 1);
                    if(select_gun == 'd'){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THE GUN HAS ALREADY BEEN SELECTED !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else if(select_gun != 'x'){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "PUT YOUR GUN IN BACKPACK !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else if(number_dagger == 0){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THERE IS NO GUN !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else{
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THE GUN WAS SUCCESSFULLY SELECTED !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        select_gun = 'd';
                        continue;
                    }
                    delwin(message);
                }

                if(z == 'w'){
                    WINDOW *message = newwin(2, 40, 1, 1);
                    if(select_gun == 'w'){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THE GUN HAS ALREADY BEEN SELECTED !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else if(select_gun != 'x'){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "PUT YOUR GUN IN BACKPACK !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else if(number_wand == 0){
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THERE IS NO GUN !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        continue;
                    }
                    else{
                        wattron(message, COLOR_PAIR(6));
                        mvwprintw(message, 1, 1, "THE GUN WAS SUCCESSFULLY SELECTED !");
                        wrefresh(message);
                        napms(800);
                        wattroff(message, COLOR_PAIR(6));
                        wrefresh(message);
                        select_gun = 'd';
                        continue;
                    }
                    delwin(message);
                }
                
                if()
                
            }
        }
        else if(c == 'h'){
             
            if(map[floor][character_row][character_column - 1] == '|' || map[floor][character_row][character_column - 1] == 'D' || map[floor][character_row][character_column - 1] == 'F' || map[floor][character_row][character_column - 1] == 'G' || map[floor][character_row][character_column - 1] == 'S' || map[floor][character_row][character_column - 1] == 'U' || map[floor][character_row][character_column - 1] == 'O' || map[floor][character_row + 1][character_column] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row][character_column - 1] = '$';

                if(map[floor][character_row][character_column - 1] == '+')
                    map_door[floor][character_row][character_column - 1] = 1;
                if(map[floor][character_row][character_column - 1] == '#')
                    map_door[floor][character_row][character_column - 1] = 2;

                if(map_door[floor][character_row][character_column] == 1)
                    map[floor][character_row][character_column] = '+';
                if(map_door[floor][character_row][character_column] == 2)
                    map[floor][character_row][character_column] = '#';

                character_column = character_column - 1;
                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column -1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
            }
            refresh();
        }

        else if(c == 'l'){
             
            if(map[floor][character_row][character_column + 1] == '|' || map[floor][character_row][character_column + 1] == 'D' || map[floor][character_row][character_column + 1] == 'F' || map[floor][character_row][character_column + 1] == 'G' || map[floor][character_row][character_column + 1] == 'S' || map[floor][character_row][character_column + 1] == 'U' || map[floor][character_row][character_column + 1] == 'O' || map[floor][character_row + 1][character_column] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row][character_column + 1] = '$';

                if(map[floor][character_row][character_column + 1] == '+')
                    map_door[floor][character_row][character_column + 1] = 1;
                if(map[floor][character_row][character_column + 1] == '#')
                    map_door[floor][character_row][character_column + 1] = 2;

                if(map_door[floor][character_row][character_column] == 1)
                    map[floor][character_row][character_column] = '+';
                if(map_door[floor][character_row][character_column] == 2)
                    map[floor][character_row][character_column] = '#';

                character_column = character_column + 1;
                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column -1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
            }
            refresh();
        }

        else if(c == 'k'){
             
            if(map[floor][character_row + 1][character_column] == '|' || map[floor][character_row + 1][character_column] == 'D' || map[floor][character_row + 1][character_column] == 'F' || map[floor][character_row + 1][character_column] == 'G' || map[floor][character_row + 1][character_column] == 'S' || map[floor][character_row + 1][character_column] == 'U' || map[floor][character_row + 1][character_column] == 'O' || map[floor][character_row + 1][character_column] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row + 1][character_column] = '$';

                if(map[floor][character_row + 1][character_column] == '+')
                    map_door[floor][character_row + 1][character_column] = 1;
                if(map[floor][character_row + 1][character_column] == '#')
                    map_door[floor][character_row + 1][character_column] = 2;

                if(map_door[floor][character_row][character_column] == 1)
                    map[floor][character_row][character_column] = '+';
                if(map_door[floor][character_row][character_column] == 2)
                    map[floor][character_row][character_column] = '#';

                character_row = character_row + 1;
                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column -1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
            }
            refresh();
        }

        else if(c == 'j'){
             
            if(map[floor][character_row - 1][character_column] == '*' || map[floor][character_row - 1][character_column] == 'D' || map[floor][character_row - 1][character_column] == 'F' || map[floor][character_row - 1][character_column] == 'G' || map[floor][character_row - 1][character_column] == 'S' || map[floor][character_row - 1][character_column] == 'U' || map[floor][character_row - 1][character_column] == 'O' || map[floor][character_row - 1][character_column] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row - 1][character_column] = '$';

                if(map[floor][character_row - 1][character_column] == '+')
                    map_door[floor][character_row - 1][character_column] = 1;
                if(map[floor][character_row - 1][character_column] == '#')
                    map_door[floor][character_row - 1][character_column] = 2;

                if(map_door[floor][character_row][character_column] == 1)
                    map[floor][character_row][character_column] = '+';
                if(map_door[floor][character_row][character_column] == 2)
                    map[floor][character_row][character_column] = '#';

                character_row = character_row - 1;
                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column -1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
                print_map();
            }
            refresh();
        }

        else if(c == 'y'){
             
            if(map[floor][character_row - 1][character_column - 1] == '|' || map[floor][character_row - 1][character_column - 1] == '*' || map[floor][character_row - 1][character_column - 1] == 'D' || map[floor][character_row - 1][character_column - 1] == 'F' || map[floor][character_row - 1][character_column - 1] == 'G' || map[floor][character_row - 1][character_column - 1] == 'S' || map[floor][character_row - 1][character_column - 1] == 'U' || map[floor][character_row - 1][character_column - 1] == 'O' || map[floor][character_row - 1][character_column - 1] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row - 1][character_column - 1] = '$';

                if(map[floor][character_row - 1][character_column - 1] == '+')
                    map_door[floor][character_row - 1][character_column - 1] = 1;
                if(map[floor][character_row - 1][character_column - 1] == '#')
                    map_door[floor][character_row - 1][character_column - 1] = 2;

                if(map_door[floor][character_row - 1][character_column - 1] == 1)
                    map[floor][character_row - 1][character_column - 1] = '+';
                if(map_door[floor][character_row - 1][character_column - 1] == 2)
                    map[floor][character_row - 1][character_column - 1] = '#';

                character_row = character_row - 1;
                character_column = character_column - 1;

                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column - 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
                print_map();
            }
            refresh();
        }

        else if(c == 'n'){
             
            if(map[floor][character_row + 1][character_column + 1] == '|' || map[floor][character_row + 1][character_column + 1] == '*' || map[floor][character_row + 1][character_column + 1] == 'D' || map[floor][character_row + 1][character_column + 1] == 'F' || map[floor][character_row + 1][character_column + 1] == 'G' || map[floor][character_row + 1][character_column + 1] == 'S' || map[floor][character_row + 1][character_column + 1] == 'U' || map[floor][character_row + 1][character_column + 1] == 'O' || map[floor][character_row + 1][character_column + 1] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row + 1][character_column + 1] = '$';

                if(map[floor][character_row + 1][character_column + 1] == '+')
                    map_door[floor][character_row + 1][character_column + 1] = 1;
                if(map[floor][character_row + 1][character_column + 1] == '#')
                    map_door[floor][character_row + 1][character_column + 1] = 2;

                if(map_door[floor][character_row + 1][character_column + 1] == 1)
                    map[floor][character_row + 1][character_column + 1] = '+';
                if(map_door[floor][character_row + 1][character_column + 1] == 2)
                    map[floor][character_row + 1][character_column + 1] = '#';

                character_row = character_row + 1;
                character_column = character_column + 1;

                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column - 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
                print_map();
                refresh();
            }
            refresh();
        }

        else if(c == 'u'){
             
            if(map[floor][character_row - 1][character_column + 1] == '|' || map[floor][character_row - 1][character_column + 1] == '*' || map[floor][character_row - 1][character_column + 1] == 'D' || map[floor][character_row - 1][character_column + 1] == 'F' || map[floor][character_row - 1][character_column + 1] == 'G' || map[floor][character_row - 1][character_column + 1] == 'S' || map[floor][character_row - 1][character_column + 1] == 'U' || map[floor][character_row - 1][character_column + 1] == 'O' || map[floor][character_row - 1][character_column + 1] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row - 1][character_column + 1] = '$';

                if(map[floor][character_row - 1][character_column + 1] == '+')
                    map_door[floor][character_row - 1][character_column + 1] = 1;
                if(map[floor][character_row - 1][character_column + 1] == '#')
                    map_door[floor][character_row - 1][character_column + 1] = 2;

                if(map_door[floor][character_row - 1][character_column + 1] == 1)
                    map[floor][character_row - 1][character_column + 1] = '+';
                if(map_door[floor][character_row - 1][character_column + 1] == 2)
                    map[floor][character_row - 1][character_column + 1] = '#';

                character_row = character_row - 1;
                character_column = character_column + 1;

                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column - 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
                print_map();
            }
            refresh();
        }

        else if(c == 'b'){
             
            if(map[floor][character_row + 1][character_column - 1] == '|' || map[floor][character_row + 1][character_column - 1] == '*' || map[floor][character_row + 1][character_column - 1] == 'D' || map[floor][character_row + 1][character_column - 1] == 'F' || map[floor][character_row + 1][character_column - 1] == 'G' || map[floor][character_row + 1][character_column - 1] == 'S' || map[floor][character_row + 1][character_column - 1] == 'U' || map[floor][character_row + 1][character_column - 1] == 'O' || map[floor][character_row + 1][character_column - 1] == ' '){
                attron(COLOR_PAIR(5));
                move(1, 1);
                clrtoeol();
                printw("INVALID ORDER !");
                refresh();
                napms(850);
                attroff(COLOR_PAIR(5));
                refresh();
                continue;
            }
            
            else{
                 
                map[floor][character_row][character_column] = '.';
                map[floor][character_row + 1][character_column - 1] = '$';

                if(map[floor][character_row + 1][character_column - 1] == '+')
                    map_door[floor][character_row + 1][character_column - 1] = 1;
                if(map[floor][character_row + 1][character_column - 1] == '#')
                    map_door[floor][character_row + 1][character_column - 1] = 2;

                if(map_door[floor][character_row + 1][character_column - 1] == 1)
                    map[floor][character_row + 1][character_column - 1] = '+';
                if(map_door[floor][character_row + 1][character_column - 1] == 2)
                    map[floor][character_row + 1][character_column - 1] = '#';

                character_row = character_row + 1;
                character_column = character_column - 1;

                if(map[floor][character_row - 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row - 1][character_column] = 1;
                }
                if(map[floor][character_row + 1][character_column] == '#'){
                    flag_corridor_map[floor][character_row + 1][character_column] = 1;
                }
                if(map[floor][character_row][character_column -1] == '#'){
                    flag_corridor_map[floor][character_row][character_column - 1] = 1;
                }
                if(map[floor][character_row][character_column + 1] == '#'){
                    flag_corridor_map[floor][character_row][character_column + 1] = 1;
                }
                print_map();
            }
            refresh();
        }
    }
}

void color() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
}
//24 80

int main(){
    initscr();
    raw();
    clear();
    noecho();
    color();
    menu_start();
    int select = menu_start();
    if(select == 0)
        sign_up();
    // else if(select == 1)
    //     login();
    // else
    //     guest();
    select = pre_game();
    if(select == 0 || select == 1)
        game();
    else if(select == 2)
        score();
    else if(select == 3)
        profile();
    else 
        settings();
    move_map();

    
    

    endwin();
    return 0;
}


else if(map[floor][character_row - 1][character_column] == '<'){

    map[floor][character_row - 1][character_column] = '.';
    map[floor][character_row][character_column] = '?';

    while(1){   
        int x = getch();
        
        if(x == '>'){
            map[floor][character_row - 1][character_column] = '<';
            map[floor][character_row][character_column] = '.';
            floor++;
            move_map();
            //next floor
            break;
        }
        
        else if(x == '<') {
            map[floor][character_row - 1][character_column] = '<';
            map[floor][character_row][character_column] = '.';
            floor--;
            move_map();
            //previous floor
            break;
        }

        else if(x == 'i'){
            //show weapon
        }

        else if(c == 'M'){
            for(int i = 0; i < 24; i++){
                for(int j = 0; j < 80; j++){
                    printw("%c", map[floor][i][j]);
                }
            }
        }

        else{
            map[floor][character_row - 1][character_column] = '<';
            map[floor][character_row][character_column] = '$';
        }
    }
}