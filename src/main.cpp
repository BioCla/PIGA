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

	// Inizializzazione della tavola principale iniziale
	Board board(BOARD_ROWS, BOARD_COLS);

	// Inizializzazione del personaggio principale
	Character p = Character();

	// Posizionamento del personaggio principale nel terminale, posizione relativa da 0,0 (alto sinistra del terminale per adesso)
	p.PlayerMove(10, 10);

	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{
		p.HandleInput(ch);
		refresh();
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}
