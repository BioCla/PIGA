#include "../../include/assets/game_score.hpp"

void updateGameScore(Board board, int& score, bool just_entered_new_room, int& previous_number_of_enemies) {
    if(just_entered_new_room) {
        previous_number_of_enemies = board.getEnemiesList()->listLength();
    }

    else {
        score += (previous_number_of_enemies - board.getEnemiesList()->listLength()) * 5;
    }
}