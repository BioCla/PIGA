#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/_init/game_loop.hpp"

int main() {
	init();
	init_colorpairs();
	
	//Testing Colors
		empty();
		test_colors();
		getch();
		empty();

	Board main;
	Game loop(main);
	loop.start();
	
	endwin();
	return 0;
}