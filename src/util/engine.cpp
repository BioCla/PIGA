//File contiene tutte le funzioni inerenti ncurses e la gestione dello schermo
#include "../../include/util/engine.hpp"

//#include <iostream>
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

// Svuota il terminale
void empty() {
	clear();
	refresh();
}

// Cancella un carattere in determinate coordinate
void erase(int y, int x) {
	mvaddch(y, x, ' ');
}

void werase(WINDOW *terminal, int y, int x) {
	mvwaddch(terminal, y, x, ' ');
}
