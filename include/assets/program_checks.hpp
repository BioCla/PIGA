#define MIN_TERM_Y 30
#define MIN_TERM_X 120

/**
 * Checks if the program is running on a valid terminal
 * with the right size and colors support
 * 
 * @param TERMINAL_SIZE_CHECK check if terminal is at least MIN_TERM_X x MIN_TERM_Y
 * @param TERMINAL_COLOR_CHECK check if terminal support colors  
*/
#define CHECK_TERMINAL_VALIDITY TERMINAL_SIZE_CHECK TERMINAL_COLOR_CHECK

#define TERMINAL_SIZE_CHECK \
	if((LINES < MIN_TERM_Y) || (COLS < MIN_TERM_X)) { \
		printf("Il terminale deve essere almeno di %s x %s\n", itc(MIN_TERM_X), itc(MIN_TERM_Y)); \
		printf("Il tuo terminale e' di %s x %s\n", itc(COLS), itc(LINES)); \
		exit(1); \
	}
#define TERMINAL_COLOR_CHECK if(has_colors() == FALSE){printf("Il tuo terminale non supporta i colori\n");exit(2);}
