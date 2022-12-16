#include "../../include/_init/game_board.hpp"

Board::Board() {
	init();
	draw();
}

void Board::init() {
	// il -2 serve per lasciare spazio alla finestra dello stato e alla finestra delle info (sopra e sotto)
	info_window = newwin(1, getmaxx(stdscr), 0, 0);
	_window = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr), 1, 0);
	status_window = newwin(1, getmaxx(stdscr), getmaxy(stdscr) - 1, 0);
}

void Board::draw() {
	box(info_window, 0, 0);
	box(_window, 0, 0);
	box(status_window, 0, 0);
	// Aggiorna le finestre
	wrefresh(info_window);
	wrefresh(_window);
	wrefresh(status_window);
}