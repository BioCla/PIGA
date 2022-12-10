#pragma once
#include "../assets/hch.h"
#include "superProjectile.hpp"
#include "enemy.hpp"
#include "item.hpp"
#include "listUtils.hpp"
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;


#define BOARD_DIM 35
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS (int)(BOARD_ROWS * 2.5)

#define WALL      '#'
#define PAVE      ' '
#define PLAYER    '@'
#define ROCK      '^'
#define ENEMY     'A'
#define PROJCTL   '*'




#define WALL_PAIR      1
#define PAVE_PAIR      2
#define PLAYER_PAIR    3
#define ROCK_PAIR      4
#define ENEMY_PAIR 	   5
#define PROJCTL_PAIR   6
#define PAVE_FOREGROUND 7
#define WALL_FOREGROUND 8
#define PLAYER_FOREGROUND 9
#define ALL_FOREGROUND 10



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

	//questi campi ignorali tranquillamente
	//sono solo cose che usano altre classi e vengono salvate nella stanza
	List<Projectile> projectilesList;
	List<SuperProjectile> superProjectilesList;
	List<Enemy> enemiesList;
	List<Item> itemList;
	
public:
	// Board();
	Board(int screen_height, int screen_width);
	void initialize();
	void addBorder();
	void fill();
	void fillall();
	void fillPoint(int y, int x);
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
	List<Item>* getItemList();
	void generateItems();
	int checkItemCollisions(Position character_position);
	ItemType convertItemIconToType(int posx, int posy);
};
