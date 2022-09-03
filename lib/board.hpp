#pragma once
#include <ncursesw/ncurses.h>
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;

#define PAVE      ' '
#define EMPTY     '.'
#define WATER     '~'
#define MOUNTAIN  '^'
#define PLAYER    '*'

#define WALL_PAIR      1
#define EMPTY_PAIR     1
#define PAVE_PAIR      2
#define MOUNTAIN_PAIR  3
#define PLAYER_PAIR    4



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
	map<string,int> m_colors;
	string m_lastbackground, m_lastforeground;
	

public:
	// Board();
	Board(int screen_height, int screen_width);
	void setupColors();
	int getColor(const string& background, const string& foreground);
	void startColor(const string& background, const string& foreground);
	void endColor();
	void initialize();
	void addBorder();
	void fill();
	void fillPoint(int y, int x);
	void clear();
	void refresh();
	WINDOW* getWin();
};
