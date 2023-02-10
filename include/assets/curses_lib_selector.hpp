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
    #include <iomanip>
    #include <stdio.h>
    #include <sstream>
    #include <stdlib.h>
    #include <iostream>
    #include <functional>
    #include <unordered_map>
#endif

