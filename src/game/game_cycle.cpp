
#include "../../include/game/game_cycle.hpp"


void inizializzaNcurses() {
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
}



void start_game() {

	inizializzaNcurses();


	//mappa di gioco
    Graph<Board> game_map;

    int GAME_TOTAL_SCORE;
    int number_of_enemies_in_room;  //serve per aggiornare lo score
    
	
	int stdscrxmax, stdscrymax;
	getmaxyx(stdscr, stdscrymax, stdscrxmax);
	
	WINDOW* schermoliam = newwin(50, 211, (stdscrymax / 2) - (50/2), (stdscrxmax / 2) - ((211/2)));   //DEBUG schermo massimo
	box(schermoliam, 1, 1);
	wrefresh(schermoliam);

	//stanza iniziale
	Board board(BOARD_ROWS, BOARD_COLS, 0);
	box(board.getWin(), 0, 0);
	board.addBorder();
	wrefresh(board.getWin());	

	//aggiungo la stanza iniziale alla lista di stanze, ossia la mappa di gioco
	game_map.AddVertex(board);   
	board.initialize();   

	// Inizializzazione del personaggio principale
	Position character_initial_position;
	character_initial_position.x = 5;
	character_initial_position.y = 5;
	Character p = Character("@", character_initial_position, 1500, "*", 5, 100, board.getWin());    //DEBUG 1500 di vita (di norma 30)
	p.move(character_initial_position);

	//inizializza inventario personaggio
	p.printInventoryTitle();

	//punteggio di gioco
	GAME_TOTAL_SCORE = 0;  
	//variabile necessaria alla gestione del punteggio di gioco
	bool player_entered_new_room = false;    

	//variabile d'appoggio per calcolare le variazioni di vita del giocatore ad ogni ciclo
	int current_damage_received_by_character = 0; 
	
	//display vita personaggio e punteggio di gioco
	WINDOW* window_GUI_1;
	window_GUI_1 = newwin(20, 40, 15, 165);
	box(window_GUI_1, 0, 0);
	wrefresh(window_GUI_1);
	refresh();

	//ogni board ha la sua lista di proiettili, che contiene proiettili nemici e del giocatore
	//questo fa sì che i proiettili del giocatore vengano inseriti nella lista dei proiettili della stanza in cui spara
	p.setProjectilesList(board.getProjectilesList());
	p.setSuperProjectilesList(board.getSuperProjectilesList());

	//setting iniziale per il punteggio di gioco
	updateGameScore(board, GAME_TOTAL_SCORE, true, number_of_enemies_in_room);

	//gestione del tempo
	system_clock::time_point time_now = system_clock::now();

	int ch; // Variabile di accesso al handler per gli input
	while (((ch = getch()) != 'q') && (p.isAlive()))
	{
		time_now = system_clock::now();


		p.HandleInput(ch);   //W,A,S,D,F
		
		board.getItemsList()->spawnEntities();

		board.refreshEnemies(time_now, p.getCurrentPosition());

		board.getProjectilesList()->moveEntities(time_now);
		board.getProjectilesList()->removeDeadEntities();
		refreshSuperProjectiles(time_now, board.getSuperProjectilesList(), board.getProjectilesList());
		
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

		board.getEnemiesList()->spawnEntities();    //se un nemico viene colpito ma non muore la sua icona rimane. altrimenti "scompare" fino al suo prox movimento
		p.move(p.getCurrentPosition());  //si assicura che il personaggio sia in primo piano
		refresh();
		

		//PAUSA
		if(ch == 'p') {
			//lettera scelta arbitrariamente, per entrare nel ciclo di pausa
			ch = 'h';          
			mvprintw(stdscrymax - 5, stdscrxmax/2 - 4, "**PAUSA**");
			while(ch != 'p') {
				ch = getch();
				
			}
			mvprintw(stdscrymax - 5, stdscrxmax/2 - 4, "         ");
		}


		//fuzione di ncurses, serve a gestire gli input
		napms(1000 / 144); //144 fps limit

	}
	// -- fine ciclo di gioco



	//se il personaggio muore, rendi noto all'utente che ha perso il gioco
	if (!p.isAlive()) {
		nodelay(stdscr, false);
		displayGameOver(GAME_TOTAL_SCORE);
		while ((ch = getch()) != 'q');
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	centering_text(stdscr, stdscrymax / 2 +  8, "premi un tasto qualunque per terminare");
	getch();
	endwin();

}

