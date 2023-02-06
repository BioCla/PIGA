#pragma once
#include "../assets/hch.h"
#include "../util/engine.hpp"
#include "superProjectile.hpp"
#include "enemy.hpp"
#include "item.hpp"
//#include "../assets/itemLists.hpp"
#include "character.hpp"
#include "../util/listUtils.hpp"
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;


class Board
{
protected:
	WINDOW *board_win;
	int screen_height, screen_width, xMin, yMin, xMax, yMax;
	int level_number;
	bool door_unlocked;

	
	// --------------------
	//liste di altri oggetti, presenti nella singola stanza
	List<Projectile> projectilesList;
	List<SuperProjectile> superProjectilesList;
	List<Enemy> enemiesList;
	List<Item> itemsList;
	
public:
	Board();
	Board(int screen_height, int screen_width, int level_number);
	void initialize();
	void addBorder();
	void fill();
	void fillall();
	void fillPoint(int y, int x);
	void addDoors();
	void openDoors();   //apre le porte a destra
	bool getDoorLockState();
	void clear();
	void init();
	WINDOW* getWin();
	void checkColor();


	//  ---------------------
	//funzioni riguardanti gli ultimi campi della classe Board
	void checkHits();
	void refreshEnemies(system_clock::time_point time_now, Position pos);
	void generateEnemies();
	void generateEnemiesProj(system_clock::time_point time_now);
	List<Projectile>* getProjectilesList();
	List<SuperProjectile>* getSuperProjectilesList();
	List<Enemy>* getEnemiesList();
	List<Item>* getItemsList();
	void generateItems();
	void checkItemCollisions(Character *p);

	int getLevelNumber();

};
