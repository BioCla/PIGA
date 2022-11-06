#include "../assets/hch.h"
#include "../lib/board.hpp"
#include "../lib/entity.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../lib/superProjectile.hpp"
#include "../assets/position.hpp"
#include "../lib/enemy.hpp"
#include "../lib/engine.hpp"
#include "../assets/projList.hpp"
#include "../assets/superProjList.hpp"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;






/*#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5
*/


int main(int argc, char **argv)
{

	
	
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
	
	int stdscrxmax, stdscrymax;
	getmaxyx(stdscr, stdscrymax, stdscrxmax);
	/*while(yMax>50 && xMax >200){
		mvprintw(yMax/2, xMax/2, "rimpicciolisci il terminale");
	}
	while(yMax<30 && xMax >\){
		mvprintw(yMax/2, xMax/2, "rimpicciolisci il terminale");
	}*/
	
	Board board(BOARD_ROWS, BOARD_COLS);
	WINDOW* schermoliam = newwin(50, 211, (stdscrymax / 2) - (50/2), (stdscrxmax / 2) - ((211/2)));
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
	

		
	
	
	superProjList* superProjListHead = new superProjList;	superProjListHead = NULL;
	//se cancellate la riga sopra commentate il refreshSuperProjectiles nel ciclo


	

		

	

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
	

	

	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{
		time_now = system_clock::now();


		p.HandleInput(ch);
		Astolfo.checkIfTimeToMove(time_now);
		
		refreshSuperProjectiles(superProjListHead, time_now, p.getProjectilesShot());
		refreshProjectiles(p.getProjectilesShot(), time_now);
		
		
		
		refresh();
		
		
		
		

		if(ch == 'f') {    //SE VOLETE SPARARE PER PROVARE PREMETE f
			p.shoot();
		}
		else if(ch=='g') {    //tasti di debug se li premete potrebbe buggarsi qualcosa
			SuperProjectile newProjectile = SuperProjectile("O", p.getCurrentPosition(), p.getLastDirection(),
															100, 800, 100, "'", p.getWin());
			superProjList *newproj = new superProjList;
			newproj->sproj = newProjectile;
			newproj->next = superProjListHead;
			superProjListHead = newproj;
			superProjListHead->sproj.move();
			(*p.getProjectilesShot()).proj.move();
		}

		else if(ch == 'h') {    //tasti di debug se li premete potrebbe buggarsi qualcosa
			/*int dirsdebug[2];
			superProjListHead->proj.getSpawningDirections(dirsdebug);
			p.settanuovahead( createProjectile2(p.getProjectilesShot(), "*", thiccboi.getCurrentPosition(), dirsdebug[0], 
			p.getProjectileMovingFrequency(), p.getWin()) );

			p.settanuovahead( createProjectile2(p.getProjectilesShot(), "*", thiccboi.getCurrentPosition(), dirsdebug[1], 
			p.getProjectileMovingFrequency(), p.getWin()) );
			*/

		}
		
		else if(ch=='t') {   //serve solo per il debug

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


		

		
		p.move(p.getCurrentPosition().x,p.getCurrentPosition().y);  //si assicura che il personaggio sia in primo piano
		refresh();
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}


