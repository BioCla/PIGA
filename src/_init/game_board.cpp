#include "../../include/_init/game_board.hpp"
#include "../../include/util/curses_color_pairing.hpp"

Board::Board() {
	init();
	draw();
}

void Board::init() {
	info_window = newwin(1, getmaxx(stdscr), 0, 0);
	wbkgd(info_window, COLOR_PAIR(colornum(COLOR_BLACK, COLOR_WHITE)));
	// -2 is for the info and status windows (above and below the game window)
	game_window = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr), 1, 0);
	wbkgd(game_window, COLOR_PAIR(colornum(COLOR_WHITE, COLOR_BLACK)));
	status_window = newwin(1, getmaxx(stdscr), getmaxy(stdscr) - 1, 0);
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