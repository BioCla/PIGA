#include "../lib/character.hpp"
#include "../lib/item.hpp"

Character::Character() {
    icon = "@";
    max_health = 30;
    health = max_health;
    damage = 5;   //numero a caso
    projectile_icon = "-";
    projectile_moving_frequency = 1000;
    last_direction_taken = DIR_EAST;   //arbitrario. se spara senza muoversi i proiettili devono andare da qualche parte
    current_room_win = stdscr;
}

Character::Character(const char * icon, Position pos, int max_health, const char * projectile_icon, int damage, int projectile_moving_frequency, WINDOW* win):Entity(icon, pos, win){
    this->max_health = max_health;
    health = max_health;  
    this->projectile_icon = projectile_icon;
    this->projectile_moving_frequency = projectile_moving_frequency;
    last_direction_taken = DIR_NORTH;
    this->damage = damage;
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

void Character::move(int x, int y) {

    current_position.x=x;
    current_position.y=y;
    wattron(current_room_win, COLOR_PAIR(PLAYER_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, icon);
    wattroff(current_room_win, COLOR_PAIR(PLAYER_PAIR));
    wrefresh(current_room_win);
}

void Character::HandleInput(int input){

	/**
	 * Secondo me e' meglio generalizzare la funzione e fare un check singolo dopo ogni mossa:
	 * case *:
	 * 	PlayerMove(...) {...}
	 * default:
	 * 	break;
	 * 
	 * if(!legalMove(...)) {
	 * 	PlayerMovePrevious(); // Il quale richiederebbe di segnare la posizione precedente del personaggio
	 * } else if (steppedOnArtifact) {
	 * 	...
	 * } else if (steppedOnEnemy) {
	 * 	...
	 * }
	 * 
	 * Tutto il  blocco del check puo' essere messo in una funzione separate di un namespace o come metodo della classe "character"
	 */
	// - Brian

    switch(input){
        /*si muove in su*/
        case 'w':
        case 'W':
            last_direction_taken = DIR_NORTH;
            if (legalMove(current_position.x, current_position.y - 1)) {
                if(steppedOnArtifact(current_position.x, current_position.y - 1)) {
                    //non lo so fai qualcosa
                    //updateHealth(+10) non lo so
                }
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));

                current_position.y--;
                move(current_position.x, current_position.y);
            }
            else if (steppedOnEnemy(current_position.x, current_position.y - 1)) {
                this->health = this->health - 5;
            }
            break;
        /*si muove a destra*/
        case 'd':
        case 'D':
            last_direction_taken = DIR_EAST;
            if(legalMove(current_position.x + 1, current_position.y)) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.x++;
                move(current_position.x, current_position.y);
            }
            else if (steppedOnEnemy(current_position.x + 1, current_position.y)) {
                this->health = this->health - 5;
            }
            break;
        /*si muove in giù*/
        case 's':
        case 'S':
            last_direction_taken = DIR_SOUTH;
            if(legalMove(current_position.x, current_position.y + 1)) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.y++;
                move(current_position.x, current_position.y);
            }
            else if (steppedOnEnemy(current_position.x, current_position.y + 1)) {
                this->health = this->health - 5;
            }
            break;
        /*si muove a sinistra*/
        case 'a':
        case 'A':
            last_direction_taken = DIR_WEST;
            if(legalMove(current_position.x - 1, current_position.y)) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.x--;
                move(current_position.x, current_position.y);
            }
            else if (steppedOnEnemy(current_position.x - 1, current_position.y)) {
                this->health = this->health - 5;
            }
            break;

        default:
            break;   
    }

    wrefresh(current_room_win);
}

bool Character::legalMove(int posx, int posy) {
    int k, kk;
    k =  mvwinch(current_room_win, posy,posx);
    kk = k & A_CHARTEXT;
    return ((kk == PAVE) || (kk == 42) || (kk == 79));   //42 = "*", 79 = "O"   ossia i proiettili
} 

bool Character::steppedOnEnemy(int posx, int posy) {
    int k, kk;
    k =  mvwinch(current_room_win, posy,posx);
    kk = k & A_CHARTEXT;
    return (kk == 65);   //65 = "A"    ossia i nemici
}

bool Character::steppedOnArtifact(int posx, int posy) {
   bool flag = false;
    /*
    dalla classe direi ROOM si prende il carattere alle coordinate (posx, posy) e se è un artefatto
    */
   return flag;
}

void Character::shoot(List<Projectile> *projectilesList) {
    //controlla se il tempo di ricarica è passato
    createProjectile(last_direction_taken, projectilesList);
}

void Character::createProjectile(int direction, List<Projectile> *projectilesList) {    
    Projectile newProjectile = Projectile(projectile_icon, current_position, direction, damage, projectile_moving_frequency, current_room_win);
    newProjectile.move();
    (*projectilesList).headInsert(newProjectile);
}

void Character::addToInventory(int ID) {
	
}

void Character::removeFromInventory(int ID) {
	
}

List<int> Character::getInventory() {
	return inventory.getInventory();
}