#include "../lib/character.hpp"
#include "../lib/engine.hpp"

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

WINDOW * Character::getWin() {
    return win;
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

void Character::setProjectileIcon(char set) {
    projectile_icon = set;
}

char Character::getProjectileIcon() {
    return projectile_icon;
}

void Character::setRoomWin(WINDOW* set) {
    current_room_win = set;
}

WINDOW* Character::getRoomWin() {
    return current_room_win;
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
            if (legalMove(current_position.x - getbegx(current_room_win), current_position.y - 1 - getbegy(current_room_win))) {
                if(steppedOnArtifact(current_position.x, current_position.y - 1)) {
                    //non lo so fai qualcosa
                    //updateHealth(+10) non lo so
                }
                current_position.y--;
                PlayerMove(current_position.x, current_position.y);
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
            if(legalMove(current_position.x + 1 - getbegx(current_room_win), current_position.y - getbegy(current_room_win))) {
                current_position.x++;
                PlayerMove(current_position.x, current_position.y);
            }
            else if (steppedOnEnemy(current_position.x + 1, current_position.y)) {
                //calcoladanno();
            }
            break;
        /*si muove in giù*/
        case 's':
        case 'S':
            if(legalMove(current_position.x - getbegx(current_room_win), current_position.y + 1 - getbegy(current_room_win))) {
                current_position.y++;
                PlayerMove(current_position.x, current_position.y);
            }
            else if (steppedOnEnemy(current_position.x, current_position.y + 1)) {
                //calcoladanno();
            }
            break;
        /*si muove a sinistra*/
        case 'a':
        case 'A':
            if(legalMove(current_position.x - 1 - getbegx(current_room_win), current_position.y - getbegy(current_room_win))) {
                current_position.x--;
                PlayerMove(current_position.x, current_position.y);
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
    bool legal = true;

    if(((mvwinch(current_room_win, posy, posx) & A_CHARTEXT) == 120) || 
        ((mvwinch(current_room_win, posy, posx) & A_CHARTEXT) == 113)) {
        legal = false;
    }
    else if(false) {
        legal = false;
    }

    
    //qua ci vuole una funzione che penso verrà dalla classe delle stanze che ritorni il carattere date due coordinate
    //così fai if(carattereAllaPosizione(x,y) == '|') legal = false; else if carattere == '-' legal = false;   eccetera
    

    return legal;
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