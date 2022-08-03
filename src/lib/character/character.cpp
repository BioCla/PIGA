#include "character.hpp"

Character::Character() {
    icon = "@";
    max_health = 30;
    health = max_health;
    damage = 5;   //numero a caso
    projectile_icon = '-';
    win = newwin(1, 1, 0, 0);
    mvwprintw(win, 0, 0, icon);
    wrefresh(win);
}

Character::Character(int x, int y){
    icon = "@";
    current_position.x = x;
    current_position.y = y;
}

/*Character::Character(){
    printw("è stato usato il costruttore default");
}*/

void Character::updateHearts() {
    num_hearts = ((health + 9) / 10);
}
/* in questo modo:
salute    num_cuori
30...........3
29...........3
21...........3
20...........2
11...........2
10...........1
5............1
1............1
0............0
*/

//si possono mettere valori negativi per far prendere danno al personaggio
void Character::updateHealth(int mod) {
    health = health + mod;
}

void Character::setHealth(int set) {
    health = set;
}

int Character::getHealth() {
    return health;
}

void Character::setDamage(int set) {
    damage = set;
}

int Character::getDamage() {
    return damage;
}

void Character::setProjectileIcon(char set) {
    projectile_icon= set;
}

char Character::getProjectileIcon() {
    return projectile_icon;
}


void Character::PlayerMove(Position set) {
    current_position.x=set.x;
    current_position.y=set.y;
    mvprintw(set.y, set.x, "@");
    move(current_position.y, current_position.x);
}

Position Character::getCurrentPosition() {
    return current_position;
}

void Character::HandleInput(int input){
    switch(input){
        /*si muove in su*/
        case 'w':
        case 'W':
            --current_position.y;
            PlayerMove(current_position);
            break;

        /*si muove in giù*/
        case 's':
        case 'S':
            ++current_position.y;
            PlayerMove(current_position);
            break;

        /*si muove a sinistra*/
        case 'a':
        case 'A':
            --current_position.x;
            PlayerMove(current_position);
            break;

        /*si muove a destra*/
        case 'd':
        case 'D':
            ++current_position.x;
            PlayerMove(current_position);
            break;              

        default:
            break;   
    }
}

