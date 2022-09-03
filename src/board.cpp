#include "../lib/board.hpp"

/*Board::Board(){
	int xMax, yMax;
	int height=10;
	int width=20;

	getmaxyx(stdscr, yMax, xMax);
	board_win = newwin(height, width, (yMax/2)-(height/2), (xMax/2)-(width/2));
	initialize();
}*/

Board::Board(int screen_height, int screen_width){
	int xMax, yMax;
	
	getmaxyx(stdscr, yMax, xMax);
	board_win = newwin(screen_height, screen_width, (yMax / 2) - (screen_height / 2), (xMax / 2) - (screen_width / 2));
	initialize();
}

void Board::refresh(){
	wrefresh(board_win);
}

void Board::addBorder(){
	string fence = "#";
	int xMax, yMax, Offset;
	getmaxyx(stdscr, yMax, xMax);
	Offset=5;
	xMax=xMax-Offset;
	yMax=yMax-Offset;
	for(int fy = Offset; fy < yMax; fy++){
		for(int fx = Offset; fx < xMax; fx++){
			if(fx == Offset || fy == Offset || fx == xMax-1 || fy == yMax-1){
				startColor("green", "green");
				mvprintw(fy, fx, fence.c_str());
				endColor();
			}			
		}
	}
}

void Board::setupColors(){
	/*Black = 0, Red = 1, Green = 2, Yellow = 3, Blue = 4, Magenta = 5, Cyan = 6, White = 7*/
	string colorNames[] = {
		"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"
	};
	int counter = 0;
	for (int fg = 0; fg < 8; fg++){
		for (int bg = 0; fg < 8; bg ++){
			string colorName = colorNames[bg] + "-" + colorNames[fg];
			init_pair(counter, fg, bg);
			m_colors[colorName] = counter;
			counter++;
		}
	}
}

int Board::getColor(const string& background, const string& foreground){
	string colorName = background + "-" + foreground;
	return m_colors[colorName];
}

void Board::startColor(const string& background, const string& foreground){
	if(m_lastbackground != ""){
		endColor();
	}
	m_lastbackground = background;
	m_lastforeground = foreground;
	attron(COLOR_PAIR(getColor(background, foreground)));
}

void Board::endColor(){
	attroff(COLOR_PAIR(getColor(m_lastbackground, m_lastforeground)));
	m_lastbackground = "";
	m_lastforeground = "";
}

void Board::clear(){
	wclear(board_win);
	addBorder();
}

void Board::initialize(){
	clear();
	refresh();
}

WINDOW* Board::getWin(){
	return board_win;
}