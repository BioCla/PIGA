#include "../lib/enemy.hpp"
#include <chrono>

Enemy::Enemy(){
    en_win = newwin(1, 1, 20, 20);
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
    en_win = newwin(1,1, spawn_position.y, spawn_position.x);
    this->icon = icon;
    current_position = spawn_position;
    this->max_health=max_health;
    this->damage=damage;
    this->pathID=pathID;
    this->idle_time=idle_time;
    last_time_moved = system_clock::now();
}

void Enemy::spawn(WINDOW* win, Position position) {
    en_win = newwin(1, 1, position.y, position.x);
    mvwprintw(en_win, 0, 0, icon);
    wrefresh(en_win);    
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

