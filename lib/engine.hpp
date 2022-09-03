#include <ncursesw/ncurses.h>

#define EMPTY ' '

// '_' ' ' '\' '/'
#define UNDERSCORE_COLOR_PAIR	2
#define SPACE_COLOR_PAIR 		3
#define BS_COLOR_PAIR 			4
#define FS_COLOR_PAIR 			5

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