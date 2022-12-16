#include "../../include/_init/game_board.hpp"

GameBoard::GameBoard() {
	info_window = NULL;
	game_window = NULL;
	status_window = NULL;
}

void GameBoard::init() {
	// il -2 serve per lasciare spazio alla finestra dello stato e alla finestra delle info (sopra e sotto)
	info_window = newwin(1, getmaxx(stdscr), 0, 0);
	game_window = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr), 1, 0);
	status_window = newwin(1, getmaxx(stdscr), getmaxy(stdscr) - 1, 0);
}

void GameBoard::draw() {
	box(info_window, 0, 0);
	box(game_window, 0, 0);
	box(status_window, 0, 0);
	// Aggiorna le finestre
	wrefresh(info_window);
	wrefresh(game_window);
	wrefresh(status_window);
}

WINDOW* GameBoard::getInfoWindow() {
	return info_window;
}

WINDOW* GameBoard::getGameWindow() {
	return game_window;
}

WINDOW* GameBoard::getStatusWindow() {
	return status_window;
}