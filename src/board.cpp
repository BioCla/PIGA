#include "../lib/board.hpp"
#include <iostream>
using namespace std;


/*Board::Board(){ 
	int xMax, yMax;
	int height=10;
	int width=20;

	getmaxyx(stdscr, yMax, xMax);
	board_win = newwin(height, width, (yMax/2)-(height/2), (xMax/2)-(width/2));
	initialize();
}*/

Board::Board(int screen_height, int screen_width){
	this->screen_height = screen_height;
	this->screen_width = screen_width;
	getmaxyx(stdscr, yMax, xMax);
	board_win = newwin(screen_height, screen_width, (yMax / 2) - (screen_height/2), (xMax / 2) - ((screen_width/2)));
	getbegyx(board_win, yMin, xMin);
	getmaxyx(board_win, yMax, xMax);
	initialize();
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
	init_pair(PROJCTL_PAIR, PLAYER_FOREGROUND, PAVE_FOREGROUND);
}

void Board::addBorder(){
	wattron(board_win, COLOR_PAIR(WALL_PAIR));
	for(int fy = 0; fy <= yMax; fy++){
		for(int fx = 0; fx <= xMax; fx++){
			if(fx == 0 || fy == 0 || fx == xMax-1|| fy == yMax-1){ //è +2 per il numero massimo perchè si conta 2 volte l'errore relativo alla window				
				mvwaddch(board_win, fy, fx, WALL);
			}			
		}
	}
	wattroff(board_win, COLOR_PAIR(WALL_PAIR));
	fill();
}


void Board::fill(){
	wattron(board_win, COLOR_PAIR(PAVE_PAIR));
    for (int fy = 1; fy < yMax-1; fy++) {
			mvwhline(board_win, fy, 1, PAVE, xMax-2);	
    }  
	wattroff(board_win, COLOR_PAIR(PAVE_PAIR));
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
	//wclear(board_win);
	addBorder();
	//box(board_win, 0, 0);

}

void Board::checkColor(){
	init();
}

void Board::initialize(){
	noecho();	   // Rimuove l'input inserito nel terminale
	cbreak();	   // Rimuove il buffer di input
	curs_set(0); // Rende il cursore invisibile
	nodelay(stdscr, true);   //altrimenti aspetta sempre l'input dell'utente
	checkColor();
	clear();	   // Svuota il terminale
	wrefresh(board_win);
}

WINDOW* Board::getWin(){
	return board_win;
}

//----- roba delle altre classi

void Board::generateEnemies(){
	int ne = (rand() % 3) + 4;
	for(int i=0;i<ne;i++){
		int rs = (rand()%1000)+300;
		int rp = (rand() % 3);
		Position spawnEnemy;
		spawnEnemy.x=(rand()%(BOARD_COLS-1))+1;
		spawnEnemy.y=(rand()%(BOARD_ROWS-1))+1;
		Enemy e = Enemy("A",10,5,spawnEnemy,rp,rs,board_win);
		enemiesList.headInsert(e);
	}
	enemiesList.spawnEnemies();
}

void Board::refreshEnemies(system_clock::time_point time_now){
	enemiesList.moveEntities(time_now);
	enemiesList.enemyShooting(time_now);
	enemiesList.removeDeadEntities();
}


List<Projectile>* Board::getProjectilesList() {
	return &projectilesList;
}

List<SuperProjectile>* Board::getSuperProjectilesList() {
	return &superProjectilesList;
}

List<Enemy>* Board::getEnemiesList(){
	return &enemiesList;
}