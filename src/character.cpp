#include "../lib/character.hpp"

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
    max_health = 30;
    health = max_health;
    current_position.x = x;
    current_position.y = y;
}

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

void Character::PlayerMove(int x, int y) {
    wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);

    current_position.x=x;
    current_position.y=y;
    
    win = newwin(1, 1, y, x);
    mvwprintw(win, 0, 0, icon);
    wrefresh(win);
    
    //mvprintw(y, x, "@");
    //mvprintw(200, 200,"a");
    //move(current_position.y, current_position.x);
}

Position Character::getCurrentPosition() {
    return current_position;
}

void Character::HandleInput(int input){
    int desired_pos_x, desired_pos_y;
    switch(input){
        /*si muove in su*/
        case 'w':
        case 'W':
            current_position.y--;
            PlayerMove(current_position.x, current_position.y);
            break;
        /*si muove a destra*/
        case 'd':
        case 'D':
            current_position.x++;
            PlayerMove(current_position.x, current_position.y);
            break;
        /*si muove in giù*/
        case 's':
        case 'S':
            current_position.y++;
            PlayerMove(current_position.x, current_position.y);
            break;
        /*si muove a sinistra*/
        case 'a':
        case 'A':
            current_position.x--;
            PlayerMove(current_position.x, current_position.y);
            break;

        default:
            break;   
    }

    bool legal = true;     //starebbe tipo per legal move, o qualcosa che è permesso fare insomma
                    //qua in mezzo metteremo varie chiamate a funzioni per verificare che il personaggio possa muoversi

}

