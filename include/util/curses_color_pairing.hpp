#include "../assets/extended_colors.hpp"

// The point is that using an enum you don't have to scan an array to find a specific color.
// You can just use the enum name to get the color.
// This should not be modified. If you want to add or remove colors, do it in extended_colors.hpp

#define X(name, hex) name = hex,
	enum Custom_Colors {
		CC
	};
#undef X

// fg = foreground; bg = background

int is_bold(int fg);
void init_colorpairs(void);
short curs_color(int fg);
int colornum(int fg, int bg);
void setcolor(int fg, int bg);
void setcolor(WINDOW* win, int fg, int bg);
void unsetcolor(int fg, int bg);
void unsetcolor(WINDOW* win, int fg, int bg);
void test_colors();

// This file is used as a branch from which to extract the usable functions and definitions for color pairing.