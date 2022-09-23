//File contiene tutte le funzioni inerenti ncurses e la gestione dello schermo
#include "../lib/engine.hpp"
#include <chrono>

#include <iostream>
using namespace std;

// Inizializza ncurses
void init() {
	initscr(); // Inizializza lo schermo secondo la libreria ncurses
	start_color(); // Permette l'utilizzo di colori sullo schermo
	clear(); // Svuota il terminale
	noecho(); // Rimuove l'input inserito nel terminale
	cbreak(); // Rimuove il buffer di input
	//keypad(stdscr, TRUE); //Abilita i tasti di funzione (Fn, frecce, etc...)
	curs_set(0); // Rende il cursore invisibile
	refresh();
}

// Cancella instanza ncurses
void end() {
	endwin();
}

// Conta la lunghezza di una stringa
long unsigned int Strlen(const char *p) {
	long unsigned int count = 0;
	while(*p!='\0') {
		count++;
		p++;
	}
	return count;
}

// Scrive del testo centrato sullo schermo
void centering_text(WINDOW *terminal, int first_row, const char *string) {
	int centerx = terminal->_maxx / 2;
	int lendiv = Strlen(string) / 2;
	int centerpos = centerx - lendiv;
	mvwprintw(terminal, first_row, centerpos, string);
}

/**Scrive del testo centrato sullo schermo
 * colorando i contenuti usando il color
 * pair assegnato 
 */
void centering_text(WINDOW *terminal, int first_row, const char *string, short color_pair) {
	int centerx = terminal->_maxx / 2;
	int lendiv = Strlen(string) / 2;
	int centerpos = centerx - lendiv;
	wattron(terminal, COLOR_PAIR(color_pair));
	mvwprintw(terminal, first_row, centerpos, string);
	wattroff(terminal, COLOR_PAIR(color_pair));
}

// Svuota il terminale
void empty() {
	clear();
	refresh();
}

void instructionsDisplay() {
	int scry, scrx; 
	getmaxyx(stdscr, scry, scrx);
	int height = 5, width = 61;
	WINDOW *sign = newwin(height, width, (scry / 2) + 5, (scrx / 2) - (width / 2));
	box(sign, 0, 0);
	centering_text(sign, 1, "Clicca qualsiasi tasto per iniziare");
	centering_text(sign, 2, "Se vuoi uscire dal programma premi \"q\" in qualsiasi momento");
	centering_text(sign, 3, "Per muovere il personaggio puoi utilizzare W, A, S, D");
	wrefresh(sign);
}

void titleInit(WINDOW* terminal, const char* string) {
	int cursorX = 0, cursorY = 0;
	init_pair(UNDERSCORE_COLOR_PAIR, COLOR_WHITE, COLOR_WHITE);
	init_pair(SPACE_COLOR_PAIR, COLOR_BLACK, COLOR_BLACK);
	init_pair(FS_COLOR_PAIR, COLOR_BLUE, COLOR_BLUE);
	init_pair(BS_COLOR_PAIR, COLOR_CYAN, COLOR_CYAN);
	for (unsigned int i = 0; i < Strlen(string); i++) {
		if (string[i] == '_') {
			wattron(terminal, COLOR_PAIR(UNDERSCORE_COLOR_PAIR));
			mvwaddch(terminal, cursorY, cursorX, '_');
			wattroff(terminal, COLOR_PAIR(UNDERSCORE_COLOR_PAIR));
		} else if (string[i] == '\\') {
			wattron(terminal, COLOR_PAIR(BS_COLOR_PAIR));
			mvwaddch(terminal, cursorY, cursorX, '\\');
			wattroff(terminal, COLOR_PAIR(BS_COLOR_PAIR));
		} else if (string[i] == '/') {
			wattron(terminal, COLOR_PAIR(FS_COLOR_PAIR));
			mvwaddch(terminal, cursorY, cursorX, '/');
			wattroff(terminal, COLOR_PAIR(FS_COLOR_PAIR));
		} else {
			wattron(terminal, COLOR_PAIR(SPACE_COLOR_PAIR));
			mvwaddch(terminal, cursorY, cursorX, ' ');
			wattroff(terminal, COLOR_PAIR(SPACE_COLOR_PAIR));
		}
		cursorX += 1;
		if (cursorX == terminal->_maxx - 1) {
			cursorX = 0;
			cursorY += 1;
		}
	}
}

void titleDisplay() {
	int scry, scrx; 
	getmaxyx(stdscr, scry, scrx);
	WINDOW *title = newwin(11, 80, scry / 2 - 10, scrx / 2 - 40);

	titleInit(title, "__/\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\_             _\\/\\\\\\/////////\\\\\\_\\/////\\\\\\///____/\\\\\\//////////____/\\\\\\\\\\\\\\\\\\\\\\\\\\_           _\\/\\\\\\_______\\/\\\\\\_____\\/\\\\\\______/\\\\\\______________/\\\\\\/////////\\\\\\_          _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/______\\/\\\\\\_____\\/\\\\\\____/\\\\\\\\\\\\\\_\\/\\\\\\_______\\/\\\\\\_          _\\/\\\\\\/////////________\\/\\\\\\_____\\/\\\\\\___\\/////\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_          _\\/\\\\\\_________________\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\/////////\\\\\\_          _\\/\\\\\\_________________\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_          _\\/\\\\\\______________/\\\\\\\\\\\\\\\\\\\\\\_\\//\\\\\\\\\\\\\\\\\\\\\\\\/__\\/\\\\\\_______\\/\\\\\\_          _\\///______________\\///////////___\\////////////____\\///________\\///_  ");

	/* centering_text(title, 1, "__/\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\_            ", 2);
	centering_text(title, 2, " _\\/\\\\\\/////////\\\\\\_\\/////\\\\\\///____/\\\\\\//////////____/\\\\\\\\\\\\\\\\\\\\\\\\\\_         ", 2);
	centering_text(title, 3, "  _\\/\\\\\\_______\\/\\\\\\_____\\/\\\\\\______/\\\\\\______________/\\\\\\/////////\\\\\\_       ", 2);
	centering_text(title, 4, "   _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/______\\/\\\\\\_____\\/\\\\\\____/\\\\\\\\\\\\\\_\\/\\\\\\_______\\/\\\\\\_      ", 2);
	centering_text(title, 5, "    _\\/\\\\\\/////////________\\/\\\\\\_____\\/\\\\\\___\\/////\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_     ", 2);
	centering_text(title, 6, "     _\\/\\\\\\_________________\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\/////////\\\\\\_    ", 2);
	centering_text(title, 7, "      _\\/\\\\\\_________________\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_   ", 2);
	centering_text(title, 8, "       _\\/\\\\\\______________/\\\\\\\\\\\\\\\\\\\\\\_\\//\\\\\\\\\\\\\\\\\\\\\\\\/__\\/\\\\\\_______\\/\\\\\\_  ", 2);
	centering_text(title, 9, "        _\\///______________\\///////////___\\////////////____\\///________\\///_  ", 2);
	centering_text(title, 10, "Platformer In Grafica ASCII"); */
	wrefresh(title);
}

// Inizializza ncurses e mostra la schermata di benvenuto 
void welcome() {
 	init();
	titleDisplay();
	instructionsDisplay();
}

// Cancella un carattere in determinate coordinate
void erase(int y, int x) {
	mvaddch(y, x, ' ');
}

void werase(WINDOW *terminal, int y, int x) {
	mvwaddch(terminal, y, x, ' ');
}

// Evidenzia gli angoli di una WINDOW
void corners(WINDOW *room) {
	mvaddch(room->_begy, room->_begx, 'O'); // ACS_ULCORNER
	mvaddch(room->_begy + room->_maxy, room->_begx + room->_maxx, 'O'); //ACS_LRCORNER
	refresh();
	mvaddch(room->_begy + room->_maxy, room->_begx, 'O'); // ACS_LLCORNER
	mvaddch(room->_begy, room->_begx + room->_maxx, 'O'); // ACS_URCORNER
	refresh();
}

chtype getcharat(int y, int x){
	return mvinch(y, x);
}

int legalMove(int y, int x) {
    int testch;
    testch = mvinch(y, x);
    return (((testch & A_CHARTEXT) == EMPTY)/* || se e' un artefatto */);
}

void refreshProjectiles(projList* head, system_clock::time_point time_now) {
	projList *p = new projList;
	p = head;
	projList *toBeDeleted = new projList;
	toBeDeleted = NULL;

	while(p != NULL) {
		p->proj.checkIfTimeToMove(time_now);
		p = p->next;
	}

	p = head;

	while((p != NULL) && (p->next != NULL)) {
		if(!((p->next->proj).isAlive())) {
			toBeDeleted = p->next;
			p->next = p->next->next;
			delete(toBeDeleted);
			toBeDeleted = NULL;
		}
		p = p->next;
	}
	//controllo il primo elemento
	
	if((head != NULL) && !((head->proj).isAlive())) {
		if(head->next == NULL) {
			head = NULL;
		}
		else {
			toBeDeleted = head;
			head = head->next;
			delete(toBeDeleted);
			toBeDeleted = NULL;
		}
	}

	
////////////////////
/*
	projList *p = new projList;
	p = head;
	
	//controllo per i primi elementi della lista. riguarda solo quelli da eliminare
	//serve se più proiettili vanno eliminati contemporaneamente (molto raro in realtà)
	while((head != NULL) && (!head->proj.isAlive())) {
		head = head->next;
		p->proj.deleteIcon();
		delete(p);
		p = head;
	}

	projList *pprec = new projList;
	pprec = p;

	//controllo sul primo proiettile della lista ancora "vivo". inoltre setto il pprec
	if((p != NULL) && (p->next != NULL)) {
		//il prossimo controllo agisce su p. ma io so che QUESTO p non è da cancellare (altrimenti non sarebbe uscito dal while)
		p->proj.checkIfTimeToMove(time_now);
		p = p->next;    //quindi passo a controllare il successivo, nel prossimo while
	}
	
	//controllo il resto della lista
	while(p != NULL) {
		p->proj.checkIfTimeToMove(time_now);
		pprec = p;

		if(!(p->proj.isAlive())) {
			pprec->next = p->next;
			delete(p);
			p = pprec->next;
		}

		if(p->next != NULL) {
			p = p->next;
		}
	}
	*/
}

void FUNZIONEDEBUG(projList* head, system_clock::time_point time_now) {
}