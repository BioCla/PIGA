#include "../lib/projectile.hpp"
#include <ctime>

Projectile::Projectile() {
    proj_win = newwin(1, 1, 10, 10);
    icon = "*";
    current_position = {10, 10};
    direction = 1;
    //a caso, giusto per vederlo vagare sullo schermo
}

Projectile::Projectile(const char* icon, Position position, int direction) {
    proj_win = newwin(1, 1, position.y, position.x);
    this->icon = icon;
    current_position = position;
    this->direction = direction;
}

void Projectile::spawn(WINDOW* win, Position initial_position) {
    printw(icon, proj_win);
    refresh();
}

Position Projectile::getCurrentPosition() {
    return current_position;
}

void Projectile::setPosition(Position set) {
    current_position = set;
}