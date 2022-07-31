#include <ncursesw/ncurses.h>


int main(int argc, char **argv) {
    initscr();
    printw("Heldddlo World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();	


    return 0;
}