#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/curses_color_pairing.hpp"

int main() {
	init();
	
	test_colors();
	getch();

	
	endwin();
	return 0;
}