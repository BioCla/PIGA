#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/curses_color_pairing.hpp"
#include "../../include/_init/game_board.hpp"

int main() {
	init();

	{
		GameBoard game_board;
		WINDOW* game_window = game_board.init();

		game_board.draw();
		printScreenSize(game_window);
	}

	getch();
	empty();
	test_colors();
	
	getch();
	endwin();
	return 0;
}