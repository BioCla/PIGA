#include "board.hpp"

/*Board::Board(){
    int xMax, yMax;
    int height=10;
    int width=20;

    getmaxyx(stdscr, yMax, xMax);
    board_win = newwin(height, width, (yMax/2)-(height/2), (xMax/2)-(width/2));
    initialize();
}*/

Board::Board(int height, int width){
    int xMax, yMax;
    
    getmaxyx(stdscr, yMax, xMax);
    board_win = newwin(height, width, (yMax/2)-(height/2), (xMax/2)-(width/2));
    initialize();  
}

void Board::initialize(){
    clear();
    refresh();
}

void Board::addBorder(){
    box(board_win, 0, 0);
}

void Board::clear(){
    wclear(board_win);
    addBorder();
}

void Board::refresh(){
    wrefresh(board_win);
}


