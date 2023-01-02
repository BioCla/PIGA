#include "../../include/classes/Player.hpp"
#include "../../include/util/curses_comodity_functions.hpp"

input Player::inputMap [] = {
	{ 'w', [] { move(UP); } },
	{ 's', [] { move(DOWN); } },
	{ 'a', [] { move(LEFT); } },
	{ 'd', [] { move(RIGHT); } },

	{ KEY_UP, [] { stats.pos.dir = UP; } },
	{ KEY_DOWN, [] { stats.pos.dir = DOWN; } },
	{ KEY_RIGHT, [] { stats.pos.dir = RIGHT; } },
	{ KEY_LEFT, [] { stats.pos.dir = LEFT; } },

	/* Debug */
	{ 'f', [] { takeDamage(10); } },
	{ 'g', [] { heal(10); } },
	{ 'h', [] { takeDamage(5); } },
	{ 'j', [] { heal(5); } },
	{ 'k', [] { takeDamage(1); } },
	{ 'l', [] { heal(1); } },
};
	
void Player::inputHandler(int ch) {
	for (const input& in : inputMap) {
		if (ch == in.key) {
			HANDLE_INPUT(in);
			return;
		}
	}
}

int Player::health(bool mode) {
	int SWPair = PAIR_NUMBER(SW->_attrs);
	int numHearts = (int)round(stats.health / 10.0);
	
	if (mode) {
		setcolor(SW, dcantor(SWPair));
		mvwprintw(SW, 1, 1, "Health: ");
		unsetcolor(SW, dcantor(SWPair));
		setcolor(SW, COLOR_RED, COLOR_GREEN);
		for (int i = 0; i < numHearts; i++) {
			waddstr(SW, "<3");
		}
		setcolor(SW, COLOR_BLACK, COLOR_WHITE);
		int numEmptyHearts = stats.maxHealth / 10 - numHearts;
		for (int i = 0; i < numEmptyHearts; i++) {
			waddstr(SW, "<3");
		}
		unsetcolor(SW, COLOR_BLACK, COLOR_WHITE);
	} else {
		setcolor(SW, dcantor(SWPair));
		updateString(SW, 1, 1, "Health: %d/%d", stats.health, stats.maxHealth);
		unsetcolor(SW, dcantor(SWPair));
	}
	return (mode ? numHearts : stats.health);
}

void Player::renderStats() {
	health(0);
	wrefresh(SW);
}

entityPos Player::getPosition() {
	return stats.pos;
}

void Player::render() {
	Entity::render();
	renderStats();
}

bool Player::legalMove(point pos) {
	return Entity::legalMove(pos) 
	/* check for Items */;
}