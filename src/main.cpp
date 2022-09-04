#include <ncursesw/ncurses.h>
#include "../lib/board.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../assets/position.hpp"
#include "../lib/enemy.hpp"
#include <stdlib.h>

#include <iostream>
using namespace std;


/*#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5
*/

/**
 * Main function file, runner of the program
 * Executes the primary initialiazation functions for the ncurses library and sets up the game
 * with board components and gameplay features
 */
int main(int argc, char **argv)
{

	// Questo dovra' andare in una funzione separate prima o poi:
	
	 // Permette l'utilizzo di colori sullo schermo
	
	

	int rows, cols;
	getmaxyx(stdscr, rows, cols);

	///////////////////////////////////////////////////////////////////////////

	// Inizializzazione della tavola principale iniziale
	rows=rows-21;
	cols=rows*2.5;
	Board board(rows, cols);
	getmaxyx(stdscr, rows, cols);

	


	// Inizializzazione del personaggio principale
	Character p = Character();
	p.setRoomWin(board.getWin());

	// Posizionamento del personaggio principale nel terminale, posizione relativa da 0,0 (alto sinistra del terminale per adesso)
	p.PlayerMove(getmaxx(stdscr)/2, getmaxy(stdscr)/2);


	//DEBUG - prova del proiettile
	Position spawnpoint_projectile;
	spawnpoint_projectile.x = 20; spawnpoint_projectile.y = 20;
	duration <int, std::ratio <1,1000 > > time_interval_projectile(250);
	Projectile speedygonzales = Projectile("*", spawnpoint_projectile, 1, time_interval_projectile);
	speedygonzales.spawn(speedygonzales.getCurrentPosition());

	Projectile pr1 = Projectile("?", {12, 12}, 1, time_interval_projectile*2);
	Projectile pr2 = Projectile("!", {15, 4}, 1, time_interval_projectile/4);

	bool pr1alive = false;
	bool pr2alive = false;
	bool prxalive = false;

	Projectile *prx = NULL;

	speedygonzales.setCurrentRoom(board.getWin());
	pr1.setCurrentRoom(board.getWin());
	pr2.setCurrentRoom(board.getWin());

		//-- prova character.legalMove()
	

		// /prova character.legalMove()

	

	// prova nemico
	Position spawnpoint_enemy;
	spawnpoint_enemy.x=20; spawnpoint_enemy.y=20;
	duration <int, std::ratio <1,1000 > > idle_time_enemy(250);
	Enemy Astolfo = Enemy("A",10,1,spawnpoint_enemy,1,idle_time_enemy);
	Astolfo.spawn(stdscr, Astolfo.getCurrentPosition());
	Astolfo.setCurrentRoom(board.getWin());

	// /DEBUG


	system_clock::time_point time_now = system_clock::now();
	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{
		p.HandleInput(ch);
		
		time_now = system_clock::now();
		speedygonzales.checkIfTimeToMove(time_now);

		if(ch=='f') {
			pr1.setPosition(p.getCurrentPosition());
			pr1.spawn(p.getCurrentPosition());
			pr1alive = true;
		}
		else if(ch=='g') {	
			prx = new Projectile(";", p.getCurrentPosition(), p.getLastDirection(), time_interval_projectile/4);
			prx->spawn(prx->getCurrentPosition());
			prxalive = true;
		}
		else if(ch=='t') {
			int stampa_debug = mvwinch(board.getWin(), 0, 2) & A_CHARTEXT;
			def_prog_mode();
			endwin();
			//apre terminale
			// -- inizia codice --
			cout << "last direction: " << p.getLastDirection() << endl;

			// -- fine codice --
			int inutile;
			cin >> inutile;
			//riapre ncurses
			reset_prog_mode();
			refresh();
 		}

		if(pr1alive) pr1.checkIfTimeToMove(time_now);
		if(prxalive) prx->checkIfTimeToMove(time_now);


		
		p.PlayerMove(p.getCurrentPosition().x,p.getCurrentPosition().y);  //si assicura che il personaggio sia in primo piano
		refresh();
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}
