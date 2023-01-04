#define MIN_TERM_Y 30
#define MIN_TERM_X 120

/**
 * Checks if the program is running on a valid terminal
 * with the right size and colors support
 * 
 * @note TERMINAL_SIZE_CHECK: check if terminal is at least MIN_TERM_X x MIN_TERM_Y
 * @note TERMINAL_COLOR_CHECK: check if terminal supports colors  
*/
#define CHECK_TERMINAL_VALIDITY TERMINAL_SIZE_CHECK TERMINAL_COLOR_CHECK

#define NCURSES_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            endwin(); \
            std::cerr << "Assertion failed: " #expr << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (0);

#define TERMINAL_SIZE_CHECK NCURSES_ASSERT(LINES >= MIN_TERM_Y && COLS >= MIN_TERM_X)
#define TERMINAL_COLOR_CHECK NCURSES_ASSERT(has_colors())
