#include "../../include/_init/game_menu.hpp"
#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/string_override.hpp"

option Menu::list[] = {
	{ "Start", [] { return EXIT_SUCCESS; } },
	{ "Options", [] { return 10; } },
	{ "Exit", [] { return EXIT_FAILURE; } },
};

const char* instructions[] = {
	"Use the arrow keys to navigate the menu",
	"Press enter to select an option",
};

const char* title = "Benvenuto nel gioco di prova di C++ e ncurses";

#define listSize sizeof(list) / sizeof(list[0]) - 1

#define instSize sizeof(instructions) / sizeof(instructions[0])

Menu::Menu() {
	menuWin = newwin(listSize + 3, 9, getmaxy(stdscr) / 2 - 3, getmaxx(stdscr) / 2 - 5);
	titleWin = newwin(3, strlen(title) + 2, 0, getmaxx(stdscr) / 2 - (strlen(title) / 2) - 1);
	instructionsWin = newwin(instSize + 2, 41, getmaxy(stdscr) - instSize - 2, getmaxx(stdscr) / 2 - 20);

	box(menuWin, 0, 0);
	box(titleWin, 0, 0);
	box(instructionsWin, 0, 0);
	
	wrefresh(menuWin);
	wrefresh(titleWin);
	wrefresh(instructionsWin);


	selected = 0;
}

bool Menu::handleInput() {
	bool ret = false;
	int ch = getch();
	switch (ch) {
		case KEY_UP:
			selected = selected == 0 ? listSize : selected - 1;
			break;
		case KEY_DOWN:
			selected = selected == listSize ? 0 : selected + 1;
			break;
		case KEY_ENTER:
		case '\n':
			ret = true;
			list[selected].action();
			break;
		default:
			break;
	}
	return ret;
}

void Menu::update(int selected) {
	int i = 0;
	for (option opt : list) {
		wattron(menuWin, i == selected ? A_REVERSE : A_NORMAL);
		centering_text(menuWin, i + 1, opt.label.c_str());
		wattroff(menuWin, i == selected ? A_REVERSE : A_NORMAL);
		i++;
	}
	wrefresh(menuWin);
}

void Menu::titleDisplay() {
	centering_text(titleWin, 1, title);
	wrefresh(titleWin);
}

void Menu::instructionsDisplay() {
	int i = 0;
	for (const char* inst : instructions) {
		centering_text(instructionsWin, i + 1, inst);
		i++;
	}
	wrefresh(instructionsWin);
}

void Menu::render() {
	titleDisplay();
	instructionsDisplay();

	bool in = false;
	do {
		update(selected);
		in = handleInput();
	} while(!in);
}