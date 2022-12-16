#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/string_override.hpp"
#include "../../include/assets/program_checks.hpp"
#include "../../include/util/math_override.tpp"

void init() {
	// Inizializza ncurses e controlla se il terminale è valido
	initscr();
	CHECK_TERMINAL_VALIDITY

	// Configura alcune proprietà del terminale
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, true);
	
	clear();
	refresh();
}

void centering_text(WINDOW *terminal, int first_row, const char *string) {
	int centerx = terminal->_maxx / 2;
	int lendiv = strlen(string) / 2;
	int centerpos = centerx - lendiv;
	mvwaddstr(terminal, first_row, centerpos, string);
}

void empty() {
	clear();
	refresh();
}

void werase(WINDOW *terminal, int y, int x) {
	mvwaddch(terminal, y, x, ' ');
}

void mvwaddint(WINDOW* win, int posy, int posx, int input) {
	mvwprintw(win, posy, posx, "%s", intstr(input));
}

void printScreenSize(WINDOW *win) {
	int width = win->_maxx, height = win->_maxy;
	int dif = mathy::numDigits(width);
	int x = width / 2, y = height / 2;

	mvwaddint(stdscr, y, x, width);
	mvwaddstr(stdscr, y, x + dif + 1, "x");
	mvwaddint(stdscr, y, x + dif + 3, height);
}