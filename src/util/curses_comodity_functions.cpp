#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/string_override.hpp"
#include "../../include/assets/program_checks.hpp"
#include "../../include/util/math_override.tpp"

void init() {
	/* Init and validity checks for terminal size and color comp */
	initscr();
	CHECK_TERMINAL_VALIDITY

	/* Config */
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, true);
	
	clear();
	refresh();
}

void centering_text(WINDOW *terminal, int first_row, const char *string) {
	mvwaddstr(terminal, first_row, (terminal->_maxx / 2) - (strlen(string) / 2), string);
}

void empty() {
	clear();
	refresh();
}

void werase(WINDOW *terminal, int y, int x) {
	mvwaddch(terminal, y, x, ' ');
}

void mvwaddint(WINDOW* win, int posy, int posx, int input) {
	mvwprintw(win, posy, posx, "%s", intstr(input));
}

void printScreenSize(WINDOW *win) {
	int width = win->_maxx, height = win->_maxy;
	int dif = mathy::numDigits(width);
	int x = width / 2, y = height / 2;

	mvwaddint(stdscr, y, x, width);
	mvwaddstr(stdscr, y, x + dif + 1, "x");
	mvwaddint(stdscr, y, x + dif + 3, height);
}

/* void updateString(WINDOW* window, int y, int x, const char* newStr, ...) {
	int len = mvwinch(window, y, x) & A_CHARTEXT;
	mvwhline(window, y, x, ' ', len);
	
	va_list args;
	va_start(args, newStr);
	mvwprintw(window, y, x, newStr, va_arg(args, char*));
	va_end(args);
} */


void updateString(WINDOW* window, int y, int x, const char* newStr, ...) {
	mvwhline(window, y, x, ' ', window->_maxx - x);

	va_list args;
	va_start(args, newStr);

	char nullStr[] = "(null)";
	while (*newStr != '\0') {
		if (*newStr == '%') {
			newStr++;
			if (*newStr == 's') {
				char* str = va_arg(args, char*);
				if (str == NULL) {
					str = nullStr;
				}
				int i;
				for (i = 0; str[i] != '\0'; i++) {
					waddch(window, str[i]);
				}
				x += i;
			} else if (*newStr == 'd') {
				int num = va_arg(args, int);
				char str[16];
				sprintf(str, "%d", num);
				int i;
				for (i = 0; str[i] != '\0'; i++) {
					waddch(window, str[i]);
				}
				x += i;
			} else if (*newStr == 'f') {
				double num = va_arg(args, double);
				char str[32];
				sprintf(str, "%f", num);
				int i;
				for (i = 0; str[i] != '\0'; i++) {
					waddch(window, str[i]);
				}
				x += i;
			} else if (*newStr == 'c') {
				char c = (char) va_arg(args, int);
				waddch(window, c);
				x++;
			} else {
				waddch(window, '%');
				x++;
				waddch(window, *newStr);
				x++;
			}
		} else {
			waddch(window, *newStr);
			x++;
		}
		newStr++;
	}

	va_end(args);
}
