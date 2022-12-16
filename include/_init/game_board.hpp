#include "../assets/curses_lib_selector.hpp"

class GameBoard {
	protected:
		WINDOW* game_window;
	
	public:
		GameBoard();
		WINDOW* init();
		void draw();
};