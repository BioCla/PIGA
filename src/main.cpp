#include "../assets/hch.h"
#include "../lib/board.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
//#include "../lib/superProjectile.hpp"
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


int main(int argc, char **argv)
{

	// Questo dovra' andare in una funzione separate prima o poi:
	
	 // Permette l'utilizzo di colori sullo schermo
	
	initscr();
	refresh();
	srand(time(NULL));


	///////////////////////////////////////////////////////////////////////////

	// Inizializzazione della tavola principale iniziale
	//Board board(rows, cols);
	
	Board board(BOARD_ROWS, BOARD_COLS);
	int xMax, yMax;
	getmaxyx(stdscr,yMax,xMax);
	cout<<yMax<<endl; //84
	cout<<xMax<<endl; //237


	


	// Inizializzazione del personaggio principale
	Position character_initial_position;
	character_initial_position.x = getmaxx(board.getWin())/2;
	character_initial_position.y = getmaxy(board.getWin())/2+2;
	Character p = Character(character_initial_position.x, character_initial_position.y, "@", 30, "*", 100);
	p.setRoomWin(board.getWin());

	// Posizionamento del personaggio principale nel terminale, posizione relativa da 0,0 (alto sinistra del terminale per adesso)
	p.PlayerMove(character_initial_position.x, character_initial_position.y);


	//DEBUG - prova del proiettile
	
	mvaddch(25, 120, 35);
	mvaddch(26, 120, 35);
	mvaddch(27, 120, 35);
	mvaddch(28, 120, 35);
	mvaddch(29, 120, 35);
	mvaddch(30, 120, 35);
	mvaddch(31, 120, 35);
	mvaddch(32, 120, 35);
	mvaddch(25, 119, 35);
	mvaddch(25, 118, 35);
	mvaddch(25, 117, 35);
	mvaddch(25, 116, 35);
	mvaddch(25, 115, 35);
	mvaddch(25, 114, 35);
	mvaddch(25, 113, 35);
	mvaddch(25, 112, 35);
	mvaddch(25, 111, 35);
	mvaddch(25, 110, 35);
	mvaddch(25, 109, 35);
	mvaddch(25, 80, 35);
	//mvaddch(1, 2, 35);     //se attivi questo il proiettile buggato "spawna" e si distrugge subito dopo. è una nonsoluzione diciamo
	//toglieteli pure tutti se danno fastidio
	//li ho messi perchè i # del addborder della board non li prende per qualche motivo, servono solo per debuggare
	

		

	

	// prova nemico
	
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
	int stdscrxmax, stdscrymax;
	getmaxyx(stdscr, stdscrymax, stdscrxmax);

	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{

		time_now = system_clock::now();

		p.HandleInput(ch);
		Astolfo.checkIfTimeToMove(time_now);
		
		refreshProjectiles(p.getProjectilesShot(), time_now);	

		//debug = FUNZIONEDEBUG(p.getProjectilesShot(), time_now);
		//mvaddch(5, 5, debug);
		
		

		if(ch == 'f') {    //SE VOLETE SPARARE PER PROVARE PREMETE f
			p.shoot();
		}
		else if(ch=='g') {
			//SuperProjectile MEGASPEEDYGONZALES = SuperProjectile("*", p.getCurrentPosition(), p.getLastDirection(), 100, 1000, 0, 100);
			//DA FINIRE
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
		
		//PAUSA
		else if(ch == 'p') {
			ch = 'h'; //lettera a caso, basta che sia diversa da p
			mvprintw(stdscrymax - 5, stdscrxmax/2 - 4, "**PAUSA**");
			while(ch != 'p') {
				ch = getch();
				//beh nulla? coi menu diventerà un po' più complesso
			}
			mvprintw(stdscrymax - 5, stdscrxmax/2 - 4, "         ");
		}


		

		
		p.PlayerMove(p.getCurrentPosition().x,p.getCurrentPosition().y);  //si assicura che il personaggio sia in primo piano
		refresh();
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}


