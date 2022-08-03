#include <ncurses.h>

WINDOW * CreateWindow(int height, int width, int startx, int starty){
    WINDOW * win = newwin(height, width, startx, starty);
    box(win, 0, 0);
    wrefresh(win);
    
    return win;
}


