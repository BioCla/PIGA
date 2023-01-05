#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/_init/game_loop.hpp"
#include "../../include/_init/game_menu.hpp"

int main() {
	init();
	init_colorpairs();
	
	//Testing Colors
		empty();
		test_colors();
		getch();
		empty();

	//Testing Menu
		Menu menu;
		menu.render();
	
	Board main;
	Game loop(main);
	loop.start();
	
	endwin();
	return 0;
}