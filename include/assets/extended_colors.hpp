#include "curses_lib_selector.hpp"

#define CONV_RATIO 1000 / 255

#define comp(r, g, b) (r << 16) | (g << 8) | b
#define dcomp(hex) (hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF

#define init_RGB(short, r, g, b) init_color(short, r * CONV_RATIO, g * CONV_RATIO, b * CONV_RATIO)
#define init_HEX(short, hex) init_color(short, dcomp(hex) * CONV_RATIO)

/*
Only modify this to add or remove colors according to the given structure:
	X(NAME_FORMAT, comp(R, G, B)) \ // <- Don't forget the backslash at the end of the line
	Where:
		NAME_FORMAT is the name of the color in the format: COLOR_NAME
		R, G, B are the values of the color in RGB format
		comp(R, G, B) is the color (can also be of type 0xRRGGBB or int)
Be sure to not use numbers 0-7 as we do not want to mess with the default colors.
*/

#define CC \
	X(DARK_CHARCOAL, 	comp(50, 50, 50))  		/* 0x323232 */\
	X(GRANITE_GRAY, 	comp(100, 100, 100)) 	/* 0x646464 */\
	X(VIB_BLUE, 		comp(0, 0, 255)) 		/* 0x0000FF */