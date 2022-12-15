#ifndef CURSES_COMODITY_FUNCTIONS
#define CURSES_COMODITY_FUNCTIONS

#include "../assets/curses_lib_selector.hpp"

#define erase(y, x) werase(stdscr, y, x)

// Inizializza ncurses
void init();

// Scrive del testo centrato sullo schermo
void centering_text(WINDOW *terminal, int first_row, const char *string);
// Svuota il terminale
void empty();

// Cancella un carattere in determinate coordinate su una finestra
void werase(WINDOW *terminal, int y, int x);

#endif