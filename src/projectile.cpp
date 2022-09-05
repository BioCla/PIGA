#include "../lib/projectile.hpp"
#include "../lib/engine.hpp"
#include <chrono>

Projectile::Projectile() {
    icon = "*";
    current_position = {10, 10};
    direction = DIR_EAST;     
    //a caso, giusto per vederlo vagare sullo schermo
}

Projectile::Projectile(const char* icon, Position position, int direction, int moving_frequency) {
    this->icon = icon;
    current_position = position;
    this->direction = direction;
    duration <int, std::ratio <1,1000 > > one_millisecond;
    this->moving_frequency = moving_frequency * one_millisecond;
    last_time_moved = system_clock::now();
}

void Projectile::spawn(Position position) {
    mvprintw(position.y, position.x, icon);
}

void Projectile::deleteIcon() {
    mvprintw(current_position.y, current_position.x, " ");
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
            if(!collisionWithRoomWall(current_position.x, current_position.y - 1)) {
                current_position.y = current_position.y - 1;
                spawn(current_position);
            }
            else {
                deleteIcon();
            }
            break;
        case DIR_EAST:
            deleteIcon();
            if(!collisionWithRoomWall(current_position.x + 1, current_position.y)) {
                current_position.x = current_position.x + 1;
                spawn(current_position);
            }
            else {
                deleteIcon();
            }
            break;
        case DIR_SOUTH:
            deleteIcon();
            if(!collisionWithRoomWall(current_position.x, current_position.y + 1)) {
                current_position.y = current_position.y + 1;
                spawn(current_position);
            }
            else {
                deleteIcon();
            }
            break;
        case DIR_WEST:
            deleteIcon();
            if(!collisionWithRoomWall(current_position.x - 1, current_position.y)) {
                current_position.x = current_position.x - 1;
                spawn(current_position);
            }
            else {
                deleteIcon();
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