#include <ncursesw/ncurses.h>
#include "../lib/board.hpp"
#include "../lib/character.hpp"

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

/**
 * Main function file, runner of the program
 * Executes the primary initialiazation functions for the ncurses library and sets up the game
 * with board components and gameplay features
 */
int main(int argc, char **argv)
{

	// Questo dovra' andare in una funzione separate prima o poi:

	initscr();	   // Inizializza lo schermo secondo la libreria ncurses
	start_color(); // Permette l'utilizzo di colori sullo schermo
	clear();	   // Svuota il terminale
	noecho();	   // Rimuove l'input inserito nel terminale
	cbreak();	   // Rimuove il buffer di input
	// keypad(stdscr, TRUE); //Abilita i tasti di funzione (Fn, frecce, etc...)
	curs_set(0); // Rende il cursore invisibile
	refresh();

	///////////////////////////////////////////////////////////////////////////

	Board board(BOARD_ROWS, BOARD_COLS);
	getch();
	endwin();
	return 0;
}
