#include "../../include/_init/game_board.hpp"
#include "../../include/util/curses_color_pairing.hpp"

#define TBHEIGHT 3

Board::Board() {
	init();
	draw();
}

void Board::init() {
	/* Init */
	info_window = newwin(TBHEIGHT, getmaxx(stdscr), 0, 0);
	status_window = newwin(TBHEIGHT, getmaxx(stdscr), getmaxy(stdscr) - TBHEIGHT, 0);
	game_window = newwin(getmaxy(stdscr) - (TBHEIGHT * 2), getmaxx(stdscr), TBHEIGHT, 0);

	/* Background */
	wbkgd(info_window, COLOR_PAIR(colornum(COLOR_BLACK, COLOR_WHITE)));
	wbkgd(game_window, COLOR_PAIR(colornum(COLOR_WHITE, COLOR_BLACK)));
	wbkgd(status_window, COLOR_PAIR(colornum(COLOR_BLACK, COLOR_WHITE)));
}

void Board::draw() {
	box(info_window, 0, 0);
	box(game_window, 0, 0);
	box(status_window, 0, 0);
	// Refresh all windows
	wrefresh(info_window);
	wrefresh(game_window);
	wrefresh(status_window);
}