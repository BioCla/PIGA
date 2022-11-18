#include "../lib/projectile.hpp"
#include "../lib/engine.hpp"
#include "../lib/board.hpp"


Projectile::Projectile() {
    icon = "-";
    current_position = {1, 1};
    direction = DIR_EAST;     
    alive = false;
    current_room_win = stdscr;
}

Projectile::Projectile(const char* icon, Position position, int direction, int moving_frequency, WINDOW* win) : Entity(icon,position,win){
    this->direction = direction;
    moving_frequency_multiplyer = moving_frequency;
    duration <int, std::ratio <1,1000 > > one_millisecond (1);
    this->moving_frequency = moving_frequency_multiplyer * one_millisecond;
    last_time_moved = system_clock::now();
    alive = true;
}

void Projectile::spawn(Position position) {
    wattron(current_room_win, COLOR_PAIR(PROJCTL_PAIR));
    mvwprintw(current_room_win, position.y, position.x, icon);
    wattroff(current_room_win, COLOR_PAIR(PROJCTL_PAIR));
}

void Projectile::deleteIcon() {
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
    mvwprintw(current_room_win, current_position.y, current_position.x, " ");
    wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
}

void Projectile::setPosition(Position set) {
    current_position = set;
}

void Projectile::move() {
    switch(direction) {
        case DIR_NORTH:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x, current_position.y - 1)) && (!outOfBorder())) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.y--;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
        case DIR_EAST:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x + 1, current_position.y)) && (!outOfBorder())) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.x++;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
        case DIR_SOUTH:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x, current_position.y + 1)) && (!outOfBorder())) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.y++;
                spawn(current_position);
            }
            else {
                alive = false;
            }
            break;
        case DIR_WEST:
            deleteIcon();
            if((!collisionWithRoomWall(current_position.x - 1, current_position.y)) && (!outOfBorder())) {
                wattron(current_room_win, COLOR_PAIR(PAVE_PAIR));
                mvwprintw(current_room_win, current_position.y, current_position.x, " ");
                wattroff(current_room_win, COLOR_PAIR(PAVE_PAIR));
                current_position.x--;
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
        move();
        last_time_moved = time_now;
    }
}

bool Projectile::collisionWithRoomWall(int posx, int posy) {
    bool collided = false;
    int k = mvwinch(stdscr, posy, posx) & A_CHARTEXT;

    if(k == 35) {   //35 = "#"
        collided = true;
    }

    return collided;
}

bool Projectile::outOfBorder() {
    bool outofb = false;
    int xmax, ymax;
    getmaxyx(current_room_win, ymax, xmax);
    if((current_position.y <= 0) || (current_position.y > ymax) || (current_position.x <= 0) || (current_position.x > xmax)) {
        outofb = true;
    }
    return outofb;
}

void Projectile::setDamage(int damage) {
    this->damage = damage;
}

int Projectile::getDamage() {
    return this->damage;
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
