#include "../../include/_init/game_board.hpp"

GameBoard::GameBoard() {
	game_window = NULL;
}

WINDOW* GameBoard::init() {
	game_window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
	return game_window;
}

void GameBoard::draw() {
	werase(game_window);
	box(game_window, 0, 0);
	wrefresh(game_window);
}