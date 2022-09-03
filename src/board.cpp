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
	init_pair(WALL_PAIR, COLOR_BLUE, COLOR_BLUE);
	attron(COLOR_PAIR(WALL_PAIR));
	for(int fy = Offset; fy < yMax; fy++){
		for(int fx = Offset; fx < xMax; fx++){
			if(fx == Offset || fy == Offset || fx == xMax-1 || fy == yMax-1){				
				mvprintw(fy, fx, fence.c_str());
			}			
		}
	}
	attroff(COLOR_PAIR(WALL_PAIR));
	fill();
}

void Board::fill(){
	int xMax,yMax;
	getmaxyx(stdscr,yMax,xMax);
	int Offset=5;
	xMax=xMax;
	yMax=yMax-Offset;
	init_pair(PAVE_PAIR, COLOR_CYAN, COLOR_CYAN);
    for (int y = Offset+1; y < yMax-1; y++) {
		attron(COLOR_PAIR(PAVE_PAIR));
        mvhline(y, Offset+1, PAVE, xMax-12);
		attroff(COLOR_PAIR(PAVE_PAIR));
    }  
}

void Board::fillPoint(int y, int x){
	attron(COLOR_PAIR(PAVE_PAIR));
	mvaddch(y, x, PAVE);
	attroff(COLOR_PAIR(PAVE_PAIR));
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