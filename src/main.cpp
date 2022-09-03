#include <ncursesw/ncurses.h>
#include "../lib/board.hpp"
#include "../lib/character.hpp"
#include "../lib/projectile.hpp"
#include "../assets/position.hpp"
#include "../lib/enemy.hpp"

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
	
	initscr();	   // Inizializza lo schermo secondo la libreria ncurses
	start_color(); // Permette l'utilizzo di colori sullo schermo
	clear();	   // Svuota il terminale
	noecho();	   // Rimuove l'input inserito nel terminale
	cbreak();	   // Rimuove il buffer di input
	// keypad(stdscr, TRUE); //Abilita i tasti di funzione (Fn, frecce, etc...)
	curs_set(0); // Rende il cursore invisibile
	nodelay(stdscr, true);   //altrimenti aspetta sempre l'input dell'utente
	refresh();
	int rows, cols;
	getmaxyx(stdscr, rows, cols);

	///////////////////////////////////////////////////////////////////////////

	// Inizializzazione della tavola principale iniziale
	rows=rows-21;
	cols=rows*2.5;
	Board board(rows, cols);

	// Inizializzazione del personaggio principale
	Character p = Character();
	p.setRoomWin(board.getWin());

	// Posizionamento del personaggio principale nel terminale, posizione relativa da 0,0 (alto sinistra del terminale per adesso)
	p.PlayerMove(getmaxx(stdscr)/2, getmaxy(stdscr)/2);


	//DEBUG - prova del proiettile
	Position spawnpoint_projectile;
	spawnpoint_projectile.x = 2; spawnpoint_projectile.y = 2;
	duration <int, std::ratio <1,1000 > > time_interval_projectile(250);
	Projectile speedygonzales = Projectile("*", spawnpoint_projectile, 0, time_interval_projectile);
	speedygonzales.spawn(stdscr, speedygonzales.getCurrentPosition());

	Projectile pr1 = Projectile("?", {12, 12}, 1, time_interval_projectile*2);
	Projectile pr2 = Projectile("!", {15, 4}, 1, time_interval_projectile/4);

	bool pr1alive = false;
	bool pr2alive = false;

	speedygonzales.setCurrentRoom(board.getWin());
	pr1.setCurrentRoom(board.getWin());
	pr2.setCurrentRoom(board.getWin());

		//-- prova character.legalMove()
	

		// /prova character.legalMove()

	// /DEBUG

	// prova nemico
	Position spawnpoint_enemy;
	spawnpoint_enemy.x=20; spawnpoint_enemy.y=20;
	duration <int, std::ratio <1,1000 > > idle_time_enemy(250);
	Enemy Astolfo = Enemy("A",10,1,spawnpoint_enemy,1,idle_time_enemy);
	Astolfo.spawn(stdscr, Astolfo.getCurrentPosition());




	system_clock::time_point time_now = system_clock::now();
	int ch; // Variabile di accesso al handler per gli input
	while ((ch = getch()) != 'q')
	{
		p.HandleInput(ch);
		
		time_now = system_clock::now();
		//speedygonzales.checkIfTimeToMove(time_now);

		if(ch=='f') {
			pr1.setPosition(p.getCurrentPosition());
			pr1.spawn(stdscr, p.getCurrentPosition());
			pr1alive = true;
		}
		else if(ch=='g') {
			pr2.setPosition(p.getCurrentPosition());
			pr2.spawn(stdscr, p.getCurrentPosition());
			pr2alive = true;
		}
		else if(ch=='t') {
			int stampa_debug = mvwinch(board.getWin(), 0, 2) & A_CHARTEXT;
			def_prog_mode();
			endwin();
			//apre terminale
			// -- inizia codice --
<<<<<<< HEAD
			cout << "board: " << endl;
			cout << "x: " << getbegx(board.getWin()) << " y: " << getbegy(board.getWin()) << endl;
			cout << "carattere sopra: " << stampa_debug << endl;
=======
>>>>>>> 7fd453cf8c268c8c4c737896f0d56ce0ca3e3e99
			int inutile;
			cin >> inutile;
			mvprintw(20,20,"#");
			int cacca = mvwinch(stdscr,20,20);
			cout <<cacca;
			// -- fine codice --
			//riapre ncurses
			reset_prog_mode();
			refresh();
 		}

		if(pr1alive) pr1.checkIfTimeToMove(time_now);
		if(pr2alive) pr2.checkIfTimeToMove(time_now);


		
		
		refresh();
		mvwprintw(p.getWin(), 0, 0, p.getIcon());
		wrefresh(p.getWin());
		
	}

	// Blocco funzionale per la verifica del tasto "quit", prima di svuotare lo schermo
	getch();
	endwin();

	return 0;
}
