#include "../assets/curses_lib_selector.hpp"

// fg = foreground; bg = background

// Controlla se il colore è in grassetto
int is_bold(int fg);
// Inizializza i colori e le coppie di colori
void init_colorpairs(void);
// Restituisce il colore corrispondente al numero
short curs_color(int fg);
// Restituisce il numero corrispondente al colore
int colornum(int fg, int bg);
// Imposta il colore
void setcolor(int fg, int bg);
// Disabilita il colore
void unsetcolor(int fg, int bg);
// Demo dei colori
void test_colors();