

#include "../../include/assets/map.hpp"


void createNewRoom(int current_room_level, Graph<Board>& game_map) {
    Board new_level = Board(BOARD_ROWS, BOARD_COLS, current_room_level + 1);
    game_map.AddVertex(new_level);
	game_map.AddEdge(current_room_level, current_room_level + 1);
	game_map.AddEdge(current_room_level + 1, current_room_level);
}

void moveToRoom(int level_number, Graph<Board>& game_map, Board& board, Character& player) {
    if(!game_map.HasEdge(board.getLevelNumber(), level_number)) {
        createNewRoom(board.getLevelNumber(), game_map);
    }
    board = game_map.GetVertex(level_number);
    board.initialize();

    player.setProjectilesList(board.getProjectilesList());
    player.setSuperProjectilesList(board.getSuperProjectilesList());
    player.setCurrentRoom(board.getWin());

    wrefresh(board.getWin());
}

bool updateMap(Graph<Board>& game_map, Board& board, Character& player) {
    bool player_changed_room = false;

    //salva la board attuale nel game_map
    game_map.SetVertex(board.getLevelNumber(), board);

    Position player_position = player.getCurrentPosition();
    int current_room_level = board.getLevelNumber();

    if((compare(player_position, {0, 16})) || (compare(player_position, {0, 17}))) {
        if(current_room_level != 0) {    //non esistono stanze a sinistra della stanza 0
            moveToRoom(current_room_level - 1, game_map, board, player);
            player.move({85, player.getCurrentPosition().y});
            
            player_changed_room = true;
        }
    }

    if((compare(player_position, {86, 16})) || (compare(player_position, {86, 17}))) {
        moveToRoom(current_room_level + 1, game_map, board, player);
        player.move({1, player.getCurrentPosition().y});

        player_changed_room = true;
    }

    return player_changed_room;

}

