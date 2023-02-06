#include "../../include/objects/enemy.hpp"

Enemy::Enemy(){
    
    icon = "A";
    health = 10;
    damage = 2;
    current_position = {20,20};
    pathID = 1;
    pathing = 0;
    current_room_win = stdscr;
}

Enemy::Enemy(const char* icon, int max_health, int damage, Position spawn_position, int pathID, int idlemove, int idleshoot,WINDOW* win) : Entity(icon, spawn_position, win){
    duration <int, std::ratio <1,1000> > one_millisecond(1);
    this->health=max_health;
    this->damage=damage;
    this->pathID=pathID;
    this->idle_time_move=one_millisecond*idlemove;
    this->idle_time_shoot=one_millisecond*idleshoot;
    this->shootingTarget={0,0};
}

void Enemy::spawn(Position position) {
    wattron(current_room_win, COLOR_PAIR(ENEMY_PAIR));
    mvwprintw(current_room_win, position.y, position.x, icon);
    wattroff(current_room_win, COLOR_PAIR(ENEMY_PAIR));       
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

void Enemy::updateHealth(int mod){
    health+=mod;
    if (health<=0) this->alive=false;
}

void Enemy::moveUp(){
    deleteIcon();
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
    current_position.y--;
    spawn(current_position);   
}

void Enemy::moveLeft(){
    deleteIcon();
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
    current_position.x++;
    spawn(current_position);  
}

void Enemy::moveDown(){
    deleteIcon();
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
    current_position.y++;;
    spawn(current_position);  
}

void Enemy::moveRight(){
    deleteIcon();
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
    current_position.x--;
    spawn(current_position);
}

void Enemy::move(){
    switch (pathID){
        case RANDOM:
            switch (pathing){
                case DIR_NORTH:
                    if (legalMove(current_position.x, current_position.y-1)){
                        moveUp();
                    }                        
                    break;            
                case DIR_EAST:
                    if (legalMove(current_position.x+1, current_position.y)){
                        moveLeft();
                    }
                    break;               
                case DIR_SOUTH:
                    if (legalMove(current_position.x, current_position.y+1)){
                        moveDown();
                    }
                    break;   
                case DIR_WEST:
                    if (legalMove(current_position.x-1, current_position.y)){
                        moveRight();
                    }
                    break;   
            }
            pathing = rand() % 4;
            break;
        case STSLR:
            if(pathing==5){
                if (legalMove(current_position.x+1, current_position.y)){
                    moveLeft();
                }else pathing=6;   
            }else{
                if (legalMove(current_position.x-1, current_position.y)){
                    moveRight();
                }else pathing=5;
            }
            break;
        case STSUD:
            if(pathing==5){
                if (legalMove(current_position.x, current_position.y-1)){
                    moveUp();
                }else pathing=6;
            }else{
                if (legalMove(current_position.x, current_position.y+1)){
                    moveDown();
                }else pathing=5;         
            }
            break;
        case CHASE:
            //if (distance(current_position,shootingTarget)<2.5) return;
            switch (pathing){
                case DIR_NORTH:
                    if (legalMove(current_position.x, current_position.y-1)){
                        moveUp();
                    }                        
                    break;            
                case DIR_EAST:
                    if (legalMove(current_position.x+1, current_position.y)){
                        moveLeft();
                    }
                    break;               
                case DIR_SOUTH:
                    if (legalMove(current_position.x, current_position.y+1)){
                        moveDown();
                    }
                    break;   
                case DIR_WEST:
                    if (legalMove(current_position.x-1, current_position.y)){
                        moveRight();
                    }
                    break;   
            }
            pathing = findDirection();
            break;
    }
}

bool Enemy::legalMove(int posx, int posy) {
    int k;
    k =  mvwinch(current_room_win, posy,posx);
    return ((k & A_CHARTEXT) == PAVE);
} 

void Enemy::checkIfTimeToMove(system_clock::time_point time_now) {
    if(time_now > last_time_moved + idle_time_move) {
        move();
        last_time_moved = time_now;
    }
}

void Enemy::checkIfTimeToShoot(system_clock::time_point time_now, List<Projectile> *Projlist){
    if(time_now>last_time_shot + idle_time_shoot){
        Position p1 = this->current_position;
        int dir=findDirection();
        switch (dir){
            case DIR_NORTH:
                p1.y--;
                break;
            case DIR_SOUTH:
                p1.y++;
                break;
            case DIR_WEST:
                p1.x--;
                break;
            case DIR_EAST:
                p1.x++;
                break;
        }
        Projectile p = Projectile("*",p1,dir,damage, 100, false,current_room_win);
        (*Projlist).headInsert(p);
        last_time_shot = time_now;
    }
}


void Enemy::setShootingTarget(Position player_pos){
    this->shootingTarget=player_pos;
}

int Enemy::findDirection(){
    if (abs(shootingTarget.y - current_position.y) > abs(shootingTarget.x - current_position.x)){
        if (shootingTarget.y > current_position.y)
            return DIR_SOUTH;
        else return DIR_NORTH;
    }
    else {
        if (shootingTarget.x > current_position.x)
            return DIR_EAST;
        else return DIR_WEST;
    }
}