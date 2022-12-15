#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/string_override.hpp"

void init() {
	initscr(); // Inizializza lo schermo secondo la libreria ncurses
	
	if(has_colors() == FALSE){
		endwin();
		printf("Il tuo terminale non supporta i colori");
		exit(1);
	}
	start_color(); // Permette l'utilizzo di colori sullo schermo
	
	clear(); // Svuota il terminale
	noecho(); // Rimuove l'input inserito nel terminale
	cbreak(); // Rimuove il buffer di input
	keypad(stdscr, TRUE); //Abilita i tasti di funzione (Fn, frecce, etc...)
	curs_set(0); // Rende il cursore invisibile
	
	refresh();
}

void centering_text(WINDOW *terminal, int first_row, const char *string) {
	int centerx = terminal->_maxx / 2;
	int lendiv = strlen(string) / 2;
	int centerpos = centerx - lendiv;
	mvwaddstr(terminal, first_row, centerpos, string);
}

void empty() {
	clear();
	refresh();
}

void werase(WINDOW *terminal, int y, int x) {
	mvwaddch(terminal, y, x, ' ');
}