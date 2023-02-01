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
	int screen_height, screen_width, xMin, yMin, xMax, yMax;
	int level_number;
	bool door_unlocked;

	//questi campi ignorali tranquillamente
	//sono solo cose che usano altre classi e vengono salvate nella stanza
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


	//funzioni dei campi che puoi ignorare
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

	//ATTENZIONE: la funzione cambiaStanza() deve avere nei parametri un puntatore al personaggio, perchè vanno cambiati i puntatori alle liste dei proiettili (e la current_room_win)
};