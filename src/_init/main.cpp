#include "../../include/util/curses_comodity_functions.hpp"

int main() {
	init();
	centering_text(stdscr, 0, "Hello World!");
	getch();
	end();
	return 0;
}