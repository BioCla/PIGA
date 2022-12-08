#ifndef ENGINE
#define ENGINE

#include "../assets/hch.h"
#include "superProjectile.hpp"
#include "listUtils.hpp"
#include <chrono>

#define EMPTY ' '

// '_' ' ' '\' '/'
#define UNDERSCORE_COLOR_PAIR	2
#define SPACE_COLOR_PAIR 		3
#define BS_COLOR_PAIR 			4
#define FS_COLOR_PAIR 			5

#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3

void init();
void end();
void centering_text(WINDOW *terminal, int first_row, const char *string);
void rectangle(int y1, int x1, int y2, int x2);
void welcome();
void empty();
void erase(int y, int x);
void werase(WINDOW *terminal, int y, int x);
void corners(WINDOW *room);
WINDOW *alert(const char *string);
chtype getcharat(int y, int x);
int legalMove(int y, int x);
void refreshSuperProjectiles(std::chrono::_V2::system_clock::time_point time_now, List<SuperProjectile> *superProjectilesList, List<Projectile> *projectilesList);
void createSuperProjectile(List<SuperProjectile> *superProjectilesList,
                            const char* icon, Position position, int direction, int damage, int moving_frequency, int spawning_frequency, 
                            int child_moving_frequency, const char* child_icon, WINDOW* win);

void mvwprintwInteger(WINDOW* win, int posy, int posx, int input);
void displayCharacterHealth(WINDOW* win, int health, int num_hearts);
int checkIfCharacterIsHit(List<Projectile>* projectilesList, List<SuperProjectile>* superProjectilesList, Position character_position);

#endif