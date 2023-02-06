#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/string_override.hpp"
#include "../../include/assets/program_checks.hpp"
#include "../../include/util/math_override.tpp"


void mvwaddint(WINDOW* win, int posy, int posx, int input) {
	int num_size = mathy::numDigits(input);
	char *text = new char[num_size];
	sprintf(text, "%d", input);
	mvwprintw(win, posy, posx, text);
}

void printScreenSize(WINDOW *win) {
	int width = win->_maxx, height = win->_maxy;
	int dif = mathy::numDigits(width);
	int x = width / 2, y = height / 2;

	mvwaddint(stdscr, y, x, width);
	mvwaddstr(stdscr, y, x + dif + 1, "x");
	mvwaddint(stdscr, y, x + dif + 3, height);
}