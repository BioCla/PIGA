#ifndef GAME_MAP
#define GAME_MAP

#include "../objects/board.hpp"
#include "../util/graph.tpp"

#include "game_score.hpp"

void createNewRoom(int current_room_level, Graph<Board>& game_map);
void moveToRoom(int level_number, Graph<Board>& game_map, Board& board, Character& player);
bool updateMap(Graph<Board>& game_map, Board& board, Character& player);

#endif