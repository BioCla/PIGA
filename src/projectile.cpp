#include "../lib/projectile.hpp"
#include "../lib/engine.hpp"
#include "../lib/board.hpp"
#include <chrono>

Projectile::Projectile() {
    icon = "-";
    current_position = {1, 1};
    direction = DIR_EAST;     
    //a caso, giusto per vederlo vagare sullo schermo
    alive = true;
}

Projectile::Projectile(const char* icon, Position position, int direction, int moving_frequency) {
    this->icon = icon;
    current_position = position;
    this->direction = direction;
    moving_frequency_multiplyer = moving_frequency;
    duration <int, std::ratio <1,1000 > > one_millisecond (1);
    this->moving_frequency = moving_frequency_multiplyer * one_millisecond;
    last_time_moved = system_clock::now();
    alive = true;
}

void Projectile::spawn(Position position) {
    attron(COLOR_PAIR(PROJCTL_PAIR));
    mvprintw(position.y, position.x, icon);
    attroff(COLOR_PAIR(PROJCTL_PAIR));
}

void Projectile::deleteIcon() {
    attron(COLOR_PAIR(PAVE_PAIR));
    mvprintw(current_position.y, current_position.x, " ");
    attron(COLOR_PAIR(PAVE_PAIR));
}

void Projectile::setPosition(Position set) {
    current_position = set;
}

Position Projectile::getCurrentPosition() {
    return current_position;
}

void Projectile::setCurrentRoom(WINDOW* set) {
    current_room_win = set;
}

WINDOW* Projectile::getCurrentRoom() {
    return current_room_win;
}

void Projectile::moveProjectile() {
    switch(direction) {
        case DIR_NORTH:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x, current_position.y - 1)) && (!outOfBorder())) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.y = current_position.y - 1;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
        case DIR_EAST:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x + 1, current_position.y)) && (!outOfBorder())) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.x = current_position.x + 1;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
        case DIR_SOUTH:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x, current_position.y + 1)) && (!outOfBorder())) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.y = current_position.y + 1;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
        case DIR_WEST:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x - 1, current_position.y)) && (!outOfBorder())) {
                attron(COLOR_PAIR(PAVE_PAIR));
                mvprintw(current_position.y, current_position.x, " ");
                attroff(COLOR_PAIR(PAVE_PAIR));
                current_position.x = current_position.x - 1;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
    }
}

void Projectile::checkIfTimeToMove(system_clock::time_point time_now) {
    if(time_now > last_time_moved + moving_frequency) {
        moveProjectile();
        last_time_moved = time_now;
    }
}

bool Projectile::collisionWithRoomWall(int posx, int posy) {
    bool collided = false;

    if(((mvwinch(stdscr, posy, posx) & A_CHARTEXT) == 35)) {
        collided = true;
    }

    return collided;
}

bool Projectile::outOfBorder() {
    bool outofb = false;
    if((current_position.y <= 0) || (current_position.y > getmaxy(stdscr)) ||
    (current_position.x <= 0) || (current_position.x > getmaxx(stdscr))) {
        outofb = true;
    }
    return outofb;
}

bool Projectile::isAlive() {
    return alive;
}

void Projectile::setAliveStatus(bool set) {
    alive = set;
}

/*   UTILIZZO TIMER CON CHRONO

#include <ctime>   //stampa
#include <chrono>
using namespace std::chrono;


        mvprintw(1, 1, "Welcome to Online IDE!! Happy Coding :)");
		
		duration <int, std::ratio<1,1000> > one_ms (1);    //one_ms rappresenta un millisecondo
		duration <int, std::ratio<1,1> > one_s (2);     //one_s due secondi. possono essere moltiplicati nelle condizioni con *n
		
		system_clock::time_point timer1 = system_clock::now();
		system_clock::time_point timer2 = timer1 + one_s;

        //questo serve per la stampa più che altro
		
		time_t tt1 = system_clock::to_time_t (timer1);
		time_t tt2 = system_clock::to_time_t (timer2);
		
		mvprintw(15, 10, "timer1: "); mvprintw(15, 20, ctime(&tt1));
		mvprintw(16, 10, "timer2: "); mvprintw(16, 20, ctime(&tt2));
		//std::cout << "timer1-timer2: " << ctime(&timer1)-ctime(&timer2) << std::endl;
		
		getch();
		system_clock::time_point timer3 = system_clock::now();
		time_t tt3 = system_clock::to_time_t (timer3);
		mvprintw(17, 10, "timer3: "); mvprintw(17, 20, ctime(&tt3));
			if(timer3 > timer1 + one_s) {
				mvprintw(18, 10, "plllllljjhdfjdfndjfddddFTTOdo");//TRIGGERMOVE
			}
			
		
*/