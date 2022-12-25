#include "../../include/util/curses_color_pairing.hpp"
#include "../../include/util/math_override.tpp"

// https://www.linuxjournal.com/content/about-ncurses-colors-0

void init_colorpairs() {
	#define X(name, hex) name,
		Custom_Colors CColors[] = {
			CC
		};
	#undef X

	// 8 normal colors (provided by ncurses)
	for (int bg = 0; bg <= 7; bg++) {
		for (int fg = 0; fg <= 7; fg++) {
			init_pair(colornum(fg, bg), curs_color(fg), curs_color(bg));
		}
	}

	for (const auto &color : CColors) {
		init_HEX(color);
	}
}

short curs_color(int fg) {
	switch (7 & fg) {			/* RGB */
	case 0:						/* 000 */
		return (COLOR_BLACK);
	case 1:						/* 001 */
		return (COLOR_RED);
	case 2:						/* 010 */
		return (COLOR_GREEN);
	case 3:						/* 011 */
		return (COLOR_YELLOW);
	case 4:						/* 100 */
		return (COLOR_BLUE);
	case 5:						/* 101 */
		return (COLOR_MAGENTA);
	case 6:						/* 110 */
		return (COLOR_CYAN);
	case 7:						/* 111 */
		return (COLOR_WHITE);
	}
	return (COLOR_WHITE);		/* shouldn't happen, but avoids warnings */
}

int colornum(int fg, int bg) {
	int B, bbb, ffff;
	B = 1 << 7;
	bbb = (7 & bg) << 4;
	ffff = 7 & fg;
	return (B | bbb | ffff);
}


void setcolor(int fg, int bg) {
	attron(COLOR_PAIR(colornum(fg, bg)));
	if (is_bold(fg)) {
		attron(A_BOLD);
	}
}

void unsetcolor(int fg, int bg) {
	attroff(COLOR_PAIR(colornum(fg, bg)));
	if (is_bold(fg)) {
		attroff(A_BOLD);
	}
}

void setcolor(WINDOW* win, int fg, int bg) {
	wattron(win, COLOR_PAIR(colornum(fg, bg)));
	if (is_bold(fg)) {
		attron(A_BOLD);
	}
}

void unsetcolor(WINDOW* win, int fg, int bg) {
	wattroff(win, COLOR_PAIR(colornum(fg, bg)));
	if (is_bold(fg)) {
		attroff(A_BOLD);
	}
}

int is_bold(int fg) {
	int i;
	i = 1 << 3;
	return (i & fg);
}

void test_colors() {
	init_colorpairs();

	mvaddstr(0, 35, "COLOR DEMO");
	mvaddstr(1, 35, "This might not work if you are on Windows");
	mvaddstr(2, 0, "low intensity text colors (0-7)");
	mvaddstr(12, 0, "high intensity text colors (8-15)");

	for (int bg = 0; bg <= 7; bg++) {
		for (int fg = 0; fg <= 7; fg++) {
			setcolor(fg, bg);
			mvaddstr(fg + 3, bg * 10, "...test...");
			unsetcolor(fg, bg);
		}

		for (int fg = 8; fg <= 15; fg++) {
			setcolor(fg, bg);
			mvaddstr(fg + 5, bg * 10, "...test...");
			unsetcolor(fg, bg);
		}
	}
	mvaddstr(LINES - 1, 0, "press any key to quit");
	refresh();
}