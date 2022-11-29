#include "../assets/hch.h"
#include "../lib/board.hpp"
#include "../lib/entity.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../lib/superProjectile.hpp"
#include "../assets/position.hpp"
#include "../lib/enemy.hpp"
#include "../lib/engine.hpp"
#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"
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
	Character p = Character("@", character_initial_position, 30, "*", 100, board.getWin());
	p.move(character_initial_position.x, character_initial_position.y);



	//DEBUG - prova delle collisioni

	bool DEBUGCOLLISIONI = false;
	int projheadx, projheady, enheadx, enheady;
	



	

		

	

	// prova nemico
	
	/*
	Position p1={2,2};
	Position p2={6,6};
	Position p3={10,10};
	Position p4={15,15};
	Enemy cane = Enemy("A",10,10,p1,RANDOM,idle_time_enemy,board.getWin());
	Enemy canguro = Enemy("A",10,10,p2,STSLR,idle_time_enemy,board.getWin());
	Enemy xilofono = Enemy("A",10,10,p3,STSUD,idle_time_enemy,board.getWin());
	Enemy gatto = Enemy("A",10,10,p4,RANDOM,idle_time_enemy,board.getWin());
	List<Enemy> Enemies;
	//gatto.setDistanceToPlayer(p.getCurrentPosition());
	Enemies.headInsert(cane);
	Enemies.headInsert(canguro);
	Enemies.headInsert(xilofono);
	Enemies.headInsert(gatto);
	Enemies.spawnEnemies();
	Enemies.removeDeadEntities();
	//cout << Enemies.listLenght() << endl;
	//Enemies.removeElement(&cane);
//	Enemies.killEnemy(2);
	Enemies.removeDeadEntities();
	*/


	

	board.generateEnemies();
	// /DEBUG

	//strutture per tenere proiettili e superproiettili
	List<Projectile> *projectilesList;
	projectilesList = board.getProjectilesList();
	List<SuperProjectile>* superProjectilesList;
	superProjectilesList = board.getSuperProjectilesList();
	//gestione del tempo
	system_clock::time_point time_now = system_clock::now();
	
	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{
		time_now = system_clock::now();


		p.HandleInput(ch);
		//Astolfo.checkIfTimeToMove(time_now);
		/*
		Enemies.moveEntities(time_now);
		Enemies.enemyShooting(time_now);
		Enemies.refreshEnemyProj(time_now);
		*/
		board.refreshEnemies(time_now,p.getCurrentPosition());
		(*projectilesList).moveEntities(time_now);
		(*projectilesList).removeDeadEntities();

		refreshSuperProjectiles(time_now, superProjectilesList, projectilesList);

		if((projectilesList->getHead() != NULL) && (board.getEnemiesList()->getHead() != NULL)) DEBUGCOLLISIONI = true;
		else DEBUGCOLLISIONI = false;
		if(DEBUGCOLLISIONI) {
			projheadx = board.getProjectilesList()->getHead()->getData()->getCurrentPosition().x;
			projheady = board.getProjectilesList()->getHead()->getData()->getCurrentPosition().y;
			enheadx = board.getEnemiesList()->getHead()->getData()->getCurrentPosition().x;
			enheady = board.getEnemiesList()->getHead()->getData()->getCurrentPosition().y;
			wattron(stdscr, COLOR_PAIR(PROJCTL_PAIR));
			mvprintw(19, 170, "coordinate x,y proiettile in testa alla lista:");
			mvprintw(20, 170, "        ");
			mvprintwInteger(20, 170, projheadx); mvprintwInteger(20, 175, projheady);
			mvprintw(21, 170, "coordinate x,y nemico in testa alla lista:");
			mvprintw(22, 170, "        ");
			mvprintwInteger(22, 170, enheadx); mvprintwInteger(22, 175, enheady);
			wattroff(stdscr, COLOR_PAIR(PROJCTL_PAIR));
		}
		
		board.checkHits();
		board.refreshEnemies(time_now,p.getCurrentPosition());

		refresh();

		//IF CAMBI STANZA: RIASSEGNA projectilesList e superProjectilesList

		if(ch == 'f') {    //SE VOLETE SPARARE PER PROVARE PREMETE f
		//DEVO FARE: mettere "f" nell'handleInput di Character
			p.shoot(projectilesList);
			mvwprintw(p.getWin(), 2, 2, "   ");
		}
		else if(ch=='g') {    //poi non penso che il personaggio sparerà questi, magari li spara il boss
			createSuperProjectile(superProjectilesList, "O", p.getCurrentPosition(), p.getLastDirection(), 100,
																	1000, 100, "*", p.getWin());
		}

		
		else if(ch=='t') {   //serve solo per il debug

			def_prog_mode();
			endwin();
			//apre terminale
			// -- inizia codice --


			//FUNZIONEDEBUG(); 
			cout << "numero nemici: " << (*board.getEnemiesList()).listLength() << endl;
			cout << "n proiettili sul main: " << (*projectilesList).listLength() << endl;
			//cout << "posizione thiccboi x: " << thiccboi.getCurrentPosition().x << ", y: " << thiccboi.getCurrentPosition().y << endl;
			cout << "numero proiettili board: " << (*board.getProjectilesList()).listLength() << endl;
			//cout << "posizione head proj x: " << projectilesList.getHead().getCurrentPosition().x << "y, : " << projectilesList.getHead().getCurrentPosition().x << endl;
			cout << "numero superproiettili board: " << (*board.getSuperProjectilesList()).listLength() << endl;
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


