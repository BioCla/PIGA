#include "../../include/objects/character.hpp"
#include "../../include/objects/item.hpp"

Character::Character() {
    icon = "@";
    max_health = 30;
    health = max_health;
    damage = 5;   //numero a caso
    projectile_icon = "-";
    projectile_moving_frequency = 1000;
    last_direction_taken = DIR_EAST;   //arbitrario. se spara senza muoversi i proiettili devono andare da qualche parte
    current_room_win = stdscr;
    weapon = BASE;
}

Character::Character(const char * icon, Position pos, int max_health, const char * projectile_icon, int damage, int projectile_moving_frequency, WINDOW* win):Entity(icon, pos, win){
    this->max_health = max_health;
    health = max_health;  
    this->projectile_icon = projectile_icon;
    this->projectile_moving_frequency = projectile_moving_frequency;
    last_direction_taken = DIR_NORTH;
    this->damage = damage;
    weapon = BASE;
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

int Character::getHearts() {
    return num_hearts;
}

//si possono mettere valori negativi per far prendere danno al personaggio
void Character::updateHealth(int mod) {
    health = health + mod;
    if (health > max_health) health = max_health;
    if(health <= 0) alive = false;
    updateHearts();
}

void Character::setHealth(int set) {
    health = set;
    updateHealth(0);   //controlla morte/troppa salute
}

int Character::getHealth() {
    return health;
}

void Character::setMaxHealth(int set) {
    max_health = set;
}

int Character::getMaxHealth() {
    return max_health;
}

void Character::setDamage(int set) {
    damage = set;
}

int Character::getDamage() {
    return damage;
}

void Character::setProjectileIcon(const char * set) {
    projectile_icon = set;
}

const char * Character::getProjectileIcon() {
    return projectile_icon;
}

void Character::setProjectileMovingFrequency(int set) {
    projectile_moving_frequency = set;
}

int Character::getProjectileMovingFrequency() {
    return projectile_moving_frequency;
}

void Character::setRoomWin(WINDOW* set) {
    current_room_win = set;
}

WINDOW* Character::getRoomWin() {
    return current_room_win;
}

int Character::getLastDirection() {
    return last_direction_taken;
}

void Character::deleteIcon() {
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
}

void Character::move(Position pos) {

    current_position = pos;
    wattron(current_room_win, COLOR_PAIR(PLAYER_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, icon);
    wattroff(current_room_win, COLOR_PAIR(PLAYER_PAIR));
    wrefresh(current_room_win);
}

void Character::HandleInput(int input){
    bool moving = false;    //se input è un tasto per muoversi, questo booleano si attiva, e con esso le funzioni per muoversi
                            //senza, il personaggio continua a muoversi nell'ultima direzione presa, come se pattinasse sul ghiaccio
    switch(input){

        /*si muove in su*/
        case 'w':
        case 'W':
            last_direction_taken = DIR_NORTH;
            moving = true;
            break;

        /*si muove a destra*/
        case 'd':
        case 'D':
            last_direction_taken = DIR_EAST;
            moving = true;
            break;

        /*si muove in giù*/
        case 's':
        case 'S':
            last_direction_taken = DIR_SOUTH;
            moving = true;
            break;

        /*si muove a sinistra*/
        case 'a':
        case 'A':
            last_direction_taken = DIR_WEST;
            moving = true;
            break;

        /* spara */
        case 'f':
        case 'F':
            shoot();
            break;

        default:
            break;   
    }

    if (moving) {
        if (legalMove(current_position + dirToPosition(last_direction_taken))) {
            deleteIcon();
            move(current_position + dirToPosition(last_direction_taken));
        }  
        else if (steppedOnEnemy(current_position + dirToPosition(last_direction_taken))) {
            this->health = this->health - 5;
        }
    }

    wrefresh(current_room_win);
}

bool Character::legalMove(Position pos) {
    int k;
    k =  mvwinch(current_room_win, pos.y, pos.x);
    k = k & A_CHARTEXT;
    return ((k == PAVE) || (k == 42) || (k == 79) || (k == 75) || (k == 72) || (k == 68) || (k == 83) || (k == 104) || (k == 100) || (k == 115) || (k == 76) || (k == 66) || (k == 86) || (k == 80));   
    //----  il personaggio può camminare SOLO su questi caratteri:  -------
    //42 = "*", 79 = "O"   ossia i proiettili
    //72 = "H"             ossia gli item (i seguenti sono tutti item)
    //75 = "K"             
    //68 = "D"
    //83 = "S"
    //104 = "h"
    //100 = "d"
    //115 = "s"
    //76 = "L"
    //66 = "B"
    //86 = "V"
    //80 = "P"
} 

bool Character::steppedOnEnemy(Position pos) {
    int k;
    k =  mvwinch(current_room_win, pos.y, pos.x);
    k = k & A_CHARTEXT;
    return (k == 65);   //65 = "A"    ossia i nemici
}

void Character::shoot() {
    switch(weapon) {
        case BOMB:
            createSuperProjectile(superProjectilesList, "O", current_position, last_direction_taken, damage, projectile_moving_frequency, 600, projectile_moving_frequency*2, projectile_icon, current_room_win);
            break;
        case LASER:
            createLaser(projectilesList);
            break;
        case BASE:
        default:
            createProjectile(last_direction_taken, projectilesList);
            break;
    }
    
}

void Character::createProjectile(int direction, List<Projectile> *projectilesList) {    
    Projectile newProjectile = Projectile(projectile_icon, current_position, direction, damage, projectile_moving_frequency, true ,current_room_win);
    newProjectile.move();
    projectilesList->headInsert(newProjectile);
}

void Character::createLaser(List<Projectile>* projectilesList) {
    Position pos;
    Projectile newProjectile;

    //sposta    pos    per entrare nel ciclo sotto
    switch(last_direction_taken) {
        case DIR_NORTH:
        case DIR_SOUTH:
            projectile_icon = "|";
            break;

        case DIR_EAST:
        case DIR_WEST:
            projectile_icon = "-";
            break;

        default:
            break;
    }
    pos = this->current_position + dirToPosition(last_direction_taken);

    //spawna proiettili finchè non incontra un muro o qualsiasi cosa che blocchi un laser
    while(legalMove(pos)) {

        newProjectile = Projectile(projectile_icon, pos, last_direction_taken, damage, 1, true ,current_room_win);
        projectilesList->headInsert(newProjectile);

        pos = pos + dirToPosition(last_direction_taken);
    }

}

Weapon Character::getWeapon() {
    return weapon;
}

void Character::setWeapon(Weapon weapon) {
    this->weapon = weapon;
}

void Character::addToInventory(int ID) {
	
}

void Character::removeFromInventory(int ID) {
	
}

List<int> Character::getInventory() {
	return inventory.getInventory();
}

void Character::setProjectilesList(List<Projectile> *projectilesList) {
    this->projectilesList = projectilesList;
}

List<Projectile>* Character::getProjectilesList() {
    return this->projectilesList;
}

void Character::setSuperProjectilesList(List<SuperProjectile> *superProjectilesList) {
    this->superProjectilesList = superProjectilesList;
}

List<SuperProjectile>* Character::getSuperProjectilesList() {
    return this->superProjectilesList;
}