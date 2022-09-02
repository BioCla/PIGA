#include <ncursesw/ncurses.h>
#include "../lib/board.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../assets/position.hpp"

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
	p.PlayerMove(getmaxx(stdscr)/2, getmaxy(stdscr)/2);


	//DEBUG - prova del proiettile
	Position spawnpoint_projectile;
	spawnpoint_projectile.x = 10; spawnpoint_projectile.y = 10;
	duration <int, std::ratio <1,1000 > > time_interval_projectile(250);
	Projectile speedygonzales = Projectile("*", spawnpoint_projectile, 1, time_interval_projectile);
	speedygonzales.spawn(stdscr, speedygonzales.getCurrentPosition());



	// /DEBUG

	system_clock::time_point time_now = system_clock::now();
	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{
		p.HandleInput(ch);
		
		if(ch == 'f') {
			time_now = system_clock::now();
			speedygonzales.checkIfTimeToMove(time_now);
		}
		refresh();
		mvwprintw(p.getWin(), 0, 0, p.getIcon());
		wrefresh(p.getWin());
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}
