//#include "../../include/assets/hch.h"
//#include "../../include/objects/board.hpp"
//#include "../../include/assets/entity.hpp"
//#include "../../include/objects/character.hpp"
//#include "../../include/objects/projectile.hpp"
//#include "../../include/objects/superProjectile.hpp"
//#include "../../include/assets/position.hpp"
//#include "../../include/objects/enemy.hpp"
//#include "../../include/util/engine.hpp"
//#include "../../include/objects/item.hpp"
//#include "../../include/util/graph.tpp"
#include "../../include/assets/map.hpp"   //è tutto incluso a catena qui dentro
#include "../../include/assets/game_data.hpp"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;


/*#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5
*/

int main()
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
	
	//disegno bordi massimi dello schermo
	WINDOW* schermoliam = newwin(50, 211, (stdscrymax / 2) - (50/2), (stdscrxmax / 2) - ((211/2)));
	box(schermoliam, 1, 1);
	wrefresh(schermoliam);

	//stanza iniziale
	Board board(BOARD_ROWS, BOARD_COLS, 0);
	box(board.getWin(), 0, 0);
	board.addBorder();
	wrefresh(board.getWin());	


	// Inizializzazione del personaggio principale
	Position character_initial_position;
	character_initial_position.x = 5;
	character_initial_position.y = 5;
	Character p = Character("@", character_initial_position, 1500, "*", 5, 100, board.getWin());   //DEBUG 1500 di vita temporaneamente (normalmente è 30)
	p.move(character_initial_position);

	
	GAME_TOTAL_SCORE = 0;   //da implementare
	bool player_entered_new_room = false;



	//DEBUG -
	// prova delle collisioni
/*
	bool DEBUGCOLLISIONI = false;
	int projheadx, projheady;
	bool proj_list_is_null = true;
	bool enemy_list_is_null = true;
*/
	//int enheadx, enheady;
	//servono per stampare le posizioni delle teste della lista

	
	

	// /prova delle collisioni

	int current_damage_received_by_character = 0;
	//p.setHealth(10);

	//prova item
	

	// / prova item

	// prova grafi



		// prova mappa
		game_map.AddVertex(board);   //questo sta in un suo file. potevo inizializzarlo sul main ma l'ho messo da un'altra parte. si può anche spostare
		board.initialize();   //aggiungere la board al grafo la fa visualizzare male, non so perchè.
					//quindi ristampo il pavimento e il bordo
		

		// / prova mappa
	

	// / prova grafi

	//prova update map

	// / prova update map

	

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
	//board.generateEnemies();
	//board.generateItems();


	//queste vanno cambiate nella board tutte le volte che si cambia stanza, altrimenti il personaggio non può sparare
	p.setProjectilesList(board.getProjectilesList());
	p.setSuperProjectilesList(board.getSuperProjectilesList());

	// /DEBUG

	//setting iniziale per il punteggio di gioco
	updateGameScore(board, GAME_TOTAL_SCORE, true, number_of_enemies_in_room);

	
	//gestione del tempo
	system_clock::time_point time_now = system_clock::now();

	int ch; // Variabile di accesso al handler per gli input
	while (((ch = getch()) != 'q') && (p.isAlive()))
	{
		time_now = system_clock::now();


		p.HandleInput(ch);
		
		board.getItemsList()->spawnEntities();

		board.refreshEnemies(time_now, p.getCurrentPosition());

		board.getProjectilesList()->moveEntities(time_now);
		board.getProjectilesList()->removeDeadEntities();

		refreshSuperProjectiles(time_now, board.getSuperProjectilesList(), board.getProjectilesList());

/*
		//     DEBUG ma può far comodo quindi rimane commentato
		//if((board.getProjectilesList()->getHead() != NULL) && (board.getEnemiesList()->getHead() != NULL)) DEBUGCOLLISIONI = true;
		//else DEBUGCOLLISIONI = false;
		//if(board.getProjectilesList()->getHead() != NULL) {proj_list_is_null = false;} else {proj_list_is_null = true;}
		//if(board.getEnemiesList()->getHead() != NULL) {enemy_list_is_null = false;} else {enemy_list_is_null = true;}
		DEBUGCOLLISIONI = true;
		if(DEBUGCOLLISIONI) {   //DEBUG
			projheadx = board.getProjectilesList()->getHead()->getData()->getCurrentPosition().x;
			projheady = board.getProjectilesList()->getHead()->getData()->getCurrentPosition().y;
			wattron(window_GUI_1, COLOR_PAIR(PROJCTL_PAIR));

			if(!proj_list_is_null) {
				mvwprintw(window_GUI_1, 5, 1, "coordinate x,y proiettile in testa:");
				mvwprintw(window_GUI_1, 6, 1, "        ");
				mvwprintwInteger(window_GUI_1, 6, 1, projheadx); mvwprintwInteger(window_GUI_1, 6, 6, projheady);
			}
			else {
				mvwprintw(window_GUI_1, 5, 1, "coordinate x,y proiettile in testa:");
				mvwprintw(window_GUI_1, 6, 1, "NULL");				
			}

			mvwprintw(window_GUI_1, 7, 1, "coordinate x,y personaggio:");
			mvwprintw(window_GUI_1, 8, 1, "        ");
			mvwprintwInteger(window_GUI_1, 8, 1, p.getCurrentPosition().x); mvwprintwInteger(window_GUI_1, 8, 6, p.getCurrentPosition().y);
			
			if(!enemy_list_is_null) {
				mvwprintw(window_GUI_1, 9, 1, "coordinate x,y nemico in testa:");
				mvwprintw(window_GUI_1, 10, 1, "       ");
				mvwprintwInteger(window_GUI_1, 10, 1, board.getEnemiesList()->getHead()->getData()->getCurrentPosition().x); mvwprintwInteger(window_GUI_1, 10, 6, board.getEnemiesList()->getHead()->getData()->getCurrentPosition().y);
				mvwprintw(window_GUI_1, 11, 1, "vita nemico in testa");
				mvwprintw(window_GUI_1, 12, 1, "                ");
				mvwprintwInteger(window_GUI_1, 12, 1, board.getEnemiesList()->getHead()->getData()->getHealth());
			}
			else {
				mvwprintw(window_GUI_1, 9, 1, "coordinate x,y nemico in testa:");
				mvwprintw(window_GUI_1, 10, 1, "NULL");
				mvwprintw(window_GUI_1, 11, 1, "vita nemico in testa");
				mvwprintw(window_GUI_1, 12, 1, "NULL");
				
			}

			mvwprintw(window_GUI_1, 13, 1, "livello: ");
			mvwprintw(window_GUI_1, 13, 18, "                ");
			mvwprintwInteger(window_GUI_1, 13, 19, board.getLevelNumber());
			mvwprintw(window_GUI_1, 14, 1, "porte sbloccate?(0/1)");
			mvwprintwInteger(window_GUI_1, 14, 24, board.getDoorLockState());
			mvwprintw(window_GUI_1, 15, 1, "numero nemici board:");
			mvwprintwInteger(window_GUI_1, 15, 24, board.getEnemiesList()->listLength());
			mvwprintw(window_GUI_1, 16, 1, "numero item board:");
			mvwprintwInteger(window_GUI_1, 16, 24, board.getItemsList()->listLength());
			mvwprintw(window_GUI_1, 17, 1, "numero proiettili:");
			mvwprintwInteger(window_GUI_1, 17, 24, board.getProjectilesList()->listLength());
			wattroff(window_GUI_1, COLOR_PAIR(PROJCTL_PAIR));
		}
*/
		//DEBUG 
		wattron(window_GUI_1, COLOR_PAIR(PROJCTL_PAIR));
		mvwprintw(window_GUI_1, 10, 1, "number_of_enemies_in_room");
		mvwprintw(window_GUI_1, 10, 30, "          ");
		mvwprintwInteger(window_GUI_1, 10, 30, number_of_enemies_in_room);
		wattroff(window_GUI_1, COLOR_PAIR(PROJCTL_PAIR));
		
		
		board.refreshEnemies(time_now,p.getCurrentPosition());

		player_entered_new_room = updateMap(game_map, board, p);
		updateGameScore(board, GAME_TOTAL_SCORE, player_entered_new_room, number_of_enemies_in_room);
		
		board.checkHits();
		number_of_enemies_in_room = board.getEnemiesList()->listLength();


		current_damage_received_by_character = -checkIfCharacterIsHit(board.getProjectilesList(), board.getSuperProjectilesList(), p.getCurrentPosition());
		board.checkItemCollisions(&p);
		board.getItemsList()->removeDeadEntities();
		p.updateHealth(current_damage_received_by_character);
		
		displayCharacterHealth(window_GUI_1, p.getHealth(), p.getHearts());
		displayGameScore(window_GUI_1, GAME_TOTAL_SCORE);

		refresh();


		//input DEBUG t, l, k,
		//input p
		if(ch=='t') {   //serve solo per il DEBUG

			def_prog_mode();
			endwin();
			//apre terminale
			// -- inizia codice --


			//FUNZIONEDEBUG(); 
			cout << "------------------------------------------------" << endl;
			cout << "livello attuale: " << board.getLevelNumber() << endl;
			cout << "numero nemici: " << board.getEnemiesList()->listLength() << endl;
			cout << "n proiettili sul main: " << (*board.getProjectilesList()).listLength() << endl;
			//cout << "posizione thiccboi x: " << thiccboi.getCurrentPosition().x << ", y: " << thiccboi.getCurrentPosition().y << endl;
			cout << "numero proiettili board: " << (*board.getProjectilesList()).listLength() << endl;
			//cout << "posizione head proj x: " << projectilesList.getHead().getCurrentPosition().x << "y, : " << projectilesList.getHead().getCurrentPosition().x << endl;
			cout << "numero superproiettili board: " << (*board.getSuperProjectilesList()).listLength() << endl;
			cout << "numero item board: " << board.getItemsList()->listLength() << endl;
			int mvwinchsoprailpersonaggio = mvwinch(board.getWin(), p.getCurrentPosition().y - 1, p.getCurrentPosition().x) & A_CHARTEXT;
			cout << "mvwinch sopra il personaggio: " << mvwinchsoprailpersonaggio << endl;
			cout << "numero nodi mappa: " << game_map.NumVertices() << "   numero archi: " << game_map.NumEdges() << endl;
			//cout << "game_map.GetNeighbors(board.getLevelNumber()).listLength(): " << game_map.GetNeighbors(board.getLevelNumber()).listLength() << endl;	
			// -- fine codice --
			int inutile;
			cin >> inutile;
			//riapre ncurses
			reset_prog_mode();
			refresh();
 		}


		//l e k in realtà non servono più. però le lascio nel caso le volessimo usare, le toglieremo tra qualche commit
		//quindi diciamo che sono per DEBUG
		else if (ch == 'l') {    //vai nella stanza a destra. NON DOVREBBE CRASHARE. premete o se no non avete stanze
			if (!game_map.HasEdge(board.getLevelNumber(), board.getLevelNumber() + 1)) {
				createNewRoom(board.getLevelNumber(), game_map);
				moveToRoom(board.getLevelNumber() + 1, game_map, board, p);

				mvwprintw(window_GUI_1, 15, 1, "nuova stanza creata");
			}
			else {
				moveToRoom(board.getLevelNumber() + 1, game_map, board, p);

				mvwprintw(window_GUI_1, 15, 1, "                   ");
			}
		}
		else if (ch == 'k') {     //vai nella stanza a sinistra. NON DOVREBBE CRASHARE
			if (!game_map.HasEdge(board.getLevelNumber(), board.getLevelNumber() - 1)) {
				mvwprintw(window_GUI_1, 15, 1, "LIMITE RAGGIUNTO");
			}
			else {
				moveToRoom(board.getLevelNumber() - 1, game_map, board, p);

				mvwprintw(window_GUI_1, 15, 1, "                   ");
			}
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
		p.move(p.getCurrentPosition());  //si assicura che il personaggio sia in primo piano
		refresh();
		
		//flushinp(); //svuota la coda di input
		napms(1000 / 144); //144 fps limit
	}
	
	//se il personaggio muore, rendi noto all'utente che ha perso il gioco
	if (!p.isAlive()) {
		nodelay(stdscr, false);
		displayGameOver();
		while ((ch = getch()) != 'q');
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}


