
//questo include genera l'errore multiple definition of game_map

#include "../../include/assets/map.hpp"


//se copiate e incollate questa funzione nel file main.cpp, e scommentate la riga sotto il tasto 'm' sempre nel main, dovrebbe farvi
//creare quante stanze volete. naturalmente se lo fate non premete 'o' nella stessa sessione altrimenti sballate tutto

void createNewRoom(int current_room_level, Graph<Board>& game_map) {
    Board new_level = Board(BOARD_ROWS, BOARD_COLS, current_room_level + 1);
    game_map.AddVertex(new_level);
	game_map.AddEdge(current_room_level, current_room_level + 1);
	game_map.AddEdge(current_room_level + 1, current_room_level);
}

void moveToRoom(int level_number, Graph<Board>& game_map, Board& board, Character& player) {
    board = game_map.GetVertex(level_number);
    board.initialize();

    player.setProjectilesList(board.getProjectilesList());
    player.setSuperProjectilesList(board.getSuperProjectilesList());
    player.setCurrentRoom(board.getWin());

    wrefresh(board.getWin());
}