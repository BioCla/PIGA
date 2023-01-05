#include "../../include/util/string_override.hpp"
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

const char* itemTypeToString(itemType type) {
	switch (type) {
		case DEBUFF:
			return "DEBUFF";
		case BUFF:
			return "BUFF";
		case WEAPON:
			return "WEAPON";
		case DEBUG:
			return "DEBUG";
		case ARTIFACT:
			return "ARTIFACT";
		default:
			return "UNKNOWN";
	}
}

const char* dirToString(direction dir) {
	switch (dir) {
		case UP:
			return "UP";
		case DOWN:
			return "DOWN";
		case RIGHT:
			return "RIGHT";
		case LEFT:
			return "LEFT";
		default:
			return "UNKNOWN";
	}
}

int longestString(const char* arr[], int size) {
	int max_length = 0;
	for (int i = 0; i < size; ++i) {
		int length = 0;
		const char* str = arr[i];
		while (*str != '\0') {
			++length;
			++str;
		}
		max_length = std::max(max_length, length);
	}
	return max_length;
}