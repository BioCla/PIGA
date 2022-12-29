#include "../../include/classes/Player.hpp"
#include "../../include/util/math_override.tpp"

#define SW stats.gameBoard.getStatusWindow()

input Player::inputMap [] = {
	{ 'w', [] { move(UP); } },
	{ 's', [] { move(DOWN); } },
	{ 'a', [] { move(LEFT); } },
	{ 'd', [] { move(RIGHT); } },

	{ KEY_UP, [] { stats.pos.dir = UP; } },
	{ KEY_DOWN, [] { stats.pos.dir = DOWN; } },
	{ KEY_RIGHT, [] { stats.pos.dir = RIGHT; } },
	{ KEY_LEFT, [] { stats.pos.dir = LEFT; } },
};
	
void Player::inputHandler(int ch) {
	for (const input& in : inputMap) {
		if (ch == in.key) {
			HANDLE_INPUT(in);
			return;
		}
	}
}

void Player::renderStats() {
	int SWPair = PAIR_NUMBER(SW->_attrs);
	setcolor(SW, dcantor(SWPair));
	mvwprintw(SW, 1, 1, "Health: %d/%d", stats.health, stats.maxHealth);
	unsetcolor(SW, dcantor(SWPair));
	wrefresh(SW);
}

entityPos Player::getPosition() {
	return stats.pos;
}

void Player::render() {
	Entity::render();
	renderStats();
}