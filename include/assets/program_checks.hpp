#define MIN_TERM_Y 30
#define MIN_TERM_X 120

/**
 * Checks if the program is running on a valid terminal
 * with the right size and colors support
 * 
 * @note TERMINAL_SIZE_CHECK: check if terminal is at least MIN_TERM_X x MIN_TERM_Y
 * @note TERMINAL_COLOR_CHECK: check if terminal supports colors  
*/
#define CHECK_TERMINAL_VALIDITY TERMINAL_SIZE_CHECK; TERMINAL_COLOR_CHECK;

/**
 * The whole idea of using 'do/while' version is to make a macro which will expand into a regular statement, not into a compound statement. 
 * This is done in order to make the use of function-style macros uniform with the use of ordinary functions in all contexts. 
 * 
 * @note https://stackoverflow.com/questions/1067226/c-multi-line-macro-do-while0-vs-scope-block#:~:text=The%20whole%20idea%20of%20using,ordinary%20functions%20in%20all%20contexts.
*/
#define NCURSES_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            endwin(); \
            std::cerr << "Assertion failed: " #expr << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (0)

#define TERMINAL_SIZE_CHECK NCURSES_ASSERT(LINES >= MIN_TERM_Y && COLS >= MIN_TERM_X)
#define TERMINAL_COLOR_CHECK NCURSES_ASSERT(has_colors())
