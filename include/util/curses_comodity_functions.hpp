#ifndef CURSES_COMODITY_FUNCTIONS
#define CURSES_COMODITY_FUNCTIONS

#include "../assets/curses_lib_selector.hpp"

#define erase(y, x) werase(stdscr, y, x)

void init();
void centering_text(WINDOW *terminal, int first_row, const char *string);
void empty();
void werase(WINDOW *terminal, int y, int x);
void mvwaddint(WINDOW* win, int posy, int posx, int input);
void printScreenSize(WINDOW *win);

#endif