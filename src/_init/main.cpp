#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/curses_color_pairing.hpp"

int main() {
	init();

	while (getch() != 'q') {
		empty();
		centering_text(stdscr, 0, "Premi 'q' per uscire");
		printScreenSize(stdscr);
		refresh();
	}
	empty();

	test_colors();
	getch();

	endwin();
	return 0;
}