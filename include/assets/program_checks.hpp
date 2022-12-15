/**
 * Checks if the program is running on a valid terminal
 * with the right size and colors support
 * 
 * @param TERMINAL_SIZE_CHECK check if terminal is at least 80x24
 * @param TERMINAL_COLOR_CHECK check if terminal support colors  
*/
#define CHECK_TERMINAL_VALIDITY TERMINAL_SIZE_CHECK TERMINAL_COLOR_CHECK

#define TERMINAL_SIZE_CHECK if ((LINES < 24) || (COLS < 80)) {printf("Il terminale deve essere almeno di 80x24\n");exit(1);}
#define TERMINAL_COLOR_CHECK if(has_colors() == FALSE) {printf("Il tuo terminale non supporta i colori\n");exit(2);}
