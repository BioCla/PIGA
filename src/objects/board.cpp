#include "../../include/objects/board.hpp"
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

//----- funzioni delle altre classi

void Board::checkHits(){
	Node<Enemy> *tmp1 = enemiesList.getHead();
	Node<Projectile> *tmp2;
	Node<SuperProjectile> *tmp3;
    while (tmp1!=NULL) {

		tmp2 = projectilesList.getHead();
		tmp3 = superProjectilesList.getHead();

		while(tmp2!=NULL) {
			if ((compare(tmp1->getData()->getCurrentPosition(),tmp2->getData()->getCurrentPosition()))&&(tmp2->getData()->checkifAllied())){
				tmp1->getData()->updateHealth(-tmp2->getData()->getDamage());
				mvwprintw(this->getWin(),2,2,"HIT");
				tmp2->getData()->setAlive(false);
			}
			tmp2=tmp2->getNext();
		}

		while(tmp3!=NULL){
			if ((compare(tmp1->getData()->getCurrentPosition(),tmp3->getData()->getCurrentPosition()))&&(tmp3->getData()->checkifAllied())){
				tmp1->getData()->updateHealth(-tmp3->getData()->getDamage());
			}
			tmp3=tmp3->getNext();
		}
        tmp1=tmp1->getNext();	

	}
}


void Board::generateEnemies(){
	int ne = (rand() % 3) + 4;
	for(int i=0;i<ne;i++){
		int rspeed = (rand()%1000)+300;
		int rshootspeed = rspeed + 200;
		int rpathID = (rand() % 4);
		Position spawnEnemy;
		spawnEnemy.x=(rand()%(BOARD_COLS-2))+1;
		spawnEnemy.y=(rand()%(BOARD_ROWS-2))+1;
		Enemy e = Enemy("A",10,5,spawnEnemy,rpathID,rspeed,rshootspeed,board_win);
		enemiesList.headInsert(e);
	}
	enemiesList.spawnEntities();
}

void Board::generateEnemiesProj(system_clock::time_point time_now){
	Node<Enemy> *tmp = enemiesList.getHead();
    while (tmp!=NULL) {
    	tmp->getData()->checkIfTimeToShoot(time_now,&projectilesList);
        tmp=tmp->getNext();
    }   
}

void Board::refreshEnemies(system_clock::time_point time_now, Position pos){
	enemiesList.refreshEnemyTarget(pos);
	enemiesList.moveEntities(time_now);
	generateEnemiesProj(time_now);
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

List<Item>* Board::getItemsList() {
	return &itemsList;
}

void Board::generateItems() {
	int n_items = rand() % 5 + 25;
	int n_artifacts = 1;
	int id;
	Position spawn_position;

	int i;
	for (i = 0; i < n_artifacts; i++) {
		spawn_position = {(rand()%(BOARD_COLS-3))+1, (rand()%(BOARD_ROWS-3))+1};
		id = 6;
		Item newItem = Item(findItem(id), spawn_position, board_win);
		itemsList.headInsert(newItem);
	}

	for(i = 0; i < n_items; i++) {
		id = rand() % 10;
		while(id == 6) id = rand() % 10;   //non deve generare artefatti
		spawn_position = {(rand()%(BOARD_COLS-2))+1, (rand()%(BOARD_ROWS-2))+1};
		Item newItem = Item(findItem(id), spawn_position, board_win);
		itemsList.headInsert(newItem);
	}

}

//ritorna il valore in numero da aggiungere alla vita del personaggio
//in caso di artefatti faremo partire il metodo della board che sblocca la porta senza ritornare niente

void Board::checkItemCollisions(Character *p) {
	Node<Item> *tmp = itemsList.getHead();
	int itemID = 11;

	while(tmp != NULL) {
		if(compare(p->getCurrentPosition(), tmp->getData()->getCurrentPosition())) {
			tmp->getData()->setAlive(false);
			
			itemID = tmp->getData()->getProperties().ID;
			switch(itemID) {
				case 0:
					p->setMaxHealth(p->getMaxHealth() + 1);
					break;
				case 1:
					p->setDamage(p->getDamage() + 3);
					break;
				case 2:
					if(p->getProjectileMovingFrequency() > 10) {
						p->setProjectileMovingFrequency(p->getProjectileMovingFrequency() - 10);
					}
					break;
				case 3:
					if(p->getMaxHealth() > 1) {
						p->setMaxHealth(p->getMaxHealth() - 1);
					}
					break;
				case 4:
					if(p->getDamage() > 1) {
						p->setDamage(p->getDamage() - 1);
					}
					break;
				case 5:
					p->setProjectileMovingFrequency(p->getProjectileMovingFrequency() + 10);
					break;
				case 6:
					//apriPorte();
					break;
				case 7:
					p->addToInventory(itemID);
					break;
				case 8:
					p->addToInventory(itemID);
					break;
				case 9:
					p->updateHealth(+10);
					break;
				case 10:
					//Misc
					break;
				case 11:
					//default
					break;
				
				default:
					break;
			}
		}
		tmp = tmp->getNext();
	}

	
}



