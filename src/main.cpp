#include "../assets/hch.h"
#include "../lib/board.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../lib/superProjectile.hpp"
#include "../assets/position.hpp"
#include "../lib/enemy.hpp"
#include "../lib/engine.hpp"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#include "../assets/projList.hpp"
#include "../assets/superProjList.hpp"

#include "../lib/entity.hpp"


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
	if(has_colors()== FALSE){
		endwin();
		printf("Il tuo terminale non supporta i colori");
		exit(1);
	}
	start_color();


	///////////////////////////////////////////////////////////////////////////

	// Inizializzazione della tavola principale iniziale
	//Board board(rows, cols);
	
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);
	/*while(yMax>50 && xMax >200){
		mvprintw(yMax/2, xMax/2, "rimpicciolisci il terminale");
	}
	while(yMax<30 && xMax >\){
		mvprintw(yMax/2, xMax/2, "rimpicciolisci il terminale");
	}*/
	
	Board board(BOARD_ROWS, BOARD_COLS);
	WINDOW* schermoliam = newwin(50, 211, (yMax / 2) - (50/2), (xMax / 2) - ((211/2)));
	box(schermoliam, 1, 1);
	wrefresh(schermoliam);
	box(board.getWin(), 0, 0);
	wrefresh(board.getWin());	


	// Inizializzazione del personaggio principale
	Position character_initial_position;
	character_initial_position.x = 5;
	character_initial_position.y = 5;
	Character p = Character(character_initial_position.x, character_initial_position.y, "@", 30, "*", 100);
	p.setRoomWin(board.getWin());

	// Posizionamento del personaggio principale nel terminale, posizione relativa da 0,0 (alto sinistra del terminale per adesso)
	p.move(character_initial_position.x, character_initial_position.y);



	//DEBUG - prova del proiettile
	/*
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
	mvaddch(25, 80, 35);*/
	//mvaddch(1, 2, 35);     //se attivi questo il proiettile buggato "spawna" e si distrugge subito dopo. è una nonsoluzione diciamo
	//toglieteli pure tutti se danno fastidio
	//li ho messi perchè i # del addborder della board non li prende per qualche motivo, servono solo per debuggare

		//test superproiettile
	
	SuperProjectile thiccboi = SuperProjectile("O", {3,5}, DIR_EAST, 200, 1000, 100, "'", board.getWin());
	superProjList* superProjListHead = new superProjList;
	superProjListHead->sproj = thiccboi;
	superProjListHead->next = NULL;

	Projectile speedygonzales = Projectile("s", {6,6}, DIR_EAST, 100, p.getWin());
	projList* projlistdebug = new projList;
	projlistdebug->next = p.getProjectilesShot();
	projlistdebug->proj = speedygonzales;
	p.settanuovahead(projlistdebug);

	
		// test getposiion entity
		Entity puppet = Entity("E", {9, 9}, board.getWin());
		puppet.spawn();
		puppet.setIcon("a");
			

	//projList** tempProjListForRefreshingSuperProjectiles = new projList*;
	//*tempProjListForRefreshingSuperProjectiles = p.getProjectilesShot();
		// / test superproiettile
	

		

	

	// prova nemico
	
	Position spawnpoint_enemy;
	spawnpoint_enemy.x=15; spawnpoint_enemy.y=15;
	duration <int, std::ratio <1,1000 > > idle_time_enemy(1000);
	Enemy Astolfo = Enemy("A",10,1,spawnpoint_enemy,1,idle_time_enemy);
	Astolfo.setCurrentRoom(board.getWin());
	Astolfo.spawn(Astolfo.getCurrentPosition());
	

	// / prova nemico

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
		
		refreshSuperProjectiles(superProjListHead, time_now, p.getProjectilesShot());
		refreshProjectiles(p.getProjectilesShot(), time_now);
		
		
		mvaddch(6, 6, speedygonzales.getCurrentPosition().x); mvaddch(7, 6, speedygonzales.getCurrentPosition().y); 
		refresh();
		
		
		
		

		if(ch == 'f') {    //SE VOLETE SPARARE PER PROVARE PREMETE f
			p.shoot();
		}
		else if(ch=='g') {
			SuperProjectile newProjectile = SuperProjectile("O", p.getCurrentPosition(), p.getLastDirection(),
															100, 800, 100, "'", p.getWin());
			superProjList *newproj = new superProjList;
			newproj->sproj = newProjectile;
			newproj->next = superProjListHead;
			superProjListHead = newproj;
			superProjListHead->sproj.move();
			(*p.getProjectilesShot()).proj.move();
		}

		else if(ch == 'h') {
			int dirsdebug[2];
			thiccboi.getSpawningDirections(dirsdebug);
			p.settanuovahead( createProjectile2(p.getProjectilesShot(), "*", thiccboi.getCurrentPosition(), dirsdebug[0], 
			p.getProjectileMovingFrequency(), p.getWin()) );

			p.settanuovahead( createProjectile2(p.getProjectilesShot(), "*", thiccboi.getCurrentPosition(), dirsdebug[1], 
			p.getProjectileMovingFrequency(), p.getWin()) );


			puppet.move(puppet.getCurrentPosition().x + 1, puppet.getCurrentPosition().y);

			
			
		}
		
		else if(ch=='t') {   //serve solo per il debug

			def_prog_mode();
			endwin();
			//apre terminale
			// -- inizia codice --


			//FUNZIONEDEBUG(); 
			cout << "posizione x,y personaggio: " << p.getCurrentPosition().x << ", " << p.getCurrentPosition().y << endl;
			cout << "posizione x,y speedygonzales: " << speedygonzales.getCurrentPosition().x << ", " << speedygonzales.getCurrentPosition().y << endl;
			cout << "posizione x,y nemico: " << Astolfo.getCurrentPosition().x << ", " << Astolfo.getCurrentPosition().y << endl;
			cout << "posizione x,y del superproiettile: " << thiccboi.getCurrentPosition().x << ", " << thiccboi.getCurrentPosition().y << endl;
			cout << "posizione x,y dell' Entity: " << puppet.getCurrentPosition().x << ", " << puppet.getCurrentPosition().y << endl;
			

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


		

		
		p.move(p.getCurrentPosition().x,p.getCurrentPosition().y);  //si assicura che il personaggio sia in primo piano
		refresh();
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}


