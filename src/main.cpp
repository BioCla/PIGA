#include <ncursesw/ncurses.h>
#include "../lib/board.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../assets/position.hpp"
#include "../lib/enemy.hpp"
#include "../lib/engine.hpp"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#include "../assets/projList.hpp"


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
	
	
	srand(time(NULL));
	int rows, cols;
	resizeterm(20,50);
	getmaxyx(stdscr, rows, cols);

	///////////////////////////////////////////////////////////////////////////

	// Inizializzazione della tavola principale iniziale
	rows=rows-21;
	cols=rows*2.5;
	//Board board(rows, cols);
	Board board(20,20);
	getmaxyx(stdscr, rows, cols);

	


	// Inizializzazione del personaggio principale
	Position character_initial_position;
	character_initial_position.x = getmaxx(stdscr)/2;
	character_initial_position.y = getmaxy(stdscr)/2;
	Character p = Character(character_initial_position.x, character_initial_position.y, "@", 30, "*", 100);
	p.setRoomWin(board.getWin());

	// Posizionamento del personaggio principale nel terminale, posizione relativa da 0,0 (alto sinistra del terminale per adesso)
	p.PlayerMove(character_initial_position.x, character_initial_position.y);


	//DEBUG - prova del proiettile
	Position spawnpoint_projectile;
	spawnpoint_projectile.x = 10; spawnpoint_projectile.y = 10;
	duration <int, std::ratio <1,1000 > > time_interval_projectile(250);
	/*
	Projectile speedygonzales = Projectile("*", spawnpoint_projectile, 1, 250);
	speedygonzales.spawn(speedygonzales.getCurrentPosition());
	
	speedygonzales.setCurrentRoom(board.getWin());

	

		//-- prova character.legalMove()
	

		// /prova character.legalMove()

	

	// prova nemico
	*/
	Position spawnpoint_enemy;
	spawnpoint_enemy.x=20; spawnpoint_enemy.y=20;
	duration <int, std::ratio <1,1000 > > idle_time_enemy(1000);
	Enemy Astolfo = Enemy("A",10,1,spawnpoint_enemy,1,idle_time_enemy);
	Astolfo.spawn(Astolfo.getCurrentPosition());
	Astolfo.setCurrentRoom(board.getWin());

	// / prova nemico
	int debug = 0;
	
	// /DEBUG


	system_clock::time_point time_now = system_clock::now();

	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{

		time_now = system_clock::now();

		p.HandleInput(ch);
		Astolfo.checkIfTimeToMove(time_now);
		speedygonzales.checkIfTimeToMove(time_now);
		refreshProjectiles(p.getProjectilesShot(), time_now);	
		
		

		if(ch=='f') {    //SE VOLETE SPARARE PER PROVARE PREMETE f
			p.shoot();
		}
		else if(ch=='g') {
			
		}
		else if(ch=='t') {
			
			def_prog_mode();
			endwin();
			//apre terminale
			// -- inizia codice --


			//FUNZIONEDEBUG();  
			

			// -- fine codice --
			int inutile;
			cin >> inutile;
			//riapre ncurses
			reset_prog_mode();
			refresh();
 		}


		

		
		p.PlayerMove(p.getCurrentPosition().x,p.getCurrentPosition().y);  //si assicura che il personaggio sia in primo piano
		refresh();
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}
