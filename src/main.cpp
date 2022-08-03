#include <ncursesw/ncurses.h>
#include "lib/screen/screen.cpp"
//#include "lib/character/character.hpp"
#include "lib/character/character.cpp"


int main(int argc, char **argv) {
    WINDOW *my_win;
    int height, width, startx, starty, ch;
    initscr();
    noecho();
    start_color();
    cbreak();
    init_pair(1,COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    refresh();
    attroff(COLOR_PAIR(1));
    height = 18;
    width = 70;
    startx = (LINES - height)/3;
    starty = (COLS - width)/2;
    my_win = CreateWindow(height, width, startx, starty);
    mvprintw(startx+10, starty+20,"a");
    Character player = Character(startx+10, starty+20);
    while ((ch = getch()) != 'q'){
        player.HandleInput(ch);
    }
    
	endwin();	

	return 0;
}
