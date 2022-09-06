#include "../lib/enemy.hpp"
#include "../lib/board.hpp"
#include "../lib/engine.hpp"
#include <chrono>
#include <ctime>

Enemy::Enemy(){
    
    icon = "A";
    health = 10;
    max_health = 10;
    damage = 2;
    current_position = {20,20};
    pathID = 1;
    //altri parametri
    // [creare più sottoclassi di nemici]
}

Enemy::Enemy(const char* icon, int max_health, int damage, Position spawn_position, int pathID, duration <int, std::ratio <1,1000> > idle_time){

    this->icon = icon;
    current_position = spawn_position;
    this->max_health=max_health;
    this->damage=damage;
    this->pathID=pathID;
    this->idle_time=idle_time;
    last_time_moved = system_clock::now();
}

void Enemy::spawn(Position position) {
    mvprintw(position.y, position.x, icon);    
}

Position Enemy::getCurrentPosition(){
    return current_position;
}

void Enemy::setHealth(int set){
    health = set;
}

int Enemy::getHealth(){
    return health;
}

void Enemy::setDamage(int set){
    damage = set;
}

int Enemy::getDamage(){
    return damage;
}

void Enemy::deleteIcon() {
    mvprintw(current_position.y, current_position.x, " ");
}

void Enemy::setCurrentRoom(WINDOW* set) {
    current_room_win = set;
}

WINDOW* Enemy::getCurrentRoom() {
    return current_room_win;
}


void Enemy::moveEnemy(){
    switch (pathID){
        /*
        case 1:
            pathID++;
            deleteIcon();
            current_position.y = current_position.y - 1;
            spawn(current_position);
            break;
        case 2:
            pathID++;
            deleteIcon();
            current_position.x = current_position.x - 1;
            spawn(current_position);
            break;
        case 3:
            pathID++;
            deleteIcon();
            current_position.y = current_position.y + 1;
            spawn(current_position);
            break;
        case 4:
            pathID=1;
            deleteIcon();
            current_position.x = current_position.x + 1;
            spawn(current_position);
            break;
        */
        case DIR_NORTH:
            if (legalMove(current_position.x, current_position.y-1)){
                deleteIcon();
                current_position.y--;
                spawn(current_position);
            }                        
            break;            
        case DIR_EAST:
            if (legalMove(current_position.x+1, current_position.y)){
                deleteIcon();
                current_position.x++;
                spawn(current_position);
            }
            break;               
        case DIR_SOUTH:
            if (legalMove(current_position.x, current_position.y+1)){
                deleteIcon();
                current_position.y++;;
                spawn(current_position);
            }
            break;   
        case DIR_WEST:
            if (legalMove(current_position.x-1, current_position.y)){
                deleteIcon();
                current_position.x--;
                spawn(current_position);
            }
            break;   
    }
    pathID = rand() % 4;
}

bool Enemy::legalMove(int posx, int posy) {
    int k;
    k =  mvinch(posy,posx);
    return ((k & A_CHARTEXT) == PAVE);
} 


void Enemy::checkIfTimeToMove(system_clock::time_point time_now) {
    if(time_now > last_time_moved + idle_time) {
        moveEnemy();
        last_time_moved = time_now;
    }
}