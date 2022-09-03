#pragma once
#include <ncursesw/ncurses.h>

/**
 * Author:
 * Co:
 *
 * Description:
 *
 */
class Board
{
private:
	WINDOW *board_win;
	int screen_height, screen_width;

public:
	// Board();
	Board(int screen_height, int screen_width);
	void initialize();
	void addBorder();
	void clear();
	void refresh();
	WINDOW* getWin();
};
