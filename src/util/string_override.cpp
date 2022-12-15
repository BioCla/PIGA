#include "../../include/util/string_override.hpp"

long unsigned int strlen(const char *p) {
	long unsigned int count = 0;
	while(*p!='\0') {
		count++;
		p++;
	}
	return count;
}
