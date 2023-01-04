#ifndef CURSES_COLOR_PAIRING
#define CURSES_COLOR_PAIRING

#include "../assets/extended_colors.hpp"

// The point is that using an enum you don't have to scan an array to find a specific color.
// You can just use the enum name to get the color.
// This should not be modified. If you want to add or remove colors, do it in extended_colors.hpp

#define X(name, hex) COLOR_##name, 
	enum CColor {
		CC
	};
#undef X

#define getCC(name) name + 8

// fg = foreground; bg = background

void init_colorpairs(void);
void setcolor(int fg, int bg);
void setcolor(WINDOW* win, int fg, int bg);
void unsetcolor(int fg, int bg);
void unsetcolor(WINDOW* win, int fg, int bg);
void test_colors();

// This file is used as a branch from which to extract the usable functions and definitions for color pairing.

#endif