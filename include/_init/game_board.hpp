#include "../assets/curses_lib_selector.hpp"

class Board {
	protected:
		WINDOW* info_window;
		WINDOW* status_window;

	public:
		Board();
		void init();
		void draw();
		WINDOW* _window;
};