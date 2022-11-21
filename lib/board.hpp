#pragma once
#include "../assets/hch.h"
#include "superProjectile.hpp"
#include "listUtils.hpp"
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;


#define BOARD_DIM 35
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_ROWS * 2.5

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

	List<Projectile> projectilesList;
	List<SuperProjectile> superProjectilesList;
	
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

	List<Projectile>* getProjectilesList();
	List<SuperProjectile>* getSuperProjectilesList();
};
