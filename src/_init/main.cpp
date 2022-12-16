#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/curses_color_pairing.hpp"
#include "../../include/_init/game_board.hpp"

int main() {
	init();

	/* Testing GameBoard class */
	{
		GameBoard game_board;

		game_board.init();
		game_board.draw();

		printScreenSize(game_board.getGameWindow());
	}

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