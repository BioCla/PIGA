#include "../lib/character.hpp"
#include "../lib/engine.hpp"
#include "../lib/board.hpp"

Character::Character() {
    icon = "@";
    max_health = 30;
    health = max_health;
    damage = 5;   //numero a caso
    projectile_icon = "-";
    projectile_moving_frequency = 1000;
    last_direction_taken = DIR_EAST;   //arbitrario. se spara senza muoversi i proiettili devono andare da qualche parte
    projListHead = NULL;
}

Character::Character(int x, int y, const char * icon, int max_health, const char * projectile_icon, int projectile_moving_frequency){
    current_position.x = x;
    current_position.y = y;
    this->icon = icon;
    this->max_health = max_health;
    health = max_health;
    damage = 5;   
    this->projectile_icon = projectile_icon;
    this->projectile_moving_frequency = projectile_moving_frequency;
    last_direction_taken = DIR_NORTH;
    damage = 5;
    projListHead = NULL;
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
    if (health > max_health) health = max_health;
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

void Character::setIcon(const char* set) {
    icon = set;
}

const char* Character::getIcon() {
    return icon;
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

void Character::PlayerMove(int x, int y) {

    current_position.x=x;
    current_position.y=y;
    attron(COLOR_PAIR(PLAYER_PAIR));
    mvprintw(current_position.y, current_position.x, icon);
    attroff(COLOR_PAIR(PLAYER_PAIR));
}

Position Character::getCurrentPosition() {
    return current_position;
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
            if (legalMove(current_position.x, current_position.y - 1)) {
                if(steppedOnArtifact(current_position.x, current_position.y - 1)) {
                    //non lo so fai qualcosa
                    //updateHealth(+10) non lo so
                }
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                //Board::fillPoint(current_position.y, current_position.x); non so come implementare in modo che usi la classe Board e usi la funzione per riempire lo spazio
                current_position.y--;
                PlayerMove(current_position.x, current_position.y);
                last_direction_taken = DIR_NORTH;
            }
            else if (steppedOnEnemy(current_position.x, current_position.y - 1)) {
                //calcoladanno();
                /*
                penso si farà più o meno così:
                prendi icona nemico in quella posizione()
                da un qualche metodo nella classe ENEMY prendi il danno da collisione fisica (non per forza uguale a quello da proiettile)
                togli i punti vita  updateHealth(-dannodelmostro)
                e poi direi che rimangono lì sia il mostro che il personaggio
                inoltre si potrebbe fare che se un mostro va addosso al personaggio il personaggio viene spinto di una casella
                */
            }
            break;
        /*si muove a destra*/
        case 'd':
        case 'D':
            if(legalMove(current_position.x + 1, current_position.y)) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.x++;
                PlayerMove(current_position.x, current_position.y);
                last_direction_taken = DIR_EAST;
            }
            else if (steppedOnEnemy(current_position.x + 1, current_position.y)) {
                //calcoladanno();
            }
            break;
        /*si muove in giù*/
        case 's':
        case 'S':
            if(legalMove(current_position.x, current_position.y + 1)) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.y++;
                PlayerMove(current_position.x, current_position.y);
                last_direction_taken = DIR_SOUTH;
            }
            else if (steppedOnEnemy(current_position.x, current_position.y + 1)) {
                //calcoladanno();
            }
            break;
        /*si muove a sinistra*/
        case 'a':
        case 'A':
            if(legalMove(current_position.x - 1, current_position.y)) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.x--;
                PlayerMove(current_position.x, current_position.y);
                last_direction_taken = DIR_WEST;
            }
            else if (steppedOnEnemy(current_position.x - 1, current_position.y)) {
                //calcoladanno();
            }
            break;

        default:
            break;   
    }
}

bool Character::legalMove(int posx, int posy) {
    int k;
    k =  mvinch(posy,posx);
    return ((k & A_CHARTEXT) == PAVE);
} 

bool Character::steppedOnEnemy(int posx, int posy) {
    bool flag = false;
    /*
    qui stessa roba. se il carattere che hai a destra è quello di un nemico e te vai a destra ritorna true e 
    poi si calcola il danno
    */
    return flag;
}

bool Character::steppedOnArtifact(int posx, int posy) {
   bool flag = false;
    /*
    dalla classe direi ROOM si prende il carattere alle coordinate (posx, posy) e se è un artefatto
    */
   return flag;
}

void Character::shoot() {
    //controlla se il tempo di ricarica è passato
    //controlla se sta sparando attaccato ad un muro contro il muro
    createProjectile(last_direction_taken);
}

void Character::createProjectile(int direction) {
    projList *p = new projList;
    Projectile newProjectile = Projectile(projectile_icon, current_position, direction, projectile_moving_frequency);
    
    //head insert del nuovo proiettile
    p->next = projListHead;
    p->proj = newProjectile;
    
    //salva la nuova head
    projListHead = p;

    //stampa il proiettile
    projListHead->proj.moveProjectile();
}

projList* Character::getProjectilesShot() {
    return projListHead;
}