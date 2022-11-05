#include "../assets/hch.h"

#include "../assets/projList.hpp"
#include "../assets/superProjList.hpp"

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
void refreshProjectiles(projList* head, system_clock::time_point time_now);
int FUNZIONEDEBUG(projList* projectiles, system_clock::time_point time_now);
void ELIMINATESTA(projList* head);
void refreshSuperProjectiles(superProjList* head, system_clock::time_point time_now, projList* projListHead);
projList* createProjectile2(projList* projListHead, const char* icon, Position position, int direction, int moving_frequency, WINDOW* win);