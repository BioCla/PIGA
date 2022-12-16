#include "../assets/curses_lib_selector.hpp"

class Board {
	protected:
		WINDOW* info_window;
		WINDOW* game_window;
		WINDOW* status_window;

	public:
		Board();
		void init();
		void draw();
		WINDOW* getGameWindow() { return game_window; };
		WINDOW* getInfoWindow() { return info_window; };
		WINDOW* getStatusWindow() { return status_window; };
};