#include "../../include/classes/Player.hpp"

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

entityPos Player::getPosition() {
	return stats.pos;
}