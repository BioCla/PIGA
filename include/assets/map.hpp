#ifndef GAME_MAP
#define GAME_MAP

#include "../util/graph.tpp"
#include "../objects/board.hpp"


Graph<Board> game_map;


void createNewRoom(int direction);

#endif