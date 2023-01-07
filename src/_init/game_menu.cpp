#include "../../include/_init/game_menu.hpp"
#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/util/string_override.hpp"

int Menu::returnCode = 0;

option Menu::list[] = {
	{ "Start", [] { returnCode = 0; } },
	{ "Exit", [] { endwin(); std::exit(EXIT_SUCCESS); } },
};

const char* instructions[] = {
	"Use the up/down keys to navigate the menu",
	"Press enter to select an option",
};

const char* title[] = {
" _/\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\_           ",
" _\\/\\\\\\/////////\\\\\\_\\/////\\\\\\///____/\\\\\\//////////____/\\\\\\\\\\\\\\\\\\\\\\\\\\_        ",
"  _\\/\\\\\\_______\\/\\\\\\_____\\/\\\\\\______/\\\\\\______________/\\\\\\/////////\\\\\\_      ",
"   _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/______\\/\\\\\\_____\\/\\\\\\____/\\\\\\\\\\\\\\_\\/\\\\\\_______\\/\\\\\\_     ",
"    _\\/\\\\\\/////////________\\/\\\\\\_____\\/\\\\\\___\\/////\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_    ",
"     _\\/\\\\\\_________________\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\/////////\\\\\\_   ",
"      _\\/\\\\\\_________________\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_  ",
"       _\\/\\\\\\______________/\\\\\\\\\\\\\\\\\\\\\\_\\//\\\\\\\\\\\\\\\\\\\\\\\\/__\\/\\\\\\_______\\/\\\\\\_ ",
"        _\\///______________\\///////////___\\////////////____\\///________\\///_ ",
};

#define menuSize sizeof(list) / sizeof(list[0]) - 1
#define titleSize sizeof(title) / sizeof(title[0])
#define instSize sizeof(instructions) / sizeof(instructions[0])

Menu::Menu() {
	const char* menuOptions[menuSize];
	for (size_t i = 0; i < menuSize; i++) {
		menuOptions[i] = list[i].label.c_str();
	}	

	int menuwidth = longestString(menuOptions, menuSize) + 2;
	int titlewidth = longestString(title, titleSize) + 2;
	int instwidth = longestString(instructions, instSize) + 2;

	menuWin = 			newwin(menuSize + 3, 	menuwidth, 		getmaxy(stdscr) / 2 - 1, 			getmaxx(stdscr) / 2 - (menuwidth / 2) - 1);
	titleWin = 			newwin(titleSize + 2, 	titlewidth, 	getbegy(stdscr), 					getmaxx(stdscr) / 2 - (titlewidth / 2) - 1);
	instructionsWin = 	newwin(instSize + 2, 	instwidth, 		getmaxy(stdscr) - instSize - 2, 	getmaxx(stdscr) / 2 - (instwidth / 2) - 1);

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
			selected = selected == 0 ? menuSize : selected - 1;
			break;
		case KEY_DOWN:
			selected = selected == menuSize ? 0 : selected + 1;
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
	int i = 0;
	for (const char* t : title) {
		centering_text(titleWin, i + 1, t);
		i++;
	}
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