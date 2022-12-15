#ifndef ENGINE
#define ENGINE

#include "../assets/curses_lib_OS_selector.hpp"

void init();
void end();

void centering_text(WINDOW *terminal, int first_row, const char *string);
void empty();
void erase(int y, int x);

void werase(WINDOW *terminal, int y, int x);


#endif