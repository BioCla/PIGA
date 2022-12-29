#include "curses_lib_selector.hpp"

#define NCR (1000 / 255)

#define comp(r, g, b) (r << 16) | (g << 8) | b
// This will convert the usual RGB (0-255) to the format used by ncurses (0-1000)
#define dcomp(hex) ((hex >> 16) & 0xFF) * NCR, ((hex >> 8) & 0xFF) * NCR, (hex & 0xFF) * NCR

#define init_RGB(short, r, g, b) init_color(short, r * NCR, g * NCR, b * NCR)
#define init_HEX(short, hex) init_color(short, dcomp(hex))

/*
Only modify this to add or remove colors according to the given structure:
	X(NAME_FORMAT, comp(R, G, B)) \ // <- Don't forget the backslash at the end of the line
	Where:
		NAME_FORMAT is the name of the color in the format: COLOR_NAME
		R, G, B are the values of the color in RGB format
		comp(R, G, B) is the color (can also be of type 0xRRGGBB or int)
*/

#define CC \
	X(DARK_CHARCOAL, 	comp(50, 50, 50))  		/* 0x323232 */\
	X(GRANITE_GRAY, 	comp(100, 100, 100)) 	/* 0x646464 */\
	X(VIB_BLUE, 		comp(0, 0, 255)) 		/* 0x0000FF */\
	X(VIB_GREEN, 		comp(0, 255, 0)) 		/* 0x00FF00 */\
	X(VIB_RED, 			comp(255, 0, 0)) 		/* 0xFF0000 */\
	X(VIB_YELLOW, 		comp(255, 255, 0)) 		/* 0xFFFF00 */\
	X(VIB_MAGENTA, 		comp(255, 0, 255)) 		/* 0xFF00FF */
