#pragma once
#include <ncursesw/ncurses.h>
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;

#define WALL      '#'
#define PAVE      ' '
#define PLAYER    '@'
#define ROCK      '^'


#define WALL_PAIR      1
#define PAVE_PAIR      2
#define PLAYER_PAIR    3
#define ROCK_PAIR      4




/**
 * Author:
 * Co:
 *
 * Description:
 *
 */
class Board
{
protected:
	WINDOW *board_win;
	int screen_height, screen_width;
	

public:
	// Board();
	Board(int screen_height, int screen_width);
	void initialize();
	void addBorder();
	void fill();
	void fillPoint(int y, int x);
	void clear();
	void refresh();
	void init();
	WINDOW* getWin();
};
