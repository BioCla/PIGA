#include <ncursesw/ncurses.h>


int main(int argc, char **argv) {
    initscr();
    printw("Hello World !!!");	/* Print Hello World		  */

    WINDOW myWin;

    


    box(stdscr, 0, 0);


	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();	


    return 0;
}