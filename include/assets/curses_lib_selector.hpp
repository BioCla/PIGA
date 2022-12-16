#ifdef __linux__
    #include <curses.h>
#elif _WIN32
    #include <ncurses/ncurses.h>
#endif

#ifndef STD_SYSTEM_LIB
	#define STD_SYSTEM_LIB
	#include <stdlib.h>
	#include <stdio.h>
	#include <iostream>
	#include <ctime>
#endif