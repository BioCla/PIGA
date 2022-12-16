#include "../../include/util/string_override.hpp"
#include "../../include/util/math_override.tpp"
#include "../../include/assets/curses_lib_selector.hpp"

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
