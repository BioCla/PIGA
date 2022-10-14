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

void Board::init(){
	double changecolor = 1000/255;
	init_color(PLAYER_FOREGROUND, 255*changecolor, 255*changecolor, 255*changecolor);
	init_color(WALL_FOREGROUND, 100*changecolor, 100*changecolor, 100*changecolor);
	init_color(PAVE_FOREGROUND, 50*changecolor, 50*changecolor, 50*changecolor);
	init_pair(WALL_PAIR, WALL_FOREGROUND, WALL_FOREGROUND);
	init_pair(PAVE_PAIR, PAVE_FOREGROUND, PAVE_FOREGROUND);
	init_pair(PLAYER_PAIR, PLAYER_FOREGROUND, PLAYER_FOREGROUND);
	init_pair(ENEMY_PAIR, COLOR_RED, COLOR_RED);
	init_pair(PROJCTL_PAIR, COLOR_BLACK, COLOR_CYAN);
}

void Board::addBorder(){
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
				mvaddch(fy, fx, WALL);
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
    for (int y = Offset+1; y < yMax-1; y++) {
		attron(COLOR_PAIR(PAVE_PAIR));
        mvhline(y, Offset+1, PAVE, xMax-12);
		attroff(COLOR_PAIR(PAVE_PAIR));
    }  
}

void Board::fillall(){
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);
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
	initscr();	   // Inizializza lo schermo secondo la libreria ncurses
	clear();	   // Svuota il terminale
	noecho();	   // Rimuove l'input inserito nel terminale
	cbreak();	   // Rimuove il buffer di input
	curs_set(0); // Rende il cursore invisibile
	nodelay(stdscr, true);   //altrimenti aspetta sempre l'input dell'utente
	refresh();
	if(has_colors()== FALSE){
		endwin();
		printf("Il tuo terminale non supporta i colori");
		exit(1);
	}
	start_color();
	init();
}

WINDOW* Board::getWin(){
	return board_win;
}