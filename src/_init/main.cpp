#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/curses_color_pairing.hpp"
#include "../../include/_init/game_board.hpp"
#include "../../include/_init/game_loop.hpp"

int main() {
	init();

	/* Testing GameBoard class */
		Board main;
		printScreenSize(main._window);

	/* Testing GameLoop class */
		Game loop(main._window);
		loop.start();
	

	/* Testing Colors */
	{	
		getch();
		empty();
		test_colors();
	}

	getch();
	endwin();
	return 0;
}