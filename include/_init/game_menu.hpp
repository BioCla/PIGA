#include "../assets/curses_lib_selector.hpp"

struct option {
	std::string label;
	std::function<void()> action;
};

class Menu {
	private:
		WINDOW* menuWin;
		WINDOW* titleWin;
		WINDOW* instructionsWin;
		static option list[];
		int selected;
		bool handleInput();
		void titleDisplay();
		void instructionsDisplay();
		void update(int selected);
		
	public:
		Menu();
		void render();
		static int returnCode;
};