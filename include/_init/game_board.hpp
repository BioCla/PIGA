#include "../assets/curses_lib_selector.hpp"

class GameBoard {
	protected:
		WINDOW* info_window;
		WINDOW* game_window;
		WINDOW* status_window;

	public:
		GameBoard();
		void init();
		void draw();
		WINDOW* getInfoWindow();
		WINDOW* getGameWindow();
		WINDOW* getStatusWindow();
};