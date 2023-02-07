#include "../../include/objects/projectile.hpp"
#include "../../include/util/engine.hpp"


Projectile::Projectile() {
    icon = "-";
    current_position = {1, 1};
    direction = DIR_EAST;     
    alive = false;
    current_room_win = stdscr;
}

Projectile::Projectile(const char* icon, Position position, int direction, int damage, int moving_frequency, bool isAllied, WINDOW* win) : Entity(icon,position,win){
    this->direction = direction;
    moving_frequency_multiplyer = moving_frequency;
    duration <int, std::ratio <1,1000 > > one_millisecond (1);
    this->moving_frequency = moving_frequency_multiplyer * one_millisecond;
    last_time_moved = system_clock::now();
    alive = true;
    this->isAllied = isAllied;
    this->damage = damage;
}

void Projectile::spawn(Position position) {
    wattron(current_room_win, COLOR_PAIR(PROJCTL_PAIR));
    mvwprintw(current_room_win, position.y, position.x, icon);
    wattroff(current_room_win, COLOR_PAIR(PROJCTL_PAIR));
}

void Projectile::deleteIcon() {
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
}

void Projectile::setPosition(Position set) {
    current_position = set;
}

void Projectile::move() {
    deleteIcon();
    if((!collisionWithRoomWall(current_position + dirToPosition(direction))) && (!outOfBorder())) {
        wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
        mvwprintw(current_room_win, current_position.y, current_position.x, " ");
        wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
        current_position = current_position + dirToPosition(direction);
        spawn(current_position);
    }
    else {
        alive = false;
    }
}

void Projectile::checkIfTimeToMove(system_clock::time_point time_now) {
    if(time_now > last_time_moved + moving_frequency) {
        move();
        last_time_moved = time_now;
    }
}

bool Projectile::collisionWithRoomWall(Position pos) {
    bool collided = false;
    int k = mvwinch(current_room_win, pos.y, pos.x) & A_CHARTEXT;

    if((k == 35) || (k == 88) || (k == 89) || (k == '^')) {   
        collided = true;
    }

    return collided;

    //35 = "#"   ossia i muri
    //88 = "X"   ossia le porte chiuse
    //89 = "Y"   ossia le porte aperte
}

bool Projectile::outOfBorder() {
    bool outofb = false;
    int xmax, ymax;
    getmaxyx(current_room_win, ymax, xmax);
    if((current_position.y <= 0) || (current_position.y > ymax) || (current_position.x <= 0) || (current_position.x > xmax)) {
        outofb = true;
    }
    return outofb;
}

bool Projectile::checkifAllied(){
    return isAllied;
}

void Projectile::setDamage(int damage) {
    this->damage = damage;
}

int Projectile::getDamage() {
    return this->damage;
}
