#include "../../include/assets/entity.hpp"



Entity::Entity() {
    alive = true;
    icon = "E";
    current_position.x = 2;
    current_position.y = 2;
    current_room_win = stdscr;
}

Entity::Entity(const char* icon, Position initial_position, WINDOW* win) {
    alive = true;
    this->icon = icon;
    current_position = initial_position;
    this->current_room_win = win;  
}

void Entity::setAlive(bool alive) {
    this->alive = alive;
}

bool Entity::isAlive() {
    return alive;
}

void Entity::setIcon(const char* new_icon){
    icon = new_icon;
}

const char* Entity::getIcon() {
    return icon;
}

Position Entity::getCurrentPosition() {
    return current_position;
}

void Entity::spawn() {
    mvwprintw(current_room_win, current_position.y, current_position.x, icon);
}

void Entity::spawn(Position position) {
	current_position = position;
	spawn();
}

void Entity::deleteIcon() {
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
}

void Entity::move(int new_pos_x, int new_pos_y) {
    deleteIcon();
    current_position.x = new_pos_x;
    current_position.y = new_pos_y;
    spawn();
}

WINDOW* Entity::getWin() {
    return current_room_win;
}

void Entity::setCurrentRoom(WINDOW* set) {
    current_room_win = set;
}
