#ifdef __linux__
    #include <curses.h>
#elif _WIN32
    #include <ncurses/ncurses.h>
#endif

#ifndef STD_SYSTEM_LIB
#define STD_SYSTEM_LIB
	#include <ctime>
	#include <math.h>
	#include <chrono>
	#include <string>
	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <functional>
#endif

#define KEY_BUFFER_SIZE 4
#define conv 1000 / 255

#define SYS_CLOCK std::chrono::system_clock
#define HRC std::chrono::high_resolution_clock
#define STD_DUR std::chrono::duration
#define STD_DUR_CAST std::chrono::duration_cast
#define TIME_DURATION STD_DUR<float, std::ratio<1ll, 1000000000ll>>