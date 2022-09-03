#pragma once
#include <ncursesw/ncurses.h>
#include <string>
#include <map>
using namespace std;

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
	void clear();
	void refresh();
	WINDOW* getWin();
};
