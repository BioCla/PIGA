#include "../lib/enemy.hpp"

Enemy::Enemy(){
    icon = "A";
    health = 10;
    max_health = 10;
    damage = 2;
    //altri parametri
    // [creare più sottoclassi di nemici]
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