#include <ncursesw/ncurses.h>
#include "lib/screen/screen.cpp"

int main(int argc, char **argv) {
    int height, width, startx, starty;
    initscr();
    cbreak();
    refresh();

    height = 10;
    width = 30;
    startx = (LINES - height)/3;
    starty = (COLS - width)/2;
    WINDOW *my_win = CreateWindow(height, width, startx, starty);
    int c = getch();
    endwin();
    return 0;
};


