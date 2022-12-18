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

//Confronta due stringe
//ritorna: 
//0 se le stringhe sono identiche 
//>0 se la prima stringa è maggiore della seconda
//<0 altrimenti
int strcmp(const char *s1, const char *s2) {
	const unsigned char *p1 = (const unsigned char *)s1;
	const unsigned char *p2 = (const unsigned char *)s2;
	while (*p1 && (*p1 == *p2)) 
		++p1, ++p2;
	return (*p1 > *p2) - (*p2 > *p1);
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

/** @overload
 * Scrive del testo centrato sullo schermo
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

void refreshSuperProjectiles(system_clock::time_point time_now, List<SuperProjectile> *superProjectilesList, List<Projectile> *projectilesList) {
    superProjectilesList->moveEntities(time_now);
    superProjectilesList->removeDeadEntities();
    Node<SuperProjectile> *tmp = superProjectilesList->getHead();
    while (tmp != NULL) {
		tmp->getData()->checkIfTimeToShoot(time_now, projectilesList);
        tmp = tmp->getNext();
    }
}

void createSuperProjectile(List<SuperProjectile> *superProjectilesList,
                            const char* icon, Position position, int direction, int damage, int moving_frequency, int spawning_frequency, 
                            int child_moving_frequency, const char* child_icon, WINDOW* win) {
	
	SuperProjectile newSuperProjectile = SuperProjectile(icon, position, direction, damage, moving_frequency, spawning_frequency,
															child_moving_frequency, child_icon, true, win);
	newSuperProjectile.move();
	superProjectilesList->headInsert(newSuperProjectile);
}

//DUE CIFRE
void mvwprintwInteger(WINDOW* win, int posy, int posx, int input) {
	char text[4];
	sprintf(text, "%d", input);
	mvwprintw(win, posy, posx, text);
}

void displayCharacterHealth(WINDOW* win, int health, int num_hearts) {
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	//visualizzazione della salute rimanente in interi

	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 1, 1, "Health: ");
	wattroff(win, COLOR_PAIR(1));
	
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 2, 1, "       ");
	mvwprintwInteger(win, 2, 3, health);
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
	
	//CUORI
	wattron(win, COLOR_PAIR(1));
	int in_posx = 3;
	mvwprintw(win, 3, in_posx, "                   ");
	for(int i = 0; i < num_hearts; i++) {
		mvwprintw(win, 3, in_posx + i*3, "V  ");
	}
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
}

int checkIfCharacterIsHit(List<Projectile>* projectilesList, List<SuperProjectile>* superProjectilesList, Position character_position) {
	Node<Projectile> *tmp1 = projectilesList->getHead();
	Node<SuperProjectile> *tmp2 = superProjectilesList->getHead();
	int total_damage = 0;

	while(tmp1 != NULL) {
		if((compare(character_position, tmp1->getData()->getCurrentPosition()))&&(!(tmp1->getData()->checkifAllied()))) {
			total_damage += tmp1->getData()->getDamage();
			tmp1->getData()->setAlive(false);
		}
		tmp1 = tmp1->getNext();
	}

	while(tmp2 != NULL) {
		if((compare(character_position, tmp2->getData()->getCurrentPosition()))&&(!(tmp2->getData()->checkifAllied()))) {
			total_damage += tmp2->getData()->getDamage();
			tmp2->getData()->setAlive(false);
		}
		tmp2 = tmp2->getNext();
	}

	return total_damage;
}

void displayGameOver() {
	//naturalmente può essere cambiata, adesso non è granchè
	//magari creiamo un'altra finestra che copre buona parte della stanza e magari qualche colore giusto per leggere bene che hai perso
	int stdscrxmax, stdscrymax;
	getmaxyx(stdscr, stdscrymax, stdscrxmax);
	mvprintw(stdscrymax / 2, stdscrxmax / 2, "* * * H A I   P E R S O * * *");
	mvprintw(stdscrymax / 2 + 2, stdscrxmax / 2, "premi un tasto per uscire");
}