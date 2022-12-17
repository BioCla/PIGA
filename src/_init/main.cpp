#include "../../include/assets/hch.h"
#include "../../include/objects/board.hpp"
#include "../../include/assets/entity.hpp"
#include "../../include/objects/character.hpp"
#include "../../include/objects/projectile.hpp"
#include "../../include/objects/superProjectile.hpp"
#include "../../include/assets/position.hpp"
#include "../../include/objects/enemy.hpp"
#include "../../include/util/engine.hpp"
#include "../../include/util/listUtils.hpp"
#include "../../include/objects/item.hpp"
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
	cbreak();
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
	Character p = Character("@", character_initial_position, 30, "*", 5, 100, board.getWin());
	p.move(character_initial_position.x, character_initial_position.y);



	//DEBUG -
	// prova delle collisioni

	bool DEBUGCOLLISIONI = false;
	int projheadx, projheady;
	//int enheadx, enheady;
	//servono per stampare le posizioni delle teste della lista

	
	

	// /prova delle collisioni

	int current_damage_received_by_character = 0;
	//p.setHealth(10);

	//prova item
	

	// / prova item

		

	

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


	//VITA PERSONAGGIO
	WINDOW* window_GUI_1;
	window_GUI_1 = newwin(20, 40, 15, 165);
	box(window_GUI_1, 0, 0);
	wrefresh(window_GUI_1);
	refresh();


	

	//queste due andranno nel costruttore di board: genero una nuova stanza, e con essa la lista di nemici e artefatti
	board.generateEnemies();
	board.generateItems();


	//queste vanno cambiate nella board tutte le volte che si cambia stanza, altrimenti il personaggio non può sparare
	p.setProjectilesList(board.getProjectilesList());
	p.setSuperProjectilesList(board.getSuperProjectilesList());

	// /DEBUG

	

	//strutture per tenere proiettili e superproiettili
	List<Projectile> *projectilesList;
	projectilesList = board.getProjectilesList();
	List<SuperProjectile>* superProjectilesList;
	superProjectilesList = board.getSuperProjectilesList();
	
	//gestione del tempo
	system_clock::time_point time_now = system_clock::now();
	
	int ch; // Variabile di accesso al handler per gli input
	while (((ch = getch()) != 'q') && (p.isAlive()))
	{
		time_now = system_clock::now();


		p.HandleInput(ch);
		
		board.getItemsList()->spawnEntities();

		board.refreshEnemies(time_now,p.getCurrentPosition());
		projectilesList->moveEntities(time_now);
		projectilesList->removeDeadEntities();

		refreshSuperProjectiles(time_now, superProjectilesList, projectilesList);


		
		if((projectilesList->getHead() != NULL) && (board.getEnemiesList()->getHead() != NULL)) DEBUGCOLLISIONI = true;
		else DEBUGCOLLISIONI = false;
		if(DEBUGCOLLISIONI) {   //DEBUG
			projheadx = board.getProjectilesList()->getHead()->getData()->getCurrentPosition().x;
			projheady = board.getProjectilesList()->getHead()->getData()->getCurrentPosition().y;
			wattron(window_GUI_1, COLOR_PAIR(PROJCTL_PAIR));
			mvwprintw(window_GUI_1, 5, 1, "coordinate x,y proiettile in testa:");
			mvwprintw(window_GUI_1, 6, 1, "        ");
			mvwprintwInteger(window_GUI_1, 6, 1, projheadx); mvwprintwInteger(window_GUI_1, 6, 6, projheady);
			mvwprintw(window_GUI_1, 7, 1, "coordinate x,y personaggio:");
			mvwprintw(window_GUI_1, 8, 1, "        ");
			mvwprintwInteger(window_GUI_1, 8, 1, p.getCurrentPosition().x); mvwprintwInteger(window_GUI_1, 8, 6, p.getCurrentPosition().y);
			mvwprintw(window_GUI_1, 9, 1, "coordinate x,y nemico in testa:");
			mvwprintw(window_GUI_1, 10, 1, "       ");
			mvwprintwInteger(window_GUI_1, 10, 1, board.getEnemiesList()->getHead()->getData()->getCurrentPosition().x); mvwprintwInteger(window_GUI_1, 10, 6, board.getEnemiesList()->getHead()->getData()->getCurrentPosition().y);
			mvwprintw(window_GUI_1, 11, 1, "vita nemico in testa");
			mvwprintw(window_GUI_1, 12, 1, "                ");
			mvwprintwInteger(window_GUI_1, 12, 1, board.getEnemiesList()->getHead()->getData()->getHealth());
			mvwprintw(window_GUI_1, 13, 1, "arma personaggio: ");
			mvwprintw(window_GUI_1, 13, 18, "                ");
			mvwprintwInteger(window_GUI_1, 13, 19, p.getWeapon());
			wattroff(window_GUI_1, COLOR_PAIR(PROJCTL_PAIR));
		}
		
		board.refreshEnemies(time_now,p.getCurrentPosition());
		
		board.checkHits();

		current_damage_received_by_character = -checkIfCharacterIsHit(board.getProjectilesList(), board.getSuperProjectilesList(), p.getCurrentPosition());
		board.checkItemCollisions(&p);
		board.getItemsList()->removeDeadEntities();
		p.updateHealth(current_damage_received_by_character);
		
		displayCharacterHealth(window_GUI_1, p.getHealth(), p.getHearts());

		refresh();


		if(ch=='t') {   //serve solo per il debug

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
			cout << "numero item board: " << board.getItemsList()->listLength() << endl;
			cout << "mvwinch sopra il personaggio: " << mvwinch(board.getWin(), p.getCurrentPosition().y, p.getCurrentPosition().x) << endl;
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

		board.getEnemiesList()->spawnEntities();    //se un nemico viene colpito ma non muore la sua icona rimane. altrimenti "scompare" fino al suo prox movimento
		p.move(p.getCurrentPosition().x,p.getCurrentPosition().y);  //si assicura che il personaggio sia in primo piano
		refresh();
		
		//flushinp(); //svuota la coda di input
		napms(1000 / 144); //144 fps limit
	}
	
	//se il personaggio muore, rendi noto all'utente che ha perso il gioco
	if (!p.isAlive()) {
		nodelay(stdscr, false);
		displayGameOver();
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}


