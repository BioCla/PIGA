#include "../../include/util/string_override.hpp"
#include "../../include/util/math_override.tpp"
#include "../../include/assets/curses_lib_selector.hpp"
#include "../../include/assets/game_structures.hpp"

long unsigned int strlen(const char *p) {
	long unsigned int count = 0;
	while(*p!='\0') {
		count++;
		p++;
	}
	return count;
}

char* intstr(int input) {
	int num_size = mathy::numDigits(input);
	char *text = new char[num_size];
	sprintf(text, "%d", input);
	return text;
}

const char* dirToString(direction dir) {
	switch (dir) {
		case UP:
			return "UP\t";
		case DOWN:
			return "DOWN\t";
		case RIGHT:
			return "RIGHT\t";
		case LEFT:
			return "LEFT\t";
		default:
			return "UNKNOWN";
	}
}