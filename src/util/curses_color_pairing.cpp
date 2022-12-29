#include "../../include/util/curses_color_pairing.hpp"
#include "../../include/util/math_override.tpp"

/* Custom Colors */
#define X(name, hex) name = hex,
	enum Custom_Colors {
		CC
	};
#undef X

#define X(name, hex) name,
	Custom_Colors CColors[] = {
		CC
	};
#undef X
int CCSize = sizeof(CColors) / sizeof(CColors[0]);

void init_colorpairs() {
	// Init the CC
	for (int CIndex = 0; CIndex < CCSize; CIndex++) {
		init_HEX(getCC(CIndex), CColors[CIndex]);
	}
	
	for (int bg = 0; bg <= 7 + CCSize; bg++) {
		for (int fg = 0; fg <= 7 + CCSize; fg++) {
			init_pair(cantor(fg, bg), fg, bg);
		}
	}
}

void setcolor(int fg, int bg) {
	attron(COLOR_PAIR(cantor(fg, bg)));
}

void unsetcolor(int fg, int bg) {
	attroff(COLOR_PAIR(cantor(fg, bg)));
}

void setcolor(WINDOW* win, int fg, int bg) {
	wattron(win, COLOR_PAIR(cantor(fg, bg)));
}

void unsetcolor(WINDOW* win, int fg, int bg) {
	wattroff(win, COLOR_PAIR(cantor(fg, bg)));
}

void test_colors() {
	mvaddstr(0, 35, "COLOR DEMO");
	mvaddstr(1, 35, "This might not work if you are on Windows");
	mvprintw(2, 35, "This terminal supports the following colors: %s", 
	(tigetnum("colors") == -2 ? "Partially or not compatible" : tigetnum("colors") == -1 ? "ERROR" : std::to_string(tigetnum("colors")).c_str()));

	for (int bg = 0; bg <= CCSize + 7; bg++) {
		for (int fg = 0; fg <= CCSize + 7; fg++) {
			setcolor(fg, bg);
			mvaddstr(fg + 3, bg * 10, "...test...");
			unsetcolor(fg, bg);
		}
	}
	mvaddstr(LINES - 1, 0, "press any key to quit");
	refresh();
}