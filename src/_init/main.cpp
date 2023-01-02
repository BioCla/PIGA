#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/_init/game_loop.hpp"

#include "../../include/util/adj_graph_override.tpp"

int main() {
	init();
	init_colorpairs();
	
	//Testing Colors
		empty();
		test_colors();
		getch();
		empty();

	// Testing GameBoard class
		Board main;
		// printScreenSize(main._window);

	// Testing GameLoop class
		Game loop(main);
		loop.start();
	
	
	endwin();
	return 0;
}