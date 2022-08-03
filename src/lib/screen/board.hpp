#pragma once
#include <ncursesw/ncurses.h>


class Board{
    private:
        WINDOW *board_win;
        int height, width;

    public:
        //Board();
        Board(int height, int width);
        void initialize();
        void addBorder();
        void clear();
        void refresh();
        


};

