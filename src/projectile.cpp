#include "../lib/projectile.hpp"
#include <chrono>

Projectile::Projectile() {
    proj_win = newwin(1, 1, 10, 10);
    icon = "*";
    current_position = {10, 10};
    direction = 1;
    //a caso, giusto per vederlo vagare sullo schermo
}

Projectile::Projectile(const char* icon, Position position, int direction, duration <int, std::ratio <1,1000 > > moving_frequency) {
    proj_win = newwin(1, 1, position.y, position.x);
    this->icon = icon;
    current_position = position;
    this->direction = direction;
    this->moving_frequency = moving_frequency;
    last_time_moved = system_clock::now();
}

void Projectile::spawn(WINDOW* win, Position position) {
    proj_win = newwin(1, 1, position.y, position.x);
    mvwprintw(proj_win, 0, 0, icon);
    wrefresh(proj_win);
}

void Projectile::deleteIcon() {
    wborder(proj_win,' ',' ',' ',' ',' ',' ',' ',' ');
    wrefresh(proj_win);
    delwin(proj_win);
}

Position Projectile::getCurrentPosition() {
    return current_position;
}

void Projectile::setPosition(Position set) {
    current_position = set;
}

void Projectile::moveProjectile() {
    switch(direction) {
        case 0:
            deleteIcon();
            current_position.y = current_position.y - 1;
            spawn(proj_win, current_position);
            break;
        case 1:
            deleteIcon();
            current_position.x = current_position.x + 1;
            spawn(proj_win, current_position);
            break;
        case 2:
            deleteIcon();
            current_position.y = current_position.y + 1;
            spawn(proj_win, current_position);
            break;
        case 3:
            deleteIcon();
            current_position.x = current_position.x - 1;
            spawn(proj_win, current_position);
            break;
    }
}

void Projectile::checkIfTimeToMove(system_clock::time_point time_now) {
    if(last_time_moved + moving_frequency > time_now) {
        moveProjectile();
    }
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