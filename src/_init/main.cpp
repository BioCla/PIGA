#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/curses_color_pairing.hpp"
#include "../../include/_init/game_loop.hpp"

int main() {
	init();
	init_colorpairs();

	/* Testing GameBoard class */
		Board main;
		// printScreenSize(main._window);

	/* Testing GameLoop class */
		Game loop(main);
		loop.start();
	
	/* Testing Colors */
		empty();
		test_colors();

	getch();
	
	endwin();
	return 0;
}